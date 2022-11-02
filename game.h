#ifndef GAME
#define GAME

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <chrono>
#include <cstdlib>

enum class gameState {
    QUIT,
    PLAY,
    PAUSE
};

class Game {
    private:

    std::string username;
    gameState GameState;          // 0 for initialising, 1 for running, 2 for paused, 3 for stopping

    double mvtInterval;

    int snakeLength;
    std::pair<int, int> snakeHead;

    std::string snakeDirection;
    std::vector<std::string> snakeTiles;

    std::vector<std::vector<int>> board;
    int width;
    int height;

    class timers {
        private:
        std::chrono::time_point<std::chrono::system_clock> overallTimer;
        std::chrono::time_point<std::chrono::system_clock> fpsTimer;
        std::chrono::time_point<std::chrono::system_clock> mvtTimer;

        public:
        void resetOverallTimer();
        void resetMvtTimer();
        void resetFPSTimer();
        double calcOverallTimer();
        double calcMvtTimer();
        double calcFPSTimer();
    };

    timers Timer;

    int snakeUpdate();
    bool snakeHeadUpdate();
    bool snakeHeadUpdateTiles();
    bool snakeMovement();
    bool snakeTailUpdateTiles();
    bool spawnApple();

    std::string oppositeDir(std::string dir);
    std::string concatenateDirs(std::string dir1, std::string dir2);

    public:

    Game(int w, int h, double s);

    bool gameUpdate();
    int getGameScore();
    std::vector<std::pair<std::pair<int, int>, std::string>> getBoardData();
    bool snakeChangeDir(std::string d);

    void gameFPSControl();

    void gamePause();
    void gameResume();
    bool gameEnd();
    bool getGameState();

};

#endif