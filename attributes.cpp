#include <map>
#include <string>
#include <vector>
#include "attributes.h"

const int SPRITE_SRC_WIDTH = 64;        // Width and height on spritemap
const int SPRITE_SRC_HEIGHT = 64;

const int SPRITE_WIDTH = 32;            // Width and height on display window
const int SPRITE_HEIGHT = 32;

const int WIDTH = 20;
const int HEIGHT = 15;

const int SCREEN_WIDTH = 740;
const int SCREEN_HEIGHT = 580;

const double SPF = 0.0166;

std::map<std::string, std::map<std::string, std::vector<int>>> spriteList = {
    {"spritemap.png", {
        {"apple",   {0, 0, SPRITE_SRC_WIDTH, SPRITE_SRC_HEIGHT} },
        {"snakeEW", {0, 128, SPRITE_SRC_WIDTH, SPRITE_SRC_HEIGHT} },
        {"snakeNS", {0, 192, SPRITE_SRC_WIDTH, SPRITE_SRC_HEIGHT} },
        {"snakeSE", {64, 0, SPRITE_SRC_WIDTH, SPRITE_SRC_HEIGHT} },
        {"snakeSW", {64, 64, SPRITE_SRC_WIDTH, SPRITE_SRC_HEIGHT} },
        {"snakeNW", {64, 128, SPRITE_SRC_WIDTH, SPRITE_SRC_HEIGHT} },
        {"snakeNE", {64, 192, SPRITE_SRC_WIDTH, SPRITE_SRC_HEIGHT} },
        {"headS",   {128, 0, SPRITE_SRC_WIDTH, SPRITE_SRC_HEIGHT} },
        {"headW",   {128, 64, SPRITE_SRC_WIDTH, SPRITE_SRC_HEIGHT} },
        {"headN",   {128, 128, SPRITE_SRC_WIDTH, SPRITE_SRC_HEIGHT} },
        {"headE",   {128, 192, SPRITE_SRC_WIDTH, SPRITE_SRC_HEIGHT} },
        {"tailN",   {192, 0, SPRITE_SRC_WIDTH, SPRITE_SRC_HEIGHT} },
        {"tailE",   {192, 64, SPRITE_SRC_WIDTH, SPRITE_SRC_HEIGHT} },
        {"tailS",   {192, 128, SPRITE_SRC_WIDTH, SPRITE_SRC_HEIGHT} },
        {"tailW",   {192, 192, SPRITE_SRC_WIDTH, SPRITE_SRC_HEIGHT} },
        {"cell",    {0, 64, SPRITE_SRC_WIDTH, SPRITE_SRC_HEIGHT} },
        {"cellN",   {256, 0, SPRITE_SRC_WIDTH, SPRITE_SRC_HEIGHT} },
        {"cellS",   {256, 64, SPRITE_SRC_WIDTH, SPRITE_SRC_HEIGHT} },
        {"cellE",   {256, 128, SPRITE_SRC_WIDTH, SPRITE_SRC_HEIGHT} },
        {"cellW",   {256, 192, SPRITE_SRC_WIDTH, SPRITE_SRC_HEIGHT} },
        {"cellNE",  {320, 0, SPRITE_SRC_WIDTH, SPRITE_SRC_HEIGHT} },
        {"cellSE",  {320, 64, SPRITE_SRC_WIDTH, SPRITE_SRC_HEIGHT} },
        {"cellSW",  {320, 128, SPRITE_SRC_WIDTH, SPRITE_SRC_HEIGHT} },
        {"cellNW",  {320, 192, SPRITE_SRC_WIDTH, SPRITE_SRC_HEIGHT} }
        }
    }
};