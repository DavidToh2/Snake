#ifndef RENDERER
#define RENDERER

        // To start the render engine:
            // renderEngine renderer;
            // renderer.rendererStart();

        // To blit an image:
            // renderer.blitImage(image name, optional destination (x, y, w, h), optional source (x, y, w, h))
            // Image name needs to be already stored in the image cache.

        // To update the frame:
            // renderer.rendererUpdate();

        // To stop the render engine:
            // renderer.rendererStop();

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "attributes.h"

class renderEngine {

    class imgCache {
        private:
        std::map<std::string, SDL_Surface*> cache_;

        public:
        SDL_Surface* loadImageIntoMemory(std::string imgPath);
        bool cacheImage(std::string imgName, std::string imgPath);
        bool cacheImageMap(std::vector<std::string> imgNameList, std::string imgMapPath, std::vector<SDL_Rect> rectList);
        SDL_Surface* getRawImage(std::string imgName);
        SDL_Texture* getImage(std::string imgName, SDL_Renderer* targetRenderer);
        void flushCache();
        ~imgCache();
    };

    SDL_Window* window;
    SDL_Renderer* renderer;
    imgCache imageCache;

    public:

    renderEngine();

    bool rendererInit();
    bool cacheMedia();
    bool rendererStart();
    bool blitImage(std::string imgName, std::vector<int>* destCoords = nullptr, std::vector<int>* srcCoords = nullptr);
    bool renderClear();
    bool rendererUpdate();
    bool rendererStop();
};

#endif