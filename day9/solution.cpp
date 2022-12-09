#include <iostream>
#include <fstream>
#include <set>
#include <vector>

using std::vector;
using std::cout;
using std::endl;
using std::set;
using std::ifstream;
using std::ostream;

class Knot {
    int x;
    int y;
public:
    Knot() : x(0), y(0) {}

    void move(char direction) {
        switch(direction) {
            case 'U':
                ++y;
                break;
            case 'D':
                --y;
                break;
            case 'R':
                ++x;
                break;
            case 'L':
                --x;
                break;
            default:
                cout << "unrecognized direction" << endl;
        }
    }

    bool is_adjacent(const Knot& other) const {
        return abs(x - other.x) <= 1 &&
            abs(y - other.y) <= 1;
    }

    void get_pulled(const Knot& other) {
        if (is_adjacent(other)) {
            return;
        }
        if (x == other.x) {
            y += other.y > y ? 1 : -1;
            return;
        }
        if (y == other.y) {
            x += other.x > x ? 1 : -1;
            return;
        }
        
        y += other.y > y ? 1 : -1;
        x += other.x > x ? 1 : -1;
        
    }

    

    bool operator<(const Knot& r) const {
        if (x == r.x) return y < r.y;
        return x < r.x;
    }

    friend class Rope;
    friend ostream& operator<<(ostream& os, const Knot& p);
};

ostream& operator<<(ostream& os, const Knot& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

class Rope {
    vector<Knot> knots;
public:
    Rope(int num_knots) : knots(num_knots) {}

    void move(char direction) {
        knots.front().move(direction);
        for (uint i = 1; i < knots.size(); ++i) {
            knots[i].get_pulled(knots[i - 1]);
        }
        
    }

    const Knot& get_tail() {
        return knots.back();
    }

    friend ostream& operator<<(ostream& os, const Rope& r);
};

ostream& operator<<(ostream& os, const Rope& r) {
    for (Knot knot : r.knots) {
        os << knot << endl;
    }
    return os;
}

int main() {
    ifstream input("input.txt");

    Rope p1_rope(2);
    Rope p2_rope(10);
    set<Knot> p1_tail_Knots;
    set<Knot> p2_tail_Knots;
    char direction;
    int moves;
    while(input >> direction >> moves) {
        cout << p2_rope << endl;
        for (int i = 0; i < moves; ++i) {
            p1_rope.move(direction);
            p2_rope.move(direction);
            p1_tail_Knots.insert(p1_rope.get_tail());
            p2_tail_Knots.insert(p2_rope.get_tail());
        }
    }

   cout << p2_rope << endl;

    cout << p1_tail_Knots.size() << endl;
    cout << p2_tail_Knots.size() << endl;
}