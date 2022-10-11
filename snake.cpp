                // https://www.reddit.com/r/gamedev/comments/ptme93/making_a_game_in_c/hdy0wfu/?context=8&depth=9

                // https://thenumb.at/cpp-course/sdl2/04/04.html
                // https://lazyfoo.net/tutorials/SDL/04_key_presses/index.php

// All include files are located in /usr/include

#include <iostream>     // Located in /usr/include/c++/11. Automatically picked out by compiler
#include <map>
#include <string>
#include <SDL.h>        // Located in /usr/include/SDL2. Add this to c_cpp_properties.json first
#include <SDL_image.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Array containing list of images to cache
std::pair<std::string, std::string> images[2] = 
{
    {"Hello World", "./assets/hello_world.bmp"},
    {"Krabs", "./assets/krabs.png"}
};

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool init();
bool cacheMedia();

bool blitImage(std::string imgName, SDL_Rect* srcRect, SDL_Rect* destRect);

bool close();

class imgCache {
    std::map<std::string, SDL_Surface*> cache_;

    public:

    SDL_Surface* cacheImage(std::string imgName, std::string imgPath) {
        std::string fileType = imgPath.substr(imgPath.size() - 3);
        SDL_Surface* newSurface = NULL;
        switch((char) fileType[0]) {
            case 'j':
            case 'p':
                newSurface = IMG_Load(imgPath.c_str());
            break;
            case 'b':
                newSurface = SDL_LoadBMP(imgPath.c_str());
            break;
        }
        if (newSurface == NULL) {
            std::cout << "Unable to find image! SDL_Error:" << SDL_GetError() << std::endl;
            return NULL;
        }
        // emplace()s the pair (imgName, newSurface) to cache_.
        // The emplace() function returns a pair (iterator to new pair, true). Use pair.first to access iterator.
        // Then, use iterator->second to access the newSurface.
        return cache_.emplace(imgName, newSurface).first->second;
    }

    SDL_Surface* getRawImage(std::string imgName) {
        std::map<std::string, SDL_Surface*>::iterator i = cache_.find(imgName);
        if (i == cache_.end()) {
            std::cout << "Image " << imgName << " not found in cache!\n";
            return NULL;
        }
        return i->second;
    }

    SDL_Texture* getImage(std::string imgName) {
        return SDL_CreateTextureFromSurface(renderer, getRawImage(imgName));
    }

    void flushCache() {
        std::map<std::string, SDL_Surface*>::iterator i = cache_.begin();
        for (;i != cache_.end(); i++) {
            SDL_FreeSurface(i->second);
        }
    }

    // Class destructor
    ~imgCache() {flushCache();}

};
imgCache imageCache;

int main( int argc, char* argv[] ) {

    if (!init()) {
        std::cout << "Failed to initialise!\n";
        return 1;
    }
    if (!cacheMedia()) {
        std::cout << "Failed to cache images!\n";
        return 1;
    } 
    bool quit = false;
    SDL_Event event;
    while (!quit) {

        // Process all user inputs

        while (SDL_PollEvent(&event) != 0) {
            // SDL_PollEvent pulls one event off the event stack, and puts it into the address of event.
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        for (int i=0; i<2; i++) {
            SDL_Rect rect = {0, 0 + 100*i, 100, 100};
            blitImage(images[i].first, NULL, &rect);
        }

        SDL_RenderPresent(renderer);
    }
    

    close();
}

bool init() {

    // Initialise video component of SDL, as well as image library

    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        std::cout << "SDL could not initialize! SDL_Error:" << SDL_GetError() << std::endl;
        return false;
    }

    if ( IMG_Init( IMG_INIT_JPG | IMG_INIT_PNG ) == 0) {
        std::cout << "SDL_Img could not initialise! SDL_Error:" << SDL_GetError() << std::endl;
        return false;
    }

    // Create window and renderer at the same time
    
    if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer) < 0) {
        std::cout << "Window and renderer could not be created! SDL_Error:" << SDL_GetError() << std::endl;
        return false;
    } 
    
    return true;
}

bool cacheMedia() {
    
    // Cache images. Exit upon any error
    for (auto img : images) {
        if (imageCache.cacheImage(img.first, img.second) == NULL) {
            return false;
        }
    }

    return true;
}

bool blitImage(std::string imgName, SDL_Rect* srcRect, SDL_Rect* destRect) {
    SDL_Texture* newTexture = imageCache.getImage(imgName);
    if (newTexture == NULL) {
        return false;
    }
    SDL_RenderCopy(renderer, newTexture, srcRect, destRect);
}

bool close() {
    imageCache.flushCache();

    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyWindow(window);
    window = NULL;
    // It's a good practice to reset pointers to point to NULL when they aren't in use.
    SDL_Quit();
    return true;
}