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

    map<string, int> game_pts_pt1{
        { "AX", ROCK_PTS + TIE_PTS },
        { "AY", PAPER_PTS + WIN_PTS },
        { "AZ", SCISSOR_PTS + LOSE_PTS },
        
        { "BX", ROCK_PTS + LOSE_PTS },
        { "BY", PAPER_PTS + TIE_PTS },
        { "BZ", SCISSOR_PTS + WIN_PTS },

        { "CX", ROCK_PTS + WIN_PTS },
        { "CY", PAPER_PTS + LOSE_PTS },
        { "CZ", SCISSOR_PTS + TIE_PTS },
    };

    map<string, int> game_pts_pt2{
        { "AX", LOSE_PTS + SCISSOR_PTS },
        { "AY", TIE_PTS + ROCK_PTS },
        { "AZ", WIN_PTS + PAPER_PTS },
        
        { "BX", LOSE_PTS + ROCK_PTS },
        { "BY", TIE_PTS + PAPER_PTS },
        { "BZ", WIN_PTS + SCISSOR_PTS },

        { "CX", LOSE_PTS + PAPER_PTS },
        { "CY", TIE_PTS + SCISSOR_PTS },
        { "CZ", WIN_PTS + ROCK_PTS },
    };

    ifstream input("input.txt");

    int total_points_pt1 = 0;
    int total_points_pt2 = 0;
    string opp_move, result;
    while (input >> opp_move >> result) {
        total_points_pt1 += game_pts_pt1[opp_move + result];
        total_points_pt2 += game_pts_pt2[opp_move + result];
    }

    cout << total_points_pt1 << endl;
    cout << total_points_pt2 << endl;
}