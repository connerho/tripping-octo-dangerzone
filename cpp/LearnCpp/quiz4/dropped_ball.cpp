#include <iostream>

using namespace std;

constexpr double GRAV_CONSTANT = 9.8;

void printHelper(const double height, const double seconds) {
    double distance_fallen = GRAV_CONSTANT * (seconds * seconds) / 2.0;
    double curr_dist = height - distance_fallen;

    if(curr_dist > 0.0) {
        cout << "At " << seconds << " seconds, the ball is at height: " << curr_dist << " meters\n";
    } else {
        cout << "At " << seconds << " seconds, the ball is at the ground.\n";
    }
}

int main() {
    double height = 0;

    cout << "How tall is the building?" << "\n";
    cin >> height;

    printHelper(height, 1);
    printHelper(height, 2);
    printHelper(height, 3);
    printHelper(height, 4);
    printHelper(height, 5);
}