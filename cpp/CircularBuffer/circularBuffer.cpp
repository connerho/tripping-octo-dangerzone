#include <utility>
#include <vector>
#include <iostream>
#include <cmath>
#include <cstdint>
#include <cassert>
#include <limits>

struct GPSCoord {
    double lat;
    double lon;
};

class CircularBuffer {
public:
    CircularBuffer(size_t size);

    // assume that every call to update is monotonically increasing
    void update(const GPSCoord& in_coord, uint64_t timestamp_ns);

    bool query(uint64_t timestamp_ns, GPSCoord& out_coord);

    // for unit testing
    size_t size() { return myBuffer.size(); }

    // for unit testing
    int getCurrIdx() { return curr_idx; }

private:
    std::vector<std::pair<GPSCoord, uint64_t>> myBuffer;
    int curr_idx;
};

CircularBuffer::CircularBuffer(size_t size) : curr_idx(0) {
    // Initialize vector to be constant size
    myBuffer = std::vector<std::pair<GPSCoord, uint64_t>>(size, std::pair<GPSCoord, uint64_t>( {0.0, 0.0}, 0));
}

void CircularBuffer::update(const GPSCoord& in_coord, uint64_t timestamp_ns) {
    myBuffer[curr_idx] = std::pair<GPSCoord, uint64_t>(in_coord, timestamp_ns);
    // If we fall off the edge of the vector, go back around to the beginning
    curr_idx = (curr_idx + 1) % myBuffer.size();
}

bool CircularBuffer::query(uint64_t timestamp_ns, GPSCoord& out_coord) {
    // "Oldest" sample will be the one pointed to by curr_idx
    // "Newest" sample will be the one at curr_idx - 1 (accounting for wrap around)
    // bounds check and throw false if timestamp_ns is before the oldest sample or after
    // the newest sample
    if(timestamp_ns < myBuffer[curr_idx].second || 
       timestamp_ns > myBuffer[(curr_idx - 1 + myBuffer.size()) % myBuffer.size()].second) return false;

    // Otherwise we can perform a binary search
    int left_idx = 0;
    int right_idx = myBuffer.size() - 1;
    int mid_idx = 0;
    int buff_idx = 0;
    uint64_t diff = 0;
    GPSCoord closest_coord_to_time;
    uint64_t closest_time = std::numeric_limits<uint64_t>::max();

    while(left_idx <= right_idx) {
        mid_idx = ((left_idx + right_idx) / 2);
        // Index into the buffer should be just the mid_idx + the offset we started with (the curr_idx)
        buff_idx = (mid_idx + curr_idx) % myBuffer.size();
        diff = (timestamp_ns > myBuffer[buff_idx].second) ? timestamp_ns - myBuffer[buff_idx].second :
                                                           myBuffer[buff_idx].second - timestamp_ns;
        if(diff < closest_time) {
            closest_time = diff;
            closest_coord_to_time = myBuffer[buff_idx].first;
        }

        if(timestamp_ns > myBuffer[buff_idx].second) {
            // we need to check into the future (go right)
            left_idx = mid_idx + 1;
        } else if(timestamp_ns < myBuffer[buff_idx].second) {
            // we need to check in the past (go left)
            right_idx = mid_idx - 1;
        } else {
            closest_coord_to_time = myBuffer[buff_idx].first;
            break;
        }
    }

    out_coord = closest_coord_to_time;
    // std::cout << "Returning GPS Coordinate Lat: " << out_coord.lat << " Lon: " << out_coord.lon << "\n";

    return true;
}

