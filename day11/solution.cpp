#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using std::endl;
using std::cout;
using std::string;
using std::ifstream;
using std::vector;
using std::stringstream;
using std::ostream;

class Monkey {
    int divisible_by;
    int num_items_inspected;
    char op;
    string change;
    Monkey* throw_if_true;
    Monkey* throw_if_false;
    vector<int> items;
    bool sees_relief;
    int mod_val;

public:
    void init_monkey(int d, 
            Monkey* t, Monkey* f, char o, string c, vector<int> i, bool sr = true) {
        divisible_by = d;
        num_items_inspected = 0;
        op = o; 
        change = c;
        throw_if_true = t; 
        throw_if_false = f; 
        items = i;
        sees_relief = sr;
        mod_val = 0;
    }

    int get_divisible_by() const {
        return divisible_by;
    }

    void set_mod_val(int mod) {
        mod_val = mod;
    }

    void inspect_item() {
        for (auto& item : items) {
            ++num_items_inspected;
            int change_num = change == "old" ? item : stoi(change);
            if (op == '*') {
                item = (item * change_num) % mod_val;
            }
            else if (op == '+') {
                item = (item + change_num) % mod_val;
            }

            if (sees_relief) {
                item /= 3;
            }
        }
    }

    void throw_items() {
        for (auto item : items) {
            if (item % divisible_by) {
                throw_if_false->items.push_back(item);
            } else {
                throw_if_true->items.push_back(item);
            }
        }
        items.clear();
    }

    int get_num_items_inspected() {
        return num_items_inspected;
    }

    friend ostream& operator<<(ostream& os, const Monkey& m);
};

ostream& operator<<(ostream& os, const Monkey& m) {
    os << "Items: ";
    for (auto item : m.items) {
        os << item << ", ";
    }
    os << endl;
    os << "Operation: new = old " << m.op << " " << m.change << endl;
    os << "Test: divisible by " << m.divisible_by << endl;

    return os;
}

int main() {
    ifstream input("input.txt");

    vector<Monkey> monkeys_p1(8);
    vector<Monkey> monkeys_p2(8);
    int current_monkey = 0;
    int mod_val = 1;

    string monkey_strt, items, operation, test, t_cond, f_cond, empty;
    while (getline(input, monkey_strt) 
            && getline(input, items)
            && getline(input, operation)
            && getline(input, test)
            && getline(input, t_cond)
            && getline(input, f_cond)) {

        string words;
        
        stringstream line(items);
        line >> words >> words;

        vector<int> items;
        int item_worry;
        while (line >> item_worry) {
            items.push_back(item_worry);
            line >> words;
        }

        line.clear();
        line.str(operation);
        char op;
        string change;
        line >> words >> words >> words >> words >> op >> change;

        line.clear();
        line.str(test);
        int divisible_by;
        line >> words >> words >> words >> divisible_by;
        mod_val *= divisible_by;

        line.clear();
        line.str(t_cond);
        int t_monkey_num;
        line >> words >> words >> words >> words >> words >> t_monkey_num;

        line.clear();
        line.str(f_cond);
        int f_monkey_num;
        line >> words >> words >> words >> words >> words >> f_monkey_num;

        monkeys_p1[current_monkey].init_monkey(
            divisible_by, &monkeys_p1[t_monkey_num], &monkeys_p1[f_monkey_num], 
            op, change, items);

        monkeys_p2[current_monkey].init_monkey(
            divisible_by, &monkeys_p2[t_monkey_num], &monkeys_p2[f_monkey_num], 
            op, change, items, false);

        ++current_monkey;
        getline(input, empty);
    }

    for (Monkey& m : monkeys_p2) {
        m.set_mod_val(mod_val);
    }

    for (int i = 0; i < 20; ++i) {
        for (Monkey& m : monkeys_p1) {
            m.inspect_item();
            m.throw_items();
        }
    }
    
    int top1 = 0, top2 = 0;
    for (Monkey& m : monkeys_p1) {
        int num_items_inspected = m.get_num_items_inspected();
        if (num_items_inspected > top1) {
            top2 = top1;
            top1 = num_items_inspected;
        } else if (num_items_inspected > top2) {
            top2 = num_items_inspected;
        }
    }

    cout << top1 * top2 << endl;

        for (int i = 0; i < 10000; ++i) {
        for (Monkey& m : monkeys_p2) {
            m.inspect_item();
            m.throw_items();
        }
    }
    
    top1 = 0;
    top2 = 0;
    for (Monkey& m : monkeys_p2) {
        int num_items_inspected = m.get_num_items_inspected();
        if (num_items_inspected > top1) {
            top2 = top1;
            top1 = num_items_inspected;
        } else if (num_items_inspected > top2) {
            top2 = num_items_inspected;
        }
    }

    cout << (long long)top1 * top2 << endl;
}
