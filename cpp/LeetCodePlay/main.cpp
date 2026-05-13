#include <vector>

using namespace std;

void rotate(vector<int>& nums, int k) {
        // Figure out how many we actually need to shove to the front
        // Method one
        // int num_in_front = k % nums.size();
// 
        // for(int i = 0; i < num_in_front; i++) {
        //     nums.insert(nums.begin(), nums.back());
        //     nums.pop_back();
        // }

        // Method 2
        // Make use of insert() and erase() more cleverly
        int num_in_front = k % nums.size();
        nums.insert(nums.begin(), nums.end()-num_in_front, nums.end());
        nums.erase(nums.end()-num_in_front, nums.end());
    }

int main() {

    vector<int> my_vec = {1, 2, 3};
    int k = 1;
    rotate(my_vec, k);

}