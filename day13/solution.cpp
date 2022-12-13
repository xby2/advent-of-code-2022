#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using std::ifstream;
using std::cout;
using std::endl;
using std::vector;
using std::sort;
using std::find;
using std::istream;
using std::ostream;

class ListOrInt;
class List;
class Int;

class ListOrInt {
public:
    virtual ~ListOrInt() {}
};

class Int : public ListOrInt {
public:
    int value;

    Int(int _value) : value(_value) {}

    ~Int() override {}
};

class List : public ListOrInt {
public:
    vector<ListOrInt*> values;

    List(vector<ListOrInt*> _values) : values(_values) {}
    List() {}
    List(int value) : values({ new Int(value) }) {}
    List(const List& other) {
        for (auto value : other.values) {
            if (List* l = dynamic_cast<List*>(value)) {
                values.push_back(new List(*l));
                continue;
            }
            Int* i = dynamic_cast<Int*>(value);
            values.push_back(new Int(*i));
        }
    }

    List& operator=(const List& rhs) {
        List copy(rhs);
        vector<ListOrInt*> temp = values;
        values = copy.values;
        copy.values = temp;
        return *this;
    }

    ~List() override {
        for (auto value : values) {
            delete value;
        }
    }

    bool operator==(const List& rhs);
    
    bool operator<(const List& rhs);
};

istream& operator>>(istream& is, List& rhs) {
    char bracket, comma;
    is >> bracket;
    while (is.peek() != ']') {
        if (is.peek() == '[') {
            List* list = new List();
            is >> *list;
            rhs.values.push_back(list);
            continue;
        }

        if (is.peek() == ',') {
            is >> comma;
            continue;
        }

        int value;
        is >> value;
        rhs.values.push_back(new Int(value));
    }
    is >> bracket;
    return is;
}

ostream& operator<<(ostream& os, const ListOrInt& rhs) {
    const List* const list = dynamic_cast<const List* const>(&rhs);
    const Int* const intt = dynamic_cast<const Int* const>(&rhs);
    if (list) {
        cout << "[";
        for (auto value : list->values) {
            cout << *value << ",";
        }
        cout << "]";
        return os;
    }
    cout << intt->value;
    return os;
}

int less(const ListOrInt& left, const ListOrInt& right) {
    const List* const left_list = dynamic_cast<const List* const>(&left);
    const List* const right_list = dynamic_cast<const List* const>(&right);
    const Int* const left_int = dynamic_cast<const Int* const>(&left);
    const Int* const right_int = dynamic_cast<const Int* const>(&right);

    if (left_int && right_int) {
        return left_int->value - right_int->value;
    } 

    if (left_int) {
        List left_as_list(left_int->value);
        return less(left_as_list, *right_list);
    }

    if (right_int) {
        List right_as_list(right_int->value);
        return less(*left_list, right_as_list);
    }

    for (uint i = 0; i < left_list->values.size(); ++i) {
        if (i >= right_list->values.size()) {
            return 1;
        }

        int less_val = less(*left_list->values[i], *right_list->values[i]);
        if (less_val != 0) {
            return less_val;
        }
    }
    
    if (left_list->values.size() == right_list->values.size()) {
        return 0;
    }

    return -1;
}

bool List::operator<(const List& rhs) {
    return less(*this, rhs) < 0;
}

bool List::operator==(const List& rhs) {
    return less(*this, rhs) == 0;
}

int main() {
    ifstream input("input.txt");

    vector<List> lists;
    while(input) {
        List list;
        input >> list;
        lists.push_back(list);
        char c;
        while (input && input.peek() != '[') {
            input.get(c);
        }
    }

    int total = 0;
    for (uint i = 0; i < lists.size(); i += 2) {
        int cmp = less(lists[i], lists[i + 1]);
        if (cmp < 0) {
            total += i / 2 + 1;
        }
    }

    cout << total << endl;

    List marker1;
    marker1.values.push_back(new List(2));
    List marker2;
    marker2.values.push_back(new List(6));

    lists.push_back(marker1);
    lists.push_back(marker2);

    sort(lists.begin(), lists.end());

    auto itr1 = find(lists.begin(), lists.end(), marker1);
    auto itr2 = find(lists.begin(), lists.end(), marker2);

    uint ind1 = distance(lists.begin(), itr1) + 1;
    uint ind2 = distance(lists.begin(), itr2) + 1;

    cout << ind1 * ind2 << endl;

}