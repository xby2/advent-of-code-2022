#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <queue>

using std::ifstream;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::queue;
using std::pair;

struct Tile {
    char altitude;
    char dir_moved;
    bool is_start;
    bool is_end;

    Tile(char c) : dir_moved('.'), is_start(false), is_end(false) {
        if (c == 'S') {
            altitude = 'a';
            is_start = true;
        } else if (c == 'E') {
            altitude = 'z';
            is_end = true;
        } else {
            altitude = c;
        }
    }
};

pair<uint, uint> search(vector<vector<Tile>>& map, int end_row, int end_col, bool is_part_two = false) {
    queue<pair<uint, uint>> paths;
    paths.push({ end_row, end_col });
    auto is_allowed = [](const Tile& t, const Tile& current_tile) {
        char min_alt = char(current_tile.altitude - 1);
        return t.dir_moved == '.' && t.altitude >= min_alt;
    };
    while (!paths.empty()) {
        pair<uint, uint> next = paths.front();
        paths.pop();

        Tile& current_tile = map[next.first][next.second];
        if (current_tile.is_start || (is_part_two && current_tile.altitude == 'a')) {
            return next;
        }

        if (next.first > 0) {
            Tile& t = map[next.first - 1][next.second];
            if (is_allowed(t, current_tile)) {
                paths.push({ next.first - 1, next.second });
                t.dir_moved = 'd';
            }
        }
        if (next.first < map.size() - 1) {
            Tile& t = map[next.first + 1][next.second];
            if (is_allowed(t, current_tile)) {
                paths.push({ next.first + 1, next.second });
                t.dir_moved = 'u';
            }
        }
        if (next.second > 0) {
            Tile& t = map[next.first][next.second - 1];
            if (is_allowed(t, current_tile)) {
                paths.push({ next.first, next.second - 1});
                t.dir_moved = 'r';
            }
        }
        if (next.second < map[next.first].size() - 1) {
            Tile& t = map[next.first][next.second + 1];
            if (is_allowed(t, current_tile)) {
                paths.push({ next.first, next.second + 1});
                t.dir_moved = 'l';
            }
        }
    }
    return pair<uint, uint>(-1, -1);
}

int get_path_distance(const vector<vector<Tile>>& map, uint start_row, uint start_col, uint end_row, uint end_col) {
    uint current_row = start_row;
    uint current_col = start_col;
    Tile current_tile = map[current_row][current_col];
    int num_steps = 0;
    while (current_row != end_row || current_col != end_col) {
        switch(current_tile.dir_moved) {
            case 'd':
                ++current_row;
                break;
            case 'u':
                --current_row;
                break;
            case 'l':
                --current_col;
                break;
            case 'r':
                ++current_col;
                break;
            default:
                cout << "uh oh" << endl;
                cout << current_row << endl;
                cout << current_col << endl;
                cout << map[current_row][current_col].dir_moved;
                cout << map[current_row][current_col].altitude;
                exit(1);

        }
        current_tile = map[current_row][current_col];
        ++num_steps;
    }
    return num_steps;
}

int main() {
    ifstream input("input.txt");

    vector<vector<Tile>> map;
    string line;

    uint start_row = 0;
    uint start_col = 0;
    uint end_row = 0;
    uint end_col = 0;
    while (getline(input, line)) {
        map.push_back(vector<Tile>(line.begin(), line.end()));
        if (line.find("S") != string::npos) {
            start_col = line.find("S");
            start_row = map.size() - 1;

        }
        if (line.find("E") != string::npos) {
            end_col = line.find("E");
            end_row = map.size() - 1;
        }
    }
    
    auto p2_map = map;

    auto p1_start = search(map, end_row, end_col);
    if (p1_start.first != start_row || p1_start.second != start_col) {
        cout << "Did not find p1" << endl;
        exit(1);
    }

    int p1_num_steps = get_path_distance(map, start_row, start_col, end_row, end_col);
    cout << p1_num_steps << endl;

    auto p2_start = search(p2_map, end_row, end_col, true);
    int p2_num_steps = get_path_distance(p2_map, p2_start.first, p2_start.second, end_row, end_col);

    cout << p2_num_steps << endl;
}