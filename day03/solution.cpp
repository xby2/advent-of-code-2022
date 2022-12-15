#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <algorithm>

using std::ifstream;
using std::cout;
using std::endl;
using std::string;
using std::find;
using std::isupper;
using std::set;
using std::inserter;
using std::set_intersection;

int main() { 
    ifstream input("input.txt");

    string compartments;
    int total = 0;
    while(input >> compartments) {
        int compartment_length = compartments.size();
        string compartment_one_str = compartments.substr(0, compartment_length / 2);
        string compartment_two_str = compartments.substr(compartment_length / 2, compartment_length / 2);
        set<char> compartment_one(compartment_one_str.begin(), compartment_one_str.end());
        set<char> compartment_two(compartment_two_str.begin(), compartment_two_str.end());
        set<char> common;
        set_intersection(compartment_one.begin(), compartment_one.end(), 
            compartment_two.begin(), compartment_two.end(), 
            inserter(common, common.begin())
        );
        char c = *(common.begin());
        if (isupper(c)) {
            total += c - 'A' + 27;
        } else {
            total += c - 'a' + 1;
        }
    }
    input.close();
    
    ifstream input2("input.txt");

    string elf1, elf2, elf3;
    int total2 = 0;
    while (input2 >> elf1 >> elf2 >> elf3) {
        set<char> elf1_set(elf1.begin(), elf1.end());
        set<char> elf2_set(elf2.begin(), elf2.end());
        set<char> elf3_set(elf3.begin(), elf3.end());

        set<char> common1, common2;
        set_intersection(elf1_set.begin(), elf1_set.end(), elf2_set.begin(), elf2_set.end(), inserter(common1, common1.begin()));
        set_intersection(common1.begin(), common1.end(), elf3_set.begin(), elf3_set.end(), inserter(common2, common2.begin()));
        
        char c = *(common2.begin());
        if (isupper(c)) {
            total2 += c - 'A' + 27;
        } else {
            total2 += c - 'a' + 1;
        }
    }

    cout << total << endl;
    cout << total2 << endl;
}