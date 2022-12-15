#include <iostream>
#include <fstream>
#include <set>
#include <utility>
#include <string>
#include <sstream>
#include <cmath>
#include <limits>
#include <algorithm>
#include <bits/stdc++.h>

using Point = std::pair<int, int>;

int get_distance(const Point& a, const Point& b) {
    return std::abs(a.first - b.first) +
                std::abs(a.second - b.second);
}

class Sensor {
    Point sensor_pt;
    Point nearest_beacon;

    int distance;

public:

    Sensor(const Point& _sensor_pt, const Point& _beacon_pt) :
        sensor_pt(_sensor_pt), 
        nearest_beacon(_beacon_pt) {
            distance = get_distance(sensor_pt, nearest_beacon);
        }

    int is_point_not_beacon(const Point& p) const {
        return p != nearest_beacon &&
            get_distance(sensor_pt, p) <= distance;

    }

    bool is_row_in_range(int row) const {
        return std::abs(sensor_pt.second - row) <= distance;    
    }

    int get_leftmost_non_beacon_on_row(int row) const {
        int distance_to_row = std::abs(sensor_pt.second - row);
        int range_remaining = distance - distance_to_row;
        int x = sensor_pt.first - range_remaining;
        if (nearest_beacon == Point{ x, row }) {
            ++x;
        }
        return x;
    }

    int get_rightmost_non_beacon_on_row(int row) const {
        int distance_to_row = std::abs(sensor_pt.second - row);
        int range_remaining = distance - distance_to_row;
        int x = sensor_pt.first + range_remaining;
        if (nearest_beacon == Point{ x, row }) {
            --x;
        }
        return x;
    }

    bool operator<(const Sensor& other) const {
        return sensor_pt < other.sensor_pt;
    }

    std::set<Point> get_points_outside_covered() const {
        std::set<Point> points;
        for (int i = 0; i <= distance; ++i) {
                int x = (distance + 1) - i;
                int y = (distance + 1) - x;
                points.insert({sensor_pt.first + x, sensor_pt.second + y});
                points.insert({sensor_pt.first + x, sensor_pt.second - y});
                points.insert({sensor_pt.first - x, sensor_pt.second + y});
                points.insert({sensor_pt.first - x, sensor_pt.second - y});
        }
        return points;
    }

    
    friend std::ostream& operator<<(std::ostream& os, const Sensor& s);
};

std::ostream& operator<<(std::ostream& os, const Sensor& s) {
    os << "Sensor: (" << s.sensor_pt.first << "," << s.sensor_pt.second << ")" << ", ";
    os << "Beacon: (" << s.nearest_beacon.first << "," << s.nearest_beacon.second << ")";
    return os;
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    std::ifstream input("input.txt");

    std::set<Sensor> sensors;
    const int BEACON_ROW = 2000000;

    std::string line;
    while (std::getline(input, line)) {
        std::replace_if(line.begin(), line.end(), [](char c) { return !std::isdigit(c) && c != '-'; }, ' ');
        std::istringstream stream(line);
        int sensor_x, sensor_y, beacon_x, beacon_y;
        stream >> sensor_x >> sensor_y >> beacon_x >> beacon_y;
        sensors.insert(Sensor{{sensor_x, sensor_y}, { beacon_x, beacon_y }});
    }

    std::set<Sensor> sensors_near_row;
    std::copy_if(sensors.begin(), sensors.end(), 
        std::inserter(sensors_near_row, sensors_near_row.end()),
        [](const Sensor& s) { return s.is_row_in_range(BEACON_ROW); });

    int lowest_x = sensors_near_row.begin()->get_leftmost_non_beacon_on_row(BEACON_ROW);
    int highest_x = sensors_near_row.begin()->get_rightmost_non_beacon_on_row(BEACON_ROW);
    for (const Sensor& s : sensors_near_row) {
        lowest_x = std::min(lowest_x, s.get_leftmost_non_beacon_on_row(BEACON_ROW));
        highest_x = std::max(highest_x, s.get_rightmost_non_beacon_on_row(BEACON_ROW));
    }

    int count = 0;
    for (int i = lowest_x; i <= highest_x; ++i) {
        if (std::any_of(sensors.begin(), sensors.end(), [i, BEACON_ROW](const Sensor& s) {
                return s.is_point_not_beacon({i, BEACON_ROW});
        })) {
            ++count;
        }
    }

    std::cout << count << std::endl;

    std::set<Point> points_outside_range;
    for (const Sensor& s : sensors) {
        std::set<Point> outside_s_range = s.get_points_outside_covered();
        points_outside_range.insert(outside_s_range.begin(), outside_s_range.end());
    }

    const int MAX_COORD = 4000000;
    const int MIN_COORD = 0;
    std::erase_if(points_outside_range, [MAX_COORD, MIN_COORD](const Point& p) {
        return p.first < MIN_COORD ||
            p.second < MIN_COORD ||
            p.first > MAX_COORD ||
            p.second > MAX_COORD;
    });

    Point distress;
    for (const Point& p : points_outside_range) {
        if (std::none_of(sensors.begin(), sensors.end(), [p](const Sensor& s) {
            return s.is_point_not_beacon(p);
        })) {
            distress = p;
            break;
        }
    }

    std::cout << (long long)distress.first * MAX_COORD + distress.second << std::endl;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << duration.count() << " ms" << std::endl;
}