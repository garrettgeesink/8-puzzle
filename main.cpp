// Includes the entire std library for C++
#include <bits/stdc++.h>
using namespace std;

int n = 3; // Number of rows and cols in the n x n board

struct node {
    vector<vector<int>> state;
    int depth;
};

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
            break;
        case 3:
            board.push_back({1,2,3});
            board.push_back({5,0,6});
            board.push_back({4,7,8});
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

void uniformCostSearch(vector<vector<int>> & board, vector<vector<int>> & target) {
    unordered_map<string, bool>  map;
    queue<node> queue;

    node current;
    current.state = board;
    current.depth = 0;
    queue.push(current);

    while(!queue.empty()) {
        current = queue.front();
        queue.pop();

        // Skip current if board is a repeat
        if(isRepeat(current.state, map))
            continue;

        // Return if board is the target
        if(current.state == target) {
            cout << "Target found at depth " << current.depth;
            break;
        }

        // Add neighbors to queue
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if(board[i][j] == 0) {
                    node next;
                    // Add up to queue
                    if(i > 0) {
                        next.state = current.state;
                        swap(next.state[i-1][j], next.state[i][j]);
                        next.depth = current.depth + 1;
                        queue.push(next);
                    }
                    // Add down to queue
                    if(i < n - 1) {
                        next.state = current.state;
                        swap(next.state[i+1][j], next.state[i][j]);
                        next.depth = current.depth + 1;
                        queue.push(next);
                    }
                    // Add left to queue
                    if(j > 0) {
                        next.state = current.state;
                        swap(next.state[i][j - 1], next.state[i][j]);
                        next.depth = current.depth + 1;
                        queue.push(next);
                    }
                    // Add right to queue
                    if(j < n - 1) {
                        next.state = current.state;
                        swap(next.state[i][j + 1], next.state[i][j]);
                        next.depth = current.depth + 1;
                        queue.push(next);
                    }
                }
            }    
        }
        
    }
}

void AStarMisplacedTile(vector<vector<int>> board) {

}

void AStarManhattan(vector<vector<int>> board) {

}

int main() {
    // Fast IO
    // ios_base::sync_with_stdio(false);
    // cin.tie(0);

    vector<vector<int>> target = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    vector<vector<int>> board; // 8 puzzle board

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

    uniformCostSearch(board, target);

    cout << "\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << board[i][j] << " ";
        }    
        cout << "\n";
    }

    return 0;
}