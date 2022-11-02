#ifndef SPRITELIST
#define SPRITELIST

extern const int SPRITE_SRC_WIDTH;
extern const int SPRITE_SRC_HEIGHT;

extern const int SPRITE_WIDTH;
extern const int SPRITE_HEIGHT;

extern const int WIDTH;
extern const int HEIGHT;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern const double SPF;

extern std::map<std::string, std::map<std::string, std::vector<int>>> spriteList;

enum class events {
    QUIT,
    KEY_UP,
    KEY_RIGHT,
    KEY_DOWN,
    KEY_LEFT,
    PAUSE
};

#endif