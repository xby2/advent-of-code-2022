#include <fstream>
#include <iostream>
#include <deque>
#include <string>
#include <sstream>
#include <vector>

using std::ifstream;
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::deque;
using std::stringstream;

void partOne(ifstream& input, vector<deque<char>>& stacks);
void partTwo(ifstream& input, vector<deque<char>>& stacks);

int main() {
    ifstream input("input.txt");

    string line;
    getline(input, line);
    int num_stacks = (line.size() + 1) / 4;
    vector<deque<char>> stacks(num_stacks);

    // create crate stacks
    do {
        stringstream crates(line);
        string crate;
        int current_crate = 0;
        while (getline(crates, crate, '[')) {
            if (crate == "") {
                continue;
            }
            stacks[current_crate].push_front(crate[0]);
            current_crate += (crate.size() + 1) / 4;
        }
    }
    while(getline(input, line) && line.find('[') != string::npos);

    // remove empty line
    getline(input, line);

    // partOne(input, stacks);
    partTwo(input, stacks);

    for (auto stack : stacks) {
        cout << stack.back();
    }

    cout << endl;
}

void partOne(ifstream& input, vector<deque<char>>& stacks) {
    string word;
    int count, from, to;
    while(input >> word >> count >> word >> from >> word >> to) {
        --from;
        --to;
        for (int i = 0; i < count; ++i) {
            char crate = stacks[from].back();
            stacks[from].pop_back();
            stacks[to].push_back(crate);
        }
    }
}

void partTwo(ifstream& input, vector<deque<char>>& stacks) {
    string word;
    int count, from, to;
    while(input >> word >> count >> word >> from >> word >> to) {
        --from;
        --to;
        vector<char> to_move;
        for (int i = 0; i < count; ++i) {
            char crate = stacks[from].back();
            stacks[from].pop_back();
            to_move.push_back(crate);
        }
        
        for (int i = count - 1; i >= 0; --i) {
            stacks[to].push_back(to_move[i]);
        }
    }
}