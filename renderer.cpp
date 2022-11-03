                // https://www.reddit.com/r/gamedev/comments/ptme93/making_a_game_in_c/hdy0wfu/?context=8&depth=9

                // https://thenumb.at/cpp-course/sdl2/04/04.html
                // https://lazyfoo.net/tutorials/SDL/04_key_presses/index.php

                // https://gameprogrammingpatterns.com/contents.html

// All include files are located in /usr/include

#include <iostream>     // Located in /usr/include/c++/11. Automatically picked out by compiler
#include <map>
#include <string>
#include <vector>
#include <SDL.h>        // Located in /usr/include/SDL2. Add this to c_cpp_properties.json first
#include <SDL_image.h>
#include <mutex>

#include "renderer.h"
#include "attributes.h"

                        // IMAGE CACHE MEMBER FUNCTION DEFINITIONS

std::mutex mtx;

SDL_Surface* renderEngine::imgCache::loadImageIntoMemory(std::string imgPath) {
    std::string fileType = imgPath.substr(imgPath.size() - 3);
    std::cout << fileType[0] << std::endl;
    SDL_Surface* newSurface = NULL;
    switch(fileType[0]) {
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
    return newSurface;
}

bool renderEngine::imgCache::cacheImage(std::string imgName, std::string imgPath) {
    SDL_Surface* newSurface = loadImageIntoMemory(imgPath);
    if (newSurface == NULL) {
        return false;
    }
    // emplace()s the pair (imgName, newSurface) to cache_.
    // The emplace() function returns a pair (iterator to new pair, true). Use pair.first to access iterator.
    // Then, use iterator->second to access the newSurface.
    cache_.insert({imgName, newSurface});
    return true;
}

bool renderEngine::imgCache::cacheImageMap(std::vector<std::string> imgNameList, std::string imgMapPath, std::vector<SDL_Rect> rectList) {
    SDL_Surface* mapSurface = loadImageIntoMemory(imgMapPath);
    if (mapSurface == NULL) {
        return false;
    }
    int i = 0;
    for (SDL_Rect rect : rectList) {
        SDL_Surface* newSurface = SDL_CreateRGBSurface(0, rect.w, rect.h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

        SDL_BlitSurface(mapSurface, &rect, newSurface, NULL);

        if (newSurface == NULL) {
            std::cout << "Failed to copy spritemap section!\n";
            return false;
        }

        // cache_.insert({imgNameList[i], newSurface});
        mtx.lock();
        cache_[imgNameList[i]] = newSurface;
        mtx.unlock();

        i++;
    }

    SDL_FreeSurface(mapSurface);
    return true;
}

SDL_Surface* renderEngine::imgCache::getRawImage(std::string imgName) {
    std::map<std::string, SDL_Surface*>::iterator i = cache_.find(imgName);
    if (i == cache_.end()) {
        std::cout << "Image " << imgName << " not found in cache!\n";
        return NULL;
    }
    return i->second;
}

SDL_Texture* renderEngine::imgCache::getImage(std::string imgName, SDL_Renderer* targetRenderer) {
    return SDL_CreateTextureFromSurface(targetRenderer, getRawImage(imgName));
    // Note: SDL_Image has an IMG_LoadTexture() function that directly loads images into SDL_Textures.
    // The separation between surface and texture is kept here to allow for potential future optimisation.
}

void renderEngine::imgCache::flushCache() {
    for (std::map<std::string, SDL_Surface*>::iterator i = cache_.begin(); i != cache_.end(); i++) {
        SDL_FreeSurface(i->second);
    }
}

        // Class destructor. 
        // The renderer destructor is called when SDL_Quit() is called. This, in turn, calls the imageCache destructor.
        // This means that flushCache() is called again, leading to a segfault.
// renderEngine::imgCache::~imgCache() {flushCache();}

            ///////////////////////////////////////////////
            // RENDER ENGINE MEMBER FUNCTION DEFINITIONS //
            ///////////////////////////////////////////////

renderEngine::renderEngine() {
    window = NULL;
    renderer = NULL;
}

bool renderEngine::rendererInit() {

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

bool renderEngine::cacheMedia() {
    // Cache images from spriteList in attributes.cpp. Exit upon any error

    for (auto it1 = spriteList.begin(); it1 != spriteList.end(); it1++) {
        // Iterate over each spritemap
        std::vector<std::string> imgNameList;
        std::vector<SDL_Rect> rectList;
        std::string imgPath = "./assets/" + it1->first;

        for (auto it2 = it1->second.begin(); it2 != it1->second.end(); it2++) {
            imgNameList.emplace_back(it2->first);
            SDL_Rect coordRect;
            std::vector<int> coords = it2->second;
            if (coords.size() != 4) {
                std::cout << "Error in initialising spriteList coordinates: coord tuple not 4 elements long!\n";
                return false;
            }
            coordRect.x = coords[0];
            coordRect.y = coords[1];
            coordRect.w = coords[2];
            coordRect.h = coords[3];
            rectList.emplace_back(coordRect);
        }
        if (!(imageCache.cacheImageMap(imgNameList, imgPath, rectList))) {
            return false;
        } else {
            // std::cout << "Finished getting media from " << imgPath << std::endl;
        }
    }

    return true;
}

bool renderEngine::rendererStart() {
    if (!rendererInit()) {
        std::cout << "Failed to initialise!\n";
        return false;
    }
    if (!cacheMedia()) {
        std::cout << "Failed to cache images!\n";
        return false;
    } 
    std::cout << "Renderer finished starting!\n";
    return true;
}

bool renderEngine::blitImage(std::string imgName, std::vector<int>* destCoords, std::vector<int>* srcCoords) {

    SDL_Rect srcRect;
    SDL_Rect destRect;
    bool srcRectPresent = true;
    bool destRectPresent = true;

    if (destCoords == nullptr) {
        destRectPresent = false;
    } else {
        destRect.x = destCoords->at(0);
        destRect.y = destCoords->at(1);
        destRect.w = destCoords->at(2);
        destRect.h = destCoords->at(3);
    }

    if (srcCoords == nullptr) {
        srcRectPresent = false;
    } else {
        srcRect.x = srcCoords->at(0);
        srcRect.y = srcCoords->at(1);
        srcRect.w = srcCoords->at(2);
        srcRect.h = srcCoords->at(3);
    }

    SDL_Texture* newTexture = imageCache.getImage(imgName, renderer);
    if (newTexture == NULL) {
        std::cout << "Failed to retrieve image from cache! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    if (!srcRectPresent) {
        if (!destRectPresent) {
            SDL_RenderCopy(renderer, newTexture, NULL, NULL);
        } else {
            SDL_RenderCopy(renderer, newTexture, NULL, &destRect);
        }
    } else {
        SDL_RenderCopy(renderer, newTexture, &srcRect, &destRect);
    }

    SDL_DestroyTexture(newTexture);
}

bool renderEngine::renderClear() {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF );  // Sets the drawing colour
    SDL_RenderClear(renderer);                                  // Fills the entire window with the drawing colour
}

bool renderEngine::rendererUpdate() {
    SDL_RenderPresent(renderer);
}

bool renderEngine::rendererStop() {
    imageCache.flushCache();

    SDL_DestroyWindow(window);

    SDL_DestroyRenderer(renderer);

    // It's a good practice to reset pointers to point to NULL when they aren't in use.
    IMG_Quit();
    SDL_Quit();
    return true;
}