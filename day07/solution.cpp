#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>

using std::vector;
using std::ifstream;
using std::map;
using std::stringstream;
using std::cout;
using std::endl;
using std::string;

int main() {
    ifstream input("input.txt");

    map<string, int> dir_sizes;
    vector<string> path;

    string line;
    while (getline(input, line)) {
        vector<string> inputs;
        stringstream data(line);
        string datum;
        while (data >> datum) {
            inputs.push_back(datum);
        }
        if (inputs[1] == "cd") {
            if (inputs[2] == "..") {
                path.pop_back();
            } else {
                path.push_back(inputs[2]);
            }
        } else if (inputs[1] == "ls") {
            continue;
        } else if (inputs[0] == "dir") {
            continue;
        } else {
            string curr_path;
            int size = stoi(inputs[0]);
            for (string path_part : path) {
                curr_path += path_part;
                dir_sizes[curr_path] += size;
                curr_path += "/";
            }
        }
    }

    int total = 0;
    for (const auto& p : dir_sizes) {
        if (p.second <= 100000) {
            total += p.second;
        }
    }

    cout << total << endl;

    const int DISK_SPACE = 70000000;
    const int NEEDED_SPACE = 30000000;
    int max_allowed_use = DISK_SPACE - NEEDED_SPACE;
    int used_space = dir_sizes["/"];
    int needed_to_free = used_space - max_allowed_use;

    int min_file_size = used_space;
    for (const auto& p : dir_sizes) {
        if (p.second >= needed_to_free && p.second < min_file_size) {
            min_file_size = p.second;
        }
    }

    cout << min_file_size << endl;
}