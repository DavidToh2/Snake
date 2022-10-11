/* Problem: Simulate a Snake game.
You are given a series of inputs representing a sequence of in-game events.

The first line consists of four integers r, c, y, x. The board is c columns by r rows large, and the snake's starting position is column x and row y. Take the bottom-left cell to be (0, 0). Assume the snake starts facing right.

Each of the following lines could be one of five possible inputs:
- F: move forward one unit.
- L: turn left. (No movement.)
- R: turn right. (No movement.)
- S y x: spawn a fruit at the cell in row y and column x;
- E: (manually) end game.

Your output should consist of two parts:
- "DEAD" if the player dies before the end of the sequence; "ALIVE" if the player is still alive
- followed by the player's score. */

#include <vector>
#include <map>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;

void gameEnding(int status, int score) {
    switch(status) {
        case 0:
            cout << "ALIVE\n";
        break;
        case 1:
            cout << "DEAD\n";
        break;
    }
    cout << "Score: " << to_string(score);
}

int main() {

    int c, r;
    int head[2];
    cin >> r >> c >> head[0] >> head[1];

        // Intiailise the board with "new".
        // board is a pointer to an array of pointers, representing the rows.
        // Each row (already initialised as a pointer) points to an array of integers.

        // Alternatively, just use vectors...but then this is just revision

        // Access row y and column x using board[y][x]

    int** board = new int*[r];
    for (int i=0; i<r; i++) {
        board[i] = new int[c];
        for (int j=0; j<c; j++) {
            board[i][j] = 0;
        }
    }

    board[head[0]][head[1]] = 1;
    int direction = 1;      // 0 = top, 1 = left, 2 = bottom, 3 = right
    int length = 1;

        // Processing each line of input individually 
    cin.ignore();
    string line, t;

    while (getline(cin, line)) {
        
        vector<string> s;

            // Load input into buffer
        istringstream ss(line);
        while (ss >> t) {
            s.emplace_back(t);
        }

            // Detect type of input

        if (s[0][0] == 'E') {
            cout << "Game manually ended!\n";
            break;
        }

        switch(s[0][0]) {

                // Snake moves forward 

            case 'F':

                switch(direction) {         // Update position of head
                    case 0:
                        head[0] += 1;
                        if (head[0] >= r) {
                            cout << "Crashed into the top wall!\n";
                            gameEnding(1, length);
                            return 1;
                        } 
                    break;
                    case 1:
                        head[1] += 1;
                        if (head[1] >= c) {
                            cout << "Crashed into the right wall!\n";
                            gameEnding(1, length);
                            return 1;
                        }
                    break;
                    case 2:
                        head[0] -= 1;
                        if (head[0] < 0) {
                            cout << "Crashed into the bottom wall!\n";
                            gameEnding(1, length);
                            return 1;
                        }
                    break;
                    case 3:
                        head[1] -= 1;
                        if (head[1] < 0) {
                            cout << "Crashed into the left wall!\n";
                            gameEnding(1, length);
                            return 1;
                        }
                    break;
                }

                if (board[head[0]][head[1]] > 0) {
                    cout << "Crashed into yourself!\n";
                    gameEnding(1, length);
                    return 1;
                } else if (board[head[0]][head[1]] == -1) {
                    cout << "Ate a fruit!\n";
                    length += 1;
                } else {
                    for (int i = 0; i < r; i++) {           // Subtract 1 from all cells
                        for (int j = 0; j < c; j++) {
                            if (board[i][j] > 0) {
                                board[i][j] -= 1;
                            }
                        }
                    }
                }
                board[head[0]][head[1]] = length;
                cout << "Coordinates are now row: " << to_string(head[0]) << " and column: " << to_string(head[1]) << " and length is " << to_string(length) << "\n";
            break;
            case 'L':
                direction = (direction - 1) % 4;
            break;
            case 'R':
                direction = (direction + 1) % 4;
            break;
            case 'S':
                int nr = stoi(s[1]), nc = stoi(s[2]);
                board[nr][nc] = -1;
            break;
        }
    }

        // Clean up memory
    
    for (int i=0; i<r; i++) {
        delete [] board[i];
    }
    delete [] board;

    gameEnding(0, length);

    return 0;
}