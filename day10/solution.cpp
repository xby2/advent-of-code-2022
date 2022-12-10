#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <cmath>

using std::ifstream;
using std::string;
using std::set;
using std::cout;
using std::endl;


void do_cycle(int x, int current_cycle, int& signal_strength_sum) {
    static const set<int> cycle_strength_checks = {20, 60, 100, 140, 180, 220};

    if (cycle_strength_checks.contains(current_cycle)) {
        signal_strength_sum += current_cycle * x;
    }

    int pixel_pos = (current_cycle - 1) % 40;
    if (pixel_pos == 0) {
        cout << '\n';
    }
    if (abs(x - pixel_pos) <= 1) {
        cout << "#";
    } else {
        cout << ".";
    }
}

int main() {
    ifstream input("input.txt");

    string command;
    int x = 1;
    int signal_strength_sum = 0;
    int current_cycle = 1;

    while (input >> command) {
       do_cycle(x, current_cycle, signal_strength_sum);

        if (command == "addx") {
            int value;
            input >> value;
            ++current_cycle;
            do_cycle(x, current_cycle, signal_strength_sum);
            x += value;
        }

        ++current_cycle;
    }

    cout << "\n\n" << signal_strength_sum << endl;
}