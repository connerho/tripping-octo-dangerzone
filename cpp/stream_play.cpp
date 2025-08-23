#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::cerr;
using std::istringstream;

void printData(vector<string>& headers, vector<vector<string>>& data) {
    cout << "===Headers===\n";
    for(auto s: headers) {
        cout << s << ", ";
    }
    cout << "\n";

    cout << "===Data===\n";
    for(int i = 0; i < data.size(); i++) {
        for(int j = 0; j < data[0].size(); j++) {
            cout << data[i][j] << ", ";
        }
        cout << "\n";
    }
}

int main() {
    // Let's open up the file first
    ifstream file("C:\\Users\\conne\\OneDrive\\Documents\\GitHub\\tripping-octo-dangerzone\\python\\sample_data.csv");

    // Need to check if we were able to successfully open the file
    if(!file.is_open()) {
        cerr << "Error opening file!\n";
        return 1;
    }

    string line, tmp;
    vector<string> headers, row_data;
    vector<vector<string>> data;
    bool first_line = true;
    while(std::getline(file, line)) {
        istringstream csvStream(line);
        if(first_line) {
            while(std::getline(csvStream, tmp, ',')) {
                headers.push_back(tmp);
            }
            first_line = false;
        } else {
            while(std::getline(csvStream, tmp, ',')) {
                row_data.push_back(tmp);
            }
            data.push_back(row_data);
            row_data.clear();
        }
    }

    // cout << headers.size() << "\n";
    // cout << data.size() << "\n";
    // cout << data[0].size() << "\n";

    printData(headers, data);

    file.close();
}