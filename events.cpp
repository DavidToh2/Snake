#include <iostream>
#include <map>
#include <vector>
#include <SDL.h>
#include "attributes.h"

std::vector<events> processEvents() {

    SDL_Event event;
    std::vector<events> output;

    while (SDL_PollEvent(&event) != 0) {
        // SDL_PollEvent pulls one event off the event stack, and puts it into the address of event.
        if (event.type == SDL_QUIT) {
            output.emplace_back(events::QUIT);
            return output;
        }
    }

    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);

    if (keyboardState[SDL_SCANCODE_Q]) {
        output.emplace_back(events::QUIT);
        return output;
    }
    if (keyboardState[SDL_SCANCODE_P]) {
        output.emplace_back(events::PAUSE);
    }
    if (keyboardState[SDL_SCANCODE_UP]) {
        output.emplace_back(events::KEY_UP);
    }
    if (keyboardState[SDL_SCANCODE_DOWN]) {
        output.emplace_back(events::KEY_DOWN);
    }
    if (keyboardState[SDL_SCANCODE_LEFT]) {
        output.emplace_back(events::KEY_LEFT);
    }
    if (keyboardState[SDL_SCANCODE_RIGHT]) {
        output.emplace_back(events::KEY_RIGHT);
    }

    return output;
}