int main() {

    CircularBuffer myCircBuff(5);

    GPSCoord myGpsCoord = {0.0, 0.0};
    uint64_t init_time_ns = 10000;
    constexpr uint64_t delta_ns = 50000;
    constexpr double delta_lat_lon = 1.0;

    for(int i = 0; i < myCircBuff.size(); ++i) {
        myCircBuff.update(myGpsCoord, init_time_ns);
        init_time_ns += delta_ns;
        myGpsCoord.lat += delta_lat_lon;
        myGpsCoord.lon += delta_lat_lon;
    }

    // Make sure that a circular buffer index actually wrapped around
    assert(myCircBuff.getCurrIdx() == 0);

    // Boundary checking
    assert(myCircBuff.query(100, myGpsCoord) == false);
    assert(myCircBuff.query(1000000, myGpsCoord) == false);

    // Checking that our binary search algo works
    assert(myCircBuff.query(10000, myGpsCoord) == true);
    assert(myGpsCoord.lat == 0.0 && myGpsCoord.lon == 0.0);
    assert(myCircBuff.query(30000, myGpsCoord) == true);
    assert(myGpsCoord.lat == 0.0 && myGpsCoord.lon == 0.0);

    assert(myCircBuff.query(40000, myGpsCoord) == true);
    assert(myGpsCoord.lat == 1.0 && myGpsCoord.lon == 1.0);
    assert(myCircBuff.query(60000, myGpsCoord) == true);
    assert(myGpsCoord.lat == 1.0 && myGpsCoord.lon == 1.0);
    assert(myCircBuff.query(84999, myGpsCoord) == true);
    assert(myGpsCoord.lat == 1.0 && myGpsCoord.lon == 1.0);

    assert(myCircBuff.query(85001, myGpsCoord) == true);
    assert(myGpsCoord.lat == 2.0 && myGpsCoord.lon == 2.0);
    assert(myCircBuff.query(110000, myGpsCoord) == true);
    assert(myGpsCoord.lat == 2.0 && myGpsCoord.lon == 2.0);

    assert(myCircBuff.query(160000, myGpsCoord) == true);
    assert(myGpsCoord.lat == 3.0 && myGpsCoord.lon == 3.0);

    assert(myCircBuff.query(210000, myGpsCoord) == true);
    assert(myGpsCoord.lat == 4.0 && myGpsCoord.lon == 4.0);

    // Check to see what happens when we start actually circling the buffer
    constexpr int loop_times = 1234;
    // Reset our update variables
    myGpsCoord = {0.0, 0.0};
    init_time_ns = 10000;
    for(int i = 0; i < loop_times; ++i) {
        // std::cout << "init time is " << init_time_ns << "\n";
        // std::cout << "gps coord is lat: " << myGpsCoord.lat << " lon: " << myGpsCoord.lon << "\n";
        myCircBuff.update(myGpsCoord, init_time_ns);
        init_time_ns += delta_ns;
        myGpsCoord.lat += delta_lat_lon;
        myGpsCoord.lon += delta_lat_lon;
    }

    // Make sure that our indexer is in the right position after looping around for a while
    assert(myCircBuff.getCurrIdx() == loop_times % myCircBuff.size());

    // std::cout << "query time is " << 10000 + (delta_ns * loop_times) << "\n";
    // (Loop_times - 5) should give us the "oldest" GPS coordinate
    int oldest_gps_idx = loop_times - 5;
    assert(myCircBuff.query(10000 + (delta_ns * oldest_gps_idx), myGpsCoord) == true);
    assert(myGpsCoord.lat == (0.0 + (delta_lat_lon * oldest_gps_idx)) && myGpsCoord.lon == (0.0 + (delta_lat_lon * oldest_gps_idx)));

    // (Loop_times - 4) should give us the second "oldest" GPS coordinate
    int second_oldest_gps_idx = loop_times - 4;
    assert(myCircBuff.query(10000 + (delta_ns * second_oldest_gps_idx), myGpsCoord) == true);
    assert(myGpsCoord.lat == (0.0 + (delta_lat_lon * second_oldest_gps_idx)) && myGpsCoord.lon == (0.0 + (delta_lat_lon * second_oldest_gps_idx)));

    // (Loop_times - 3) should give us the next GPS coordinate
    int next_gps_idx = loop_times - 3;
    assert(myCircBuff.query(10000 + (delta_ns * next_gps_idx), myGpsCoord) == true);
    assert(myGpsCoord.lat == (0.0 + (delta_lat_lon * next_gps_idx)) && myGpsCoord.lon == (0.0 + (delta_lat_lon * next_gps_idx)));

    // (Loop_times - 2) should give us the next GPS coordinate
    next_gps_idx = loop_times - 2;
    assert(myCircBuff.query(10000 + (delta_ns * next_gps_idx), myGpsCoord) == true);
    assert(myGpsCoord.lat == (0.0 + (delta_lat_lon * next_gps_idx)) && myGpsCoord.lon == (0.0 + (delta_lat_lon * next_gps_idx)));

    // (Loop_times - 1) should give us the "newest" GPS coordinate
    int newest_gps_idx = loop_times - 1;
    assert(myCircBuff.query(10000 + (delta_ns * newest_gps_idx), myGpsCoord) == true);
    assert(myGpsCoord.lat == (0.0 + (delta_lat_lon * newest_gps_idx)) && myGpsCoord.lon == (0.0 + (delta_lat_lon * newest_gps_idx)));

    // If we get here, all asserts have passed
    std::cout << "All tests PASS\n";

    return 0;
}