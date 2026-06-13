#include <iostream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>
#include <random>

// Kevin starts at 0,0
// moves randomly
// print out the position every simulation step
// 50 simulation steps
// 0.

// 1. Initialize hardware entropy source for a truly random seed
std::random_device rd;
// 2. Initialize the generator engine with the seed
std::mt19937 gen(rd());


// 4. Generate random numbers
// std::cout << "Random Number 1: " << distrib(gen) << "\n";
// std::cout << "Random Number 2: " << distrib(gen) << "\n";


class Entity {
private:
    std::pair<int,int> coord;

public:

    Entity(int x, int y) : coord{x,y} {}
    const std::pair<int,int>& getCoordPair() const { return coord; }
    void updateCoordPair(const std::pair<int,int>& new_coord) {
        coord.first = new_coord.first;
        coord.second = new_coord.second;
    }

};

class Person : public Entity {
private:
    std::string name;

public:
    Person(int x, int y, const std::string& name) : Entity{x,y}, name{name} {}
    std::string_view getName() const { return name; }
    void pickRandomSquareAndUpdateCoord(const std::vector<std::pair<int,int>>& in_vec) {
        std::uniform_int_distribution<int> distrib(0, in_vec.size()-1);
        this->updateCoordPair(in_vec[distrib(gen)]);
    }
};

class Board {
private:
    const int x_size;
    const int y_size;

    bool isValidCoord(const std::pair<int,int>& coord) {
        return (coord.first >= 0 && coord.first < x_size &&
                coord.second >= 0 && coord.second < y_size);
    }

public:
    Board(int x_size, int y_size) : x_size{x_size}, y_size{y_size} {}
    bool getValidSquares(const std::pair<int,int>& curr_pos, std::vector<std::pair<int,int>>& inout_vec) {
        bool ret_bool {false};

        for(int x {-1}; x <= 1; ++x ) {
            for(int y {-1}; y <= 1; ++y) {
                std::pair<int,int> my_coord {curr_pos.first + x, curr_pos.second + y};
                if(isValidCoord(my_coord)) {
                    inout_vec.push_back(my_coord);
                }
            }
        }

        return (inout_vec.size() > 0);
    }
};

std::ostream& operator<<(std::ostream& out, const Person& person) {
    out << person.getName() << " | (" << person.getCoordPair().first << "," << person.getCoordPair().second << ")";
    return out;
}

int main() {
    constexpr int NUM_SIM_STEPS = 50;
    Board my_board(5,5);
    Person my_kevin(0,0,"Kevin");

    for(size_t sim_step {}; sim_step < NUM_SIM_STEPS; ++sim_step) {
        std::cout << sim_step << ". " << my_kevin << "\n";
        std::vector<std::pair<int,int>> coords;
        if(my_board.getValidSquares(my_kevin.getCoordPair(), coords)) {
            my_kevin.pickRandomSquareAndUpdateCoord(coords);
        } else {
            std::cout << "I'm stuck!\n";
            break;
        }
    }
    
    return 0;
}