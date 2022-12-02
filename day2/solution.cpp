#include <fstream>
#include <iostream>
#include <map>
#include <string>

using std::string;
using std::map;
using std::ifstream;
using std::cout;
using std::endl;

int main() {

    const int ROCK_PTS = 1;
    const int PAPER_PTS = 2;
    const int SCISSOR_PTS = 3;
    const int LOSE_PTS = 0;
    const int TIE_PTS = 3;
    const int WIN_PTS = 6;
    
    map<string, int> game_pts{
        { "AX", TIE_PTS },
        { "AY", WIN_PTS },
        { "AZ", LOSE_PTS },
        
        { "BX", LOSE_PTS },
        { "BY", TIE_PTS },
        { "BZ", WIN_PTS },

        { "CX", WIN_PTS },
        { "CY", LOSE_PTS },
        { "CZ", TIE_PTS },

        { "X", LOSE_PTS },
        { "Y", TIE_PTS },
        { "Z", WIN_PTS }
    };

    map<string, int> choice_pts{
        { "X", ROCK_PTS },
        { "Y", PAPER_PTS },
        { "Z", SCISSOR_PTS },

        { "A", ROCK_PTS },
        { "B", PAPER_PTS },
        { "C", SCISSOR_PTS }
    };

    map<string, string> choice_map{
        { "AX", "C" },
        { "AY", "A" },
        { "AZ", "B" },

        { "BX", "A" },
        { "BY", "B" },
        { "BZ", "C" },

        { "CX", "B" },
        { "CY", "C" },
        { "CZ", "A" }
    };

    ifstream input("input.txt");

    int total_points_pt1 = 0;
    int total_points_pt2 = 0;
    string opp_move, result;
    while (input >> opp_move >> result) {
        total_points_pt1 += game_pts[opp_move + result] + choice_pts[result];

        string my_move = choice_map[opp_move + result];
        total_points_pt2 += game_pts[result] + choice_pts[my_move];
    }

    cout << total_points_pt1 << endl;
    cout << total_points_pt2 << endl;
}