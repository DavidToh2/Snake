#ifndef GRAPHICS
#define GRAPHICS

#include <vector>
#include <string>

#include "attributes.h"
#include "renderer.h"

void drawBackground(renderEngine& renderer);
bool drawSprites(renderEngine& renderer, std::vector<std::pair<std::pair<int, int>, std::string>> boardData);
std::vector<int> getDestVect(int x, int y);

#endif