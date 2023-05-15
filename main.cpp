// Includes the entire std library for C++
#include <bits/stdc++.h>
using namespace std;

int n = 3; // Number of rows and cols in the n x n board

struct node {
    vector<vector<int>> state;
    int depth;
    int evaluate;

    // Comparator for nodes
    bool operator<(node const& a) const
    {
        // Put the higher f(n) on top    
        return evaluate > a.evaluate;
    }
};

void initializeDefaultPuzzle(vector<vector<int>> &board) {
    int input;
    cout << "Please enter a puzzle difficulty\n"
        << "1 = Depth 0\n"
        << "2 = Depth 2\n"
        << "3 = Depth 4\n"
        << "4 = Depth 8\n"
        << "5 = Depth 12\n"
        << "6 = Depth 16\n"
        << "7 = Depth 20\n"
        << "8 = Depth 24\n";

    cin >> input;
    switch(input) {
        case 1: // Depth = 0
            board.push_back({1,2,3}); board.push_back({4,5,6}); board.push_back({7,8,0}); break;
        case 2: // Depth = 2
            board.push_back({1,2,3}); board.push_back({4,5,6}); board.push_back({0,7,8}); break;
        case 3: // Depth = 4
            board.push_back({1,2,3}); board.push_back({5,0,6}); board.push_back({4,7,8});break;
        case 4: // Depth = 8
            board.push_back({1,3,6}); board.push_back({5,0,2}); board.push_back({4,7,8});break;
        case 5: // Depth 12
            board.push_back({1,3,6}); board.push_back({5,0,7}); board.push_back({4,8,2}); break;
        case 6: // Depth 16
            board.push_back({1,6,7}); board.push_back({5,0,3}); board.push_back({4,8,2}); break;
        case 7: // Depth 20
            board.push_back({7,1,2}); board.push_back({4,8,5}); board.push_back({6,3,0}); break;
        case 8: // Depth 24
            board.push_back({0,7,2}); board.push_back({4,6,1}); board.push_back({3,5,8}); break;
        default:
            board.push_back({1,2,3}); board.push_back({4,5,6}); board.push_back({7,8,0}); break;
    }
}

// Uniform cost heuristic, f(n) = 0
int uniformCost(vector<vector<int>>  board, vector<vector<int>>  target) {
    return 0;
}

// Misplaced tile heuristic, f(n) = number of misplaced tiles
int misplacedTile(vector<vector<int>>  board, vector<vector<int>>  target) {
    int numMisplaced = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(board[i][j] != target[i][j])
                numMisplaced++;
        }    
    }
    return numMisplaced;
}

// Manhattan distance heuristic, f(n) = total manhattan distance for each tile
int manhattan(vector<vector<int>>  board, vector<vector<int>> target) {
    int correct[9][2] = {{2,2}, {0,0}, {0,1}, {0,2}, {1,0}, {1,1}, {1,2}, {2,0}, {2,1}};
    int totalDistance = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            totalDistance += abs(correct[board[i][j]][0] - i) + abs(correct[board[i][j]][1] - j);
        }    
    }
    return totalDistance;
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

void AStarSearch(vector<vector<int>> & board, vector<vector<int>> & target, int (*heuristicFunc)(vector<vector<int>>, vector<vector<int>>)) {
    unordered_map<string, bool>  map;
    priority_queue<node> queue;

    int nodesExpanded = 0;
    int maxQueueSize = 1;

    node current;
    current.state = board;
    current.depth = 0;
    current.evaluate = heuristicFunc(current.state, target);
    queue.push(current);

    while(!queue.empty()) {
        current = queue.top();
        queue.pop();

        // Skip current if board is a repeat
        if(isRepeat(current.state, map))
            continue;

        // Return if board is the target
        if(current.state == target) {
            cout << "\nSolution found at depth " << current.depth << "\n";
            cout << "Number of nodes expanded: " << nodesExpanded << "\n";
            cout << "Max queue size: " << maxQueueSize << "\n";
            return;
        }

        nodesExpanded++;

        // Add neighbors to queue
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if(current.state[i][j] == 0) {
                    node next;
                    // Add up to queue
                    if(i > 0) {
                        next.state = current.state;
                        swap(next.state[i-1][j], next.state[i][j]);
                        next.depth = current.depth + 1;
                        next.evaluate = next.depth + heuristicFunc(next.state, target);
                        queue.push(next);
                    }
                    // Add down to queue
                    if(i < n - 1) {
                        next.state = current.state;
                        swap(next.state[i+1][j], next.state[i][j]);
                        next.depth = current.depth + 1;
                        next.evaluate = next.depth + heuristicFunc(next.state, target);
                        queue.push(next);
                    }
                    // Add left to queue
                    if(j > 0) {
                        next.state = current.state;
                        swap(next.state[i][j - 1], next.state[i][j]);
                        next.depth = current.depth + 1;
                        next.evaluate = next.depth + heuristicFunc(next.state, target);
                        queue.push(next);
                    }
                    // Add right to queue
                    if(j < n - 1) {
                        next.state = current.state;
                        swap(next.state[i][j + 1], next.state[i][j]);
                        next.depth = current.depth + 1;
                        next.evaluate = next.depth + heuristicFunc(next.state, target);
                        queue.push(next);
                    }
                }
            }    
        }
        if(queue.size() > maxQueueSize)
            maxQueueSize = queue.size();
    }
    cout << "Failure!";
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

    cout << "Choose your heuristic. Type '1' for Uniform Cost, '2' for Misplaced Tile, or '3' for Manhattan Distance\n";
    cin >> input;

    // Recording the timestamp at the start of the code
    auto beg = chrono::high_resolution_clock::now();
    switch(input) {
        case 1:
            AStarSearch(board, target, &uniformCost);
            break;
        case 2:
            AStarSearch(board, target, &misplacedTile);
            break;
        case 3:
            AStarSearch(board, target, &manhattan);
            break;
        default:
            "Error: invalid input";
            break;
    }
    auto end = chrono::high_resolution_clock::now();

    // Displaying the elapsed time
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - beg);
    std::cout << "Elapsed Time: " << duration.count() << " milliseconds";

    // cout << "\n";
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cout << board[i][j] << " ";
    //     }    
    //     cout << "\n";
    // }

    return 0;
}