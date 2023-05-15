// Includes the entire std library for C++
#include <bits/stdc++.h>
using namespace std;

int n = 3; // Number of rows and cols in the n x n board

void initializeDefaultPuzzle(vector<vector<int>> &board) {
    int input;
    cout << "Please enter a puzzle difficulty\n"
        << "1 = Trivial\n"
        << "2 = Very Easy\n"
        << "3 = Easy\n"
        << "4 = Medium\n"
        << "5 = Hard\n";

    cin >> input;
    switch(input) {
        case 1:
            board.push_back({1,2,3});
            board.push_back({4,5,6});
            board.push_back({7,8,0});
            break;
        case 2:
            board.push_back({1,2,3});
            board.push_back({4,5,6});
            board.push_back({7,0,8});
        case 3:
            board.push_back({1,2,0});
            board.push_back({4,5,3});
            board.push_back({7,8,6});
            break;
        case 4:
            board.push_back({0,1,2});
            board.push_back({4,5,3});
            board.push_back({7,8,6});
            break;
        case 5:
            board.push_back({8,7,1});
            board.push_back({6,0,2});
            board.push_back({5,4,3});
            break;
        default:
            board.push_back({1,2,3});
            board.push_back({4,5,6});
            board.push_back({7,8,0});
            break;
    }

}

bool isRepeat(vector<vector<int>> & board, unordered_map<string, bool> & map) {
    string key = "";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            key = key + to_string(board[i][j]);
        }    
    }

    if(map.find(key) != map.end()) {
        return true; // Board is a repeat
    }
    else {
        map[key] = 1; // Board is not repeat. Add to map.
        return false;
    }
}

void uniformCostSearch(vector<vector<int>> & board, unordered_map<string, bool> & map, queue<vector<vector<int>>> & queue) {
    
}

void AStarMisplacedTile(vector<vector<int>> board) {

}

void AStarManhattan(vector<vector<int>> board) {

}

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    vector<vector<int>> board; // 8 puzzle board
    unordered_map<string, bool> map;

    cout << "8-Puzzle Solver. Type '1' to use a default puzzle, or '2' to create your own.\n";
    
    int input;
    cin >> input;

    if(input == 1) {
        initializeDefaultPuzzle(board);
    }
    else if (input == 2) {
        cout << "Enter your puzzle, using a 0 to represent the blank.\n";
        for(int i = 0; i < n; i++) {
            vector<int> row;
            cout << "Enter row " << i + 1 << ": ";
            for(int j = 0; j < n; j++) {
                cin >> input;
                row.push_back(input);
            }
            board.push_back(row);
        }
    }

    cout << "\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << board[i][j] << " ";
        }    
        cout << "\n";
    }

    return 0;
}