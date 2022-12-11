#include <fstream>
#include <iostream>
#include <set>

using std::ifstream;
using std::string;
using std::set;
using std::cout;
using std::endl;

int main() {
    ifstream input("input.txt");

    string data;
    input >> data;

    // part 1
    for (uint i = 0; i < data.length() - 4; ++i) {
        set<char> buffer(data.begin() + i, data.begin() + i + 4);
        if (buffer.size() == 4) {
            cout << i + 4 << endl;
            break;
        }
    }

    // part 2
    for (uint i = 0; i < data.length() - 14; ++i) {
        set<char> buffer(data.begin() + i, data.begin() + i + 14);
        if (buffer.size() == 14) {
            cout << i + 14 << endl;
            break;
        }
    }
}