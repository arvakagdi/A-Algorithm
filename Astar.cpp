/*
Implementation of an A* Algorithm
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using std::cout;
using std::ifstream;
using std::string;
using std::vector;
using std::istringstream;

enum class State { kEmpty, kObstacle, kClosed, kPath, kStart, kFinish};    //to  change the printing formal and add states to the board
const int delta[4][2]{ {-1, 0}, {0, -1}, {1, 0}, {0, 1} };   // directional deltas

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

// return what needs to be printed
string CellString(State cell) {
    switch (cell) {
    case State::kObstacle: return "⛰️   ";
    case State::kPath: return "🚗   ";
    case State::kFinish: return "🏁   ";
    case State::kStart: return"🚦   ";
    default: return "0   ";
    }
}



bool Compare(vector<int>a, vector<int>b) {
    int f1 = a[2] + a[3];
    int f2 = b[2] + b[3];

    return f1 > f2;
}


/**
 * Sort the two-dimensional vector of ints in descending order.
 */
void CellSort(vector<vector<int>>* v) {
    std::sort(v->begin(), v->end(), Compare);
}

// Calculate the manhattan distance
int Hueristic(int x1, int y1, int x2, int y2 ) {
    return abs(x2 - x1) +  abs(y2 - y1);

}

/**
 * Check that a cell is valid: on the grid, not an obstacle, and clear.
 */
bool CheckValidCell(int x, int y, vector<vector<State>>& grid) {
    bool on_grid_x = (x >= 0 && x < grid.size());
    bool on_grid_y = (y >= 0 && y < grid[0].size());
    if (on_grid_x && on_grid_y)
        return grid[x][y] == State::kEmpty;
    return false;
}

/**
 * Add a node to the open list and mark it as open.
 */
void AddToOpen(int x, int y, int g, int h, vector<vector<int>> &openlist, vector<vector<State>> &grid) {
    vector<int> node = { x,y,g,h };
    openlist.push_back(node);
    grid[x][y] = State::kClosed;

}

/**
 * Expand current nodes's neighbors and add them to the open list.
 */
void ExpandNeighbors(const vector<int>& curr_node, int goal[2], vector<vector<int>>& Open, vector<vector<State>>& grid) {
    int x = curr_node[0];     //current node
    int y = curr_node[1];
    int g = curr_node[2];

    for (auto i : delta) {
        int x2 = x + i[0];      //find neighbours
        int y2 = y + i[1];


        if (CheckValidCell(x2, y2, grid)) {     //if valid cell
            int g2 = g + 1;
            int h2 = Hueristic(x2, y2, goal[0], goal[1]);
            AddToOpen(x2, y2, g2, h2, Open, grid);       //Add to open list and addtoopen function marks it closed
        }
    }
}


/**
 * Implementation of A* search algorithm
 */
vector<vector<State>> Search(vector<vector<State>>& board, int start[2], int goal[2]) {
    vector<vector<int>> open{};     // Create the vector of open nodes.
    // Initialize the starting node.
    int x = start[0];
    int y = start[1];

    int g = 0;
    int h = Hueristic(x, y, goal[0], goal[1]);
    AddToOpen(x, y, g, h, open, board);

    while (open.size() > 0) {
        CellSort(&open);
        vector<int> current_node = open.back();
        open.pop_back();
        int x = current_node[0];
        int y = current_node[1];
        board[x][y] = State::kPath;

        if (x == goal[0] && y == goal[1]) {     //if curr_node is goal node
            board[x][y] == State::kFinish;
            return board;
        }

        if (x == start[0] && y == start[1]) {
            board[x][y] = State::kStart;
        }
            // If we're not done, expand search to current node's neighbors.
         ExpandNeighbors(current_node, goal, open, board);
        
    }
        // We've run out of new nodes to explore and haven't found a path.
        cout << "No path found!" << "\n";
        return std::vector<vector<State>>{};
}

void PrintBoard(const vector<vector<State>> board) {
    for (auto i : board) {
        for (auto j : i) {
            cout << CellString(j);
        }
        cout << "\n";
    }
}

int main() {
    int init[2]{ 0, 0 };
    int goal[2]{ 4, 5 };

    auto board = ReadBoardFile("1.board");

    auto solution = Search(board, init, goal);
    PrintBoard(solution);
}