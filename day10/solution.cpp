#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <cmath>

using std::ifstream;
using std::string;
using std::vector;
using std::set;
using std::cout;
using std::endl;

int main() {
    ifstream input("input.txt");

    string command;
    vector<int> after_cycle_change_value;
    set<int> cycle_strength_checks = {20, 60, 100, 140, 180, 220};

    while (input >> command) {
        after_cycle_change_value.push_back(0);

        if (command == "addx") {
            int value;
            input >> value;
            after_cycle_change_value.push_back(value);
        }
    }

    int x = 1;
    int signal_strength_sum = 0;

    for (uint i = 0; i < after_cycle_change_value.size(); ++i) {
        if (cycle_strength_checks.contains(i + 1)) {
            signal_strength_sum += (i + 1) * x;
        }
        int pixel_pos = i % 40;
        if (pixel_pos == 0) {
            cout << '\n';
        }
        if (abs(x - pixel_pos) <= 1) {
            cout << "#";
        } else {
            cout << ".";
        }
        x += after_cycle_change_value[i];
    }

    cout << "\n\n" << signal_strength_sum << endl;
}