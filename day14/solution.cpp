#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>
#include <algorithm>

using namespace std;

using RockFormation = vector<pair<int, int>>;

class RockMap {
    set<pair<int,int>> sand_tiles;
    set<pair<int, int>> rock_tiles;

    int x_min;
    int x_max;
    int y_min;
    int y_max;

public:

    RockMap() : x_min(500), x_max(0), y_min(0), y_max(0) {}

    void update_bounds(const pair<int, int>& coordinate) {
        if (x_min > coordinate.first) {
            x_min = coordinate.first;
        }
        if (x_max < coordinate.first) {
            x_max = coordinate.first;
        }
        if (y_min > coordinate.second) {
            y_min = coordinate.second;
        }
        if (y_max < coordinate.second) {
            y_max = coordinate.second;
        }
    }

    void add_rocks(const RockFormation& rock) {
        for (uint i = 0; i < rock.size() - 1; ++i) {
            int x_start = min(rock[i].first, rock[i + 1].first);
            int x_end = max(rock[i].first, rock[i + 1].first);
            int y_start = min(rock[i].second, rock[i + 1].second);
            int y_end = max(rock[i].second, rock[i + 1].second);
            for (int x = x_start; x <= x_end; ++x) {
                rock_tiles.insert({ x, y_start });
            }
            for (int y = y_start; y <= y_end; ++y) {
                rock_tiles.insert({ x_start, y });
            }
            update_bounds(rock[i]);
            update_bounds(rock[i + 1]);
        }
    }

    void add_sand(const pair<int, int>& sand_coord) {
        sand_tiles.insert(sand_coord);
    }

    bool in_bounds(const pair<int, int>& coordinate) const {
        return x_min <= coordinate.first
            && coordinate.first <= x_max
            && y_min <= coordinate.second
            && coordinate.second <= y_max;
    }

    int get_sand_count() const {
        return sand_tiles.size() - 1; // removing sand source
    }

    bool tile_is_free(const pair<int, int>& coordinate) const {
        return coordinate.second < y_max + 2 
            && !sand_tiles.contains(coordinate) 
            && !rock_tiles.contains(coordinate);
    }
};

int main() {
    ifstream input("input.txt");
    
    RockMap rock_map;
    pair<int, int> sand_source = { 500, 0 };
    rock_map.add_sand(sand_source);
    string rock_line_str;
    while (getline(input, rock_line_str)) {
        stringstream rock_line_stream(rock_line_str);
        RockFormation rockform;
        int x,y;
        char comma;
        while (rock_line_stream >> x >> comma >> y) {
            rockform.push_back({x, y});
            string arrow; // " -> "
            rock_line_stream >> arrow;
        }
        rock_map.add_rocks(rockform);
    }

    RockMap rock_map_p2(rock_map);

    bool dropped_sand = true;
    while (dropped_sand) {
        int x = sand_source.first;
        int y = sand_source.second;
        bool sand_at_rest = false;
        while(!sand_at_rest) {
            if (!rock_map.in_bounds({x, y})) {
                dropped_sand = false;
                break;
            }
            if (rock_map.tile_is_free({x, y + 1})) {
                ++y;
                continue;
            }
            if (rock_map.tile_is_free({x - 1, y + 1})) {
                --x;
                ++y;
                continue;
            }
            if (rock_map.tile_is_free({x + 1, y + 1})) {
                ++x;
                ++y;
                continue;
            }
            if (rock_map.tile_is_free({x, y})) {
                rock_map.add_sand({x, y});
                sand_at_rest = true;
                continue;
            }
        }
    }

    cout << rock_map.get_sand_count() << endl;

    while (rock_map_p2.tile_is_free({ sand_source.first - 1, sand_source.second + 1 })
            || rock_map_p2.tile_is_free({ sand_source.first, sand_source.second + 1 })
            || rock_map_p2.tile_is_free({ sand_source.first + 1, sand_source.second + 1 })) {
        int x = sand_source.first;
        int y = sand_source.second;
        bool sand_at_rest = false;
        while(!sand_at_rest) {
            if (rock_map_p2.tile_is_free({x, y + 1})) {
                ++y;
                continue;
            }
            if (rock_map_p2.tile_is_free({x - 1, y + 1})) {
                --x;
                ++y;
                continue;
            }
            if (rock_map_p2.tile_is_free({x + 1, y + 1})) {
                ++x;
                ++y;
                continue;
            }
            if (rock_map_p2.tile_is_free({x, y})) {
                rock_map_p2.add_sand({x, y});
                sand_at_rest = true;
                continue;
            }
        }
    }

    cout << rock_map_p2.get_sand_count() + 1 << endl;
}