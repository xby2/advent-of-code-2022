#include <fstream>
#include <iostream>

using std::ifstream;
using std::cout;
using std::endl;


int main() {
    ifstream input("input.txt");

    int num_fully_included = 0;
    int num_overlap = 0;
    int start1, end1;
    char delimeter;
    int start2, end2;
    while (input >> start1 >> delimeter >> end1 >> delimeter >> start2 >> delimeter >> end2) {
        if (start1 <= start2 && end1 >= end2) {
            ++num_fully_included;
            ++num_overlap;
        } else if (start2 <= start1 && end2 >= end1) {
            ++num_fully_included;
            ++num_overlap;
        } else if (start1 <= start2 && end1 >= start2) {
            ++num_overlap;
        } else if (start2 <= start1 && end2 >= start1) {
            ++num_overlap;
        }
    }

    cout << num_fully_included << endl;
    cout << num_overlap << endl;
}