#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>
#include <vector>
#include <string>

#include "attributes.h"
#include "renderer.h"


std::vector<int> getDestVect(int x, int y) {
    return {50 + 32 * x, 50 + 32 * y, SPRITE_WIDTH, SPRITE_HEIGHT};
}

void drawBackground(renderEngine& renderer) {

    renderer.renderClear();

    for (int i=0; i<HEIGHT; i++) {
        for (int j=0; j<WIDTH; j++) {
            std::vector<int> destVect = getDestVect(j, i);

            if (destVect.size() != 4) {
                std::cout << "Destination vector is of wrong size! Size " << std::to_string(destVect.size()) << std::endl;
                return;
            }

            if (i == 0) {
                if (j == 0) {
                    renderer.blitImage("cellNW", &destVect);
                } else if (j == WIDTH-1) {
                    renderer.blitImage("cellNE", &destVect);
                } else {
                    renderer.blitImage("cellN", &destVect);
                }
            } else if (i == HEIGHT-1) {
                if (j == 0) {
                    renderer.blitImage("cellSW", &destVect);
                } else if (j == WIDTH-1) {
                    renderer.blitImage("cellSE", &destVect);
                } else {
                    renderer.blitImage("cellS", &destVect);
                }
            } else {
                if (j == 0) {
                    renderer.blitImage("cellW", &destVect);
                } else if (j == WIDTH-1) {
                    renderer.blitImage("cellE", &destVect);
                } else {
                    renderer.blitImage("cell", &destVect);
                }
            }

        }
    }
}

bool drawSprites(renderEngine& renderer, std::vector<std::pair<std::pair<int, int>, std::string>> boardData) {

    int i = 0;
    int l = boardData.size();

    while (i < l) {

        std::string tileDir = boardData[i].second;
        std::string tile;
        std::vector<int> destVect = getDestVect(boardData[i].first.second, boardData[i].first.first); // Remember that boardData presents coords as (y, x)

        /* std::cout << "This is tile number " << std::to_string(i) << " with x-coordinate " << std::to_string(destVect[0]) << " and y-coordinate " << std::to_string(destVect[1])
                  << ", and the tile direction is " << tileDir << std::endl; */

        // If head
        if (i == 0) {
            if (tileDir.length() != 1) {
                std::cout << "Invalid snake head tile direction!\n";
                return false;
            }
            tile = "head" + tileDir;
        } else

        // If tail
        if (i == l-2) {
            if (tileDir.length() != 1) {
                std::cout << "Invalid snake tail tile direction!\n";
                return false;
            }
            tile = "tail" + tileDir;
        } else 

        // If apple
        if (i == l-1) {
            if (tileDir.length() != 5) {
                std::cout << "Invalid apple!\n";
                return false;
            }
            tile = "apple";
        } else

        // General case
        {
            if (tileDir.length() != 2) {
                std::cout << "Invalid snake tile direction!\n";
                return false;
            }
            tile = "snake" + tileDir;
        }

        renderer.blitImage(tile, &destVect);

        i++;
    }

}