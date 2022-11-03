#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <chrono>
#include <ctime>
#include <cstdlib>

#include "game.h"
#include "attributes.h"

void Game::timers::resetOverallTimer() {
    overallTimer = std::chrono::system_clock::now();
}
void Game::timers::resetMvtTimer() {
    mvtTimer = std::chrono::system_clock::now();
}
void Game::timers::resetFPSTimer() {
    fpsTimer = std::chrono::system_clock::now();
}

double Game::timers::calcOverallTimer() {
    std::chrono::time_point<std::chrono::system_clock> timeNow = std::chrono::system_clock::now();
    std::chrono::duration<double> duration = timeNow - overallTimer;
    return duration.count();
}
double Game::timers::calcMvtTimer() {
    std::chrono::time_point<std::chrono::system_clock> timeNow = std::chrono::system_clock::now();
    std::chrono::duration<double> duration = timeNow - mvtTimer;
    return duration.count();
}
double Game::timers::calcFPSTimer() {
    std::chrono::time_point<std::chrono::system_clock> timeNow = std::chrono::system_clock::now();
    std::chrono::duration<double> duration = timeNow - fpsTimer;
    return duration.count();
}

int Game::snakeUpdate() {

    snakeHeadUpdate();

    if (snakeHead.first < 0) {
        std::cout << "Crashed into top wall!\n";
        return 1;
    }
    if (snakeHead.second >= width) {
        std::cout << "Crashed into right wall!\n";
        return 2;
    }
    if (snakeHead.first >= height) {
        std::cout << "Crashed into bottom wall!\n";
        return 3;
    }
    if (snakeHead.second < 0) {
        std::cout << "Crashed into left wall!\n";
        return 4;
    }

    int c = board[snakeHead.first][snakeHead.second];
    if (c > 0) {
        std::cout << "Crashed into yourself!\n";
        return 5;
    }

    snakeHeadUpdateTiles();

    if (c == -1) {
        std::cout << "Ate an apple!\n";
        snakeLength += 1;
        spawnApple();
    }

    if (c == 0) {
        snakeMovement();
        snakeTailUpdateTiles();
    }

    board[snakeHead.first][snakeHead.second] = snakeLength;

    return 0;
}

bool Game::snakeHeadUpdate() {
    if (snakeDirection == "N") {
        snakeHead.first -= 1;
    }
    if (snakeDirection == "S") {
        snakeHead.first += 1;
    }
    if (snakeDirection == "E") {
        snakeHead.second += 1;
    }
    if (snakeDirection == "W") {
        snakeHead.second -= 1;
    }
}

bool Game::snakeHeadUpdateTiles() {
    std::string oldHeadTile = snakeTiles[0];

    std::string newHeadTile = oppositeDir(snakeDirection);

    std::string newSecondTile = concatenateDirs(oldHeadTile, snakeDirection);
    snakeTiles[0] = newSecondTile;
    snakeTiles.insert(snakeTiles.begin(), newHeadTile);

}

bool Game::snakeMovement() {
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            if (board[i][j] > 0) {
                board[i][j] -= 1;
            }
        }
    }
}

bool Game::snakeTailUpdateTiles() {

    std::string c = oppositeDir(snakeTiles.rbegin()[0]);
    int x = snakeTiles.rbegin()[1].find(c);
    std::string newEnd;
    if (x == 0) {
        newEnd = snakeTiles.rbegin()[1].substr(1);
    }
    if (x == 1) {
        newEnd = snakeTiles.rbegin()[1].substr(0, 1);
    }
    if (newEnd.empty()) {
        std::cout << "Error in updating snakeTiles!\n";
        return false;
    }
    snakeTiles.pop_back();
    snakeTiles.rbegin()[0] = newEnd;
    return true;

}

bool Game::spawnApple() {
    std::vector<std::pair<int, int>> v;
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            if (board[i][j] == 0) {
                v.emplace_back(std::make_pair(i, j));
            }
        }
    }

    int t = rand() % v.size();
    std::pair<int, int> spawnCoords = v[t];
    board[spawnCoords.first][spawnCoords.second] = -1;

    return true;
}

std::string Game::concatenateDirs(std::string dir1, std::string dir2) {
    std::string outputs[6] = {"NS", "EW", "NE", "NW", "SE", "SW"};
    for (std::string e : outputs) {
        if ((e.find(dir1) != std::string::npos) and (e.find(dir2) != std::string::npos)) {
            return e;
        }
    }
}

std::string Game::oppositeDir(std::string dir) {
    if (dir == "N") {
        return "S";
    }
    if (dir == "S") {
        return "N";
    }
    if (dir == "E") {
        return "W";
    }
    if (dir == "W") {
        return "E";
    }
}

Game::Game(int w, int h, double s) {
    GameState = gameState::PLAY;
    width = w;
    height = h;

    snakeLength = 2;
    snakeDirection = "E";
    mvtInterval = s;
    Timer.resetMvtTimer();
    Timer.resetOverallTimer();
    Timer.resetFPSTimer();

    // Initialise the board

    for (int i=0; i<h; i++) {
        std::vector<int> v(w, 0);
        board.emplace_back(v);
    }

    snakeHead = std::make_pair(h/2, w/2);
    // Place the snake in its starting position
    board[snakeHead.first][snakeHead.second] = 2;
    board[snakeHead.first][snakeHead.second - 1] = 1;

    snakeTiles.emplace_back("W");
    snakeTiles.emplace_back("E");

    srand(time(NULL));
    spawnApple();
}

bool Game::gameUpdate() {
    if (GameState == gameState::PLAY) {

        if (Timer.calcMvtTimer() > mvtInterval) {
            
            if (snakeUpdate()) {
                // End game
            }

            Timer.resetMvtTimer();
        }

    }
}

int Game::getGameScore() {
    return snakeLength - 2;
}

std::vector<std::pair<std::pair<int, int>, std::string>> Game::getBoardData() {

    // [Data for head tile, data for second tile, data for third tile, ..., data for last tile, data for apple]
    // Each tile has data [(y-coordinate, x-coordinate), tile direction]

    std::vector<std::pair<std::pair<int, int>, std::string>> returnVec(snakeLength+1, std::make_pair(std::make_pair(-1, -1), ""));
    
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            if (board[i][j] > 0) {
                int c = snakeLength - board[i][j];
                returnVec[c].first = std::make_pair(i, j);
                returnVec[c].second = snakeTiles[c];
            }
            if (board[i][j] == -1) {
                returnVec[snakeLength].first = std::make_pair(i, j);
                returnVec[snakeLength].second = "apple";
            }
        }
    }

    for (int i=0; i<snakeLength; i++) {
        if (returnVec[i].second.length() == 0) {
            std::cout << "Error in obtaining snake data!\n";
        }
    }

    return returnVec;
}

bool Game::snakeChangeDir(std::string d) {
    if (snakeTiles[0] != d) {
        snakeDirection = d;
    }
}

void Game::gamePause() {
    GameState = gameState::PAUSE;
}

void Game::gameResume() {
    GameState = gameState::PLAY;
    Timer.resetMvtTimer();
}

bool Game::gameEnd() {
    GameState = gameState::QUIT;
    // To implement: pass game data to highscore reader
}

bool Game::getGameState() {
    if (GameState == gameState::QUIT) {
        return false;
    } else {
        return true;
    }
}

void Game::gameFPSControl() {
    while (Timer.calcFPSTimer() < SPF) {

    }
    std::cout << Timer.calcFPSTimer() << std::endl;
    Timer.resetFPSTimer();
}