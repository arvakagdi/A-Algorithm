/*
Reading a file and changing its data and priniting it in a speciffic format
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using std::cout;
using std::ifstream;
using std::string;
using std::vector;
using std::istringstream;

enum class State {kEmpty, kObstacle};    //to  change the printing formal and add states to the board

vector<State> ParseLine(string s) {
    istringstream mystring(s);

    int n;
    char c;
    vector<State> myvec;
    while (mystring >> n >> c && c == ',') {
        if (n == 0) {
            myvec.push_back(State::kEmpty);
        }
        else {
            myvec.push_back(State::kObstacle);
        }

    }

    return myvec;
}


vector<vector<State>> ReadBoardFile(string path) {
    ifstream myfile(path);
    vector<vector<State>> board{};
    if (myfile) {
        string line;
        vector<State> row{};
        while (getline(myfile, line)) {
            row = ParseLine(line);
            board.push_back(row);
        }
    }

    return board;
}

string CellString(State cell) {
    if (cell == State::kObstacle) {
        return "⛰️";
    }
    else {
        return "0";
    }
}


void PrintBoard(const vector<vector<State>> board) {
    for (auto i :board) {
        for (auto j:i){
            cout << CellString(j);
    }
        cout << "\n";
    }
}

int main() {
    auto board = ReadBoardFile("1.board");
    PrintBoard(board);
}