#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <limits>

using std::ifstream;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::queue;
using std::pair;
using std::numeric_limits;

struct Tile {
    char altitude;
    char from_dir;
    bool is_end;

    Tile(char c) : from_dir('.'), is_end(false) {
        if (c == 'S') {
            altitude = 'a';
        } else if (c == 'E') {
            altitude = 'z';
            is_end = true;
        } else {
            altitude = c;
        }
    }
};

bool search(vector<vector<Tile>>& map, int start_row, int start_col) {
    queue<pair<uint, uint>> paths;
    paths.push({ start_row, start_col });
    while (!paths.empty()) {
        pair<uint, uint> next = paths.front();
        paths.pop();

        Tile& current_tile = map[next.first][next.second];
        if (current_tile.is_end) {
            return true;
        }

        char max_altitude = char(current_tile.altitude + 1);

        if (next.first > 0) {
            Tile& t = map[next.first - 1][next.second];
            if (t.from_dir == '.' && t.altitude <= max_altitude) {
                paths.push({ next.first - 1, next.second });
                t.from_dir = 'd';
            }
        }
        if (next.first < map.size() - 1) {
            Tile& t = map[next.first + 1][next.second];
            if (t.from_dir == '.' && t.altitude <= max_altitude) {
                paths.push({ next.first + 1, next.second });
                t.from_dir = 'u';
            }
        }
        if (next.second > 0) {
            Tile& t = map[next.first][next.second - 1];
            if (t.from_dir == '.' && t.altitude <= max_altitude) {
                paths.push({ next.first, next.second - 1});
                t.from_dir = 'r';
            }
        }
        if (next.second < map[next.first].size() - 1) {
            Tile& t = map[next.first][next.second + 1];
            if (t.from_dir == '.' && t.altitude <= max_altitude) {
                paths.push({ next.first, next.second + 1});
                t.from_dir = 'l';
            }
        }
    }
    return false;
}

int get_path_distance(const vector<vector<Tile>>& map, uint end_row, uint end_col, uint start_row, uint start_col) {
    uint current_row = end_row;
    uint current_col = end_col;
    Tile current_tile = map[current_row][current_col];
    int num_steps = 0;
    while (current_row != start_row || current_col != start_col) {
        switch(current_tile.from_dir) {
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
                cout << map[current_row][current_col].from_dir;
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

    bool found_p1 = search(map, start_row, start_col);
    if (!found_p1) {
        cout << "Did not find p1" << endl;
        exit(1);
    }

    int p1_num_steps = get_path_distance(map, end_row, end_col, start_row, start_col);
    cout << p1_num_steps << endl;

    vector<pair<uint, uint>> p2_starting_tiles;
    for (uint i = 0; i < p2_map.size(); ++i) {
        for (uint j = 0; j < p2_map[i].size(); ++j) {
            if (p2_map[i][j].altitude == 'a') {
                p2_starting_tiles.push_back({ i, j });
            }
        }
    }

    int p2_min_distance = numeric_limits<int>::max();
    for (auto start : p2_starting_tiles) {
        auto test_map = p2_map;
        if (search(test_map, start.first, start.second)) {
            int distance = get_path_distance(test_map, end_row, end_col, start.first, start.second);
            if (distance < p2_min_distance) {
                p2_min_distance = distance;
            }
        }
    }

    cout << p2_min_distance << endl;
}