#include <iostream>
#include <map>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>

#include "renderer.h"
#include "game.h"
#include "events.h"
#include "attributes.h"
#include "graphics.h"

        // Spritemap taken from https://rembound.com/articles/creating-a-snake-game-tutorial-with-html5

int main( int argc, char* argv[] ) {

    renderEngine renderer;
    Game game(WIDTH, HEIGHT, 0.3);

    if (!renderer.rendererStart()) {
        return 1;
    }

    while (game.getGameState()) {

        // Process all user inputs
        std::vector<events> eventQueue = processEvents();
        if (!eventQueue.empty()) {
            if (eventQueue[0] == events::QUIT) {
                game.gameEnd();
                continue;
            }
        }

        // Blits the background
        drawBackground(renderer);

        for (events event : eventQueue) {
            switch(event) {
                case events::KEY_UP:
                    game.snakeChangeDir("N");
                break;
                case events::KEY_RIGHT:
                    game.snakeChangeDir("E");
                break;
                case events::KEY_DOWN:
                    game.snakeChangeDir("S");
                break;
                case events::KEY_LEFT:
                    game.snakeChangeDir("W");
                break;
            }
        }

        // Updates the game
        game.gameUpdate();

        // Blits all game sprites
        std::vector<std::pair<std::pair<int, int>, std::string>> boardData = game.getBoardData();
        drawSprites(renderer, boardData);

        // Refreshes the screen
        renderer.rendererUpdate();

        game.gameFPSControl();
    }

    std::cout << "Stopping game...\n";

    renderer.rendererStop();
    
}