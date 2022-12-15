#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using std::cout;
using std::ifstream;
using std::string;
using std::stoi;
using std::endl;
using std::priority_queue;

int main() {
    ifstream input("./input.txt");
    priority_queue<int> q;
    string check_empty;
    int current = 0;
    while (getline(input, check_empty)) {
        if (check_empty.empty()) {
            q.push(current);
            current = 0;
        } else {
            current += stoi(check_empty);
        }
    }
    
    cout << "Part 1: " << q.top() << endl;

    int total = 0;
    const int NUM_TOP = 3;
    for (int i = 0; i < NUM_TOP; ++i) {
        total += q.top();
        q.pop();
    }
    cout << "Part 2: " << total << endl;
}