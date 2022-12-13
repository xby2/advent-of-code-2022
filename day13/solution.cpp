#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

using std::ifstream;
using std::cout;
using std::endl;
using std::vector;
using std::unique_ptr;
using std::make_unique;

class ListOrInt;
class List;
class Int;

class ListOrInt {
public:
    virtual bool operator<(const List&) const = 0;
    virtual bool operator<(const Int&) const = 0;
};

class Int : public ListOrInt {
    int value;
public:
    bool operator<(const Int& rhs) const override;

    bool operator<(const List& rhs) const override;
};

class List : public ListOrInt {
    vector<unique_ptr<ListOrInt>> values;

public:
    List(vector<unique_ptr<ListOrInt>> _values) : values(_values) {}
    List(const Int& value) : values({make_unique<ListOrInt>(value)}) {}

    bool operator<(const Int& rhs) const override;

    bool operator<(const List& rhs) const override;
};

bool Int::operator<(const Int& rhs) const {
    cout << "Int < Int" << endl;
    return value < rhs.value;
}

bool Int::operator<(const List& rhs) const {
    cout << "Int < List" << endl;
    return List(*this) < rhs;
}

bool List::operator<(const Int& rhs) const {
    cout << "List < Int" << endl;
    return *values[0] < rhs;
}

bool List::operator<(const List& rhs) const {
    cout << "List < List" << endl;
    return *values[0] < *rhs.values[0];
}

int main() {
    ifstream input("input.txt");

    // vector<unique_ptr<ListOrInt>> values;

    cout << Int(5) < Int(6) << endl;
    cout << Int(6) < Int(5) << endl;
    cout << List(5) < List(6) << endl;
    cout << List(6) < List(5) << endl;
    cout << Int(5) < List(6) << endl;
    cout << List(5) < Int(6) << endl;


}