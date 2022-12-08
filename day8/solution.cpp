#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ifstream input("input.txt");

    string row;
    vector<vector<int>> tree_heights;
    while (input >> row) {
        tree_heights.push_back(vector<int>());
        for (char c : row) {
            tree_heights.back().push_back(c - '0');
        }
    }

    int grid_height = tree_heights.size();
    int grid_length = tree_heights.back().size();
    int visible_trees = 2 * grid_height + 2 * grid_length - 4;

    for (int i = 1; i < grid_height - 1; ++i) {
        for (int j = 1; j < grid_length - 1; ++j) {
            int curr_height = tree_heights[i][j];
            bool left = true, right = true, up = true, down = true;
            
            for (int k = 0; k < j; ++k) {
                if (tree_heights[i][k] >= curr_height) {
                    left = false;
                }
            }
            for (int k = j + 1; k < grid_length; ++k) {
                if (tree_heights[i][k] >= curr_height) {
                    right = false;
                }
            }
            for (int k = 0; k < i; ++k) {
                if (tree_heights[k][j] >= curr_height) {
                    up = false;
                }
            }
            for (int k = i + 1; k < grid_height; ++k) {
                if (tree_heights[k][j] >= curr_height) {
                    down = false;
                }
            }

            if (up || down || left || right) {
                ++visible_trees;
            }
        }
    }

    cout << visible_trees << endl;

    int max_scenic = 0;
    for (int i = 1; i < grid_height - 1; ++i) {
        for (int j = 1; j < grid_length - 1; ++j) {
            int curr_height = tree_heights[i][j];
            int left = 0, right = 0, up = 0, down = 0;
            for (int k = j - 1; k >= 0; --k) {
                ++left;
                if (tree_heights[i][k] >= curr_height) {
                    break;
                }
            }
            for (int k = j + 1; k < grid_length; ++k) {
                ++right;
                if (tree_heights[i][k] >= curr_height) {
                    break;
                }
            }
            for (int k = i - 1; k >= 0; --k) {
                ++up;
                if (tree_heights[k][j] >= curr_height) {
                    break;
                }
            }
            for (int k = i + 1; k < grid_height; ++k) {
                ++down;
                if (tree_heights[k][j] >= curr_height) {
                    break;
                }
            }

            int scenic = left * right * up * down;
            if (scenic > max_scenic) {
                max_scenic = scenic;
            }
        }
    }

    cout << max_scenic << endl;
}