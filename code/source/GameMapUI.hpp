#ifndef GAMEMAPUI
#define GAMEMAPUI

#include <SFML/Graphics.hpp>

#include "PlayerUI.hpp"

using namespace sf;

extern "C" std::int32_t movInput(std::int32_t*, std::int8_t);

class GameMap {
public:
    // default constructor
    GameMap();
    // Game events
    void run(RenderWindow& window);
    void handleEvent(RenderWindow& window, Event& event, std::int8_t& key);
    // update the window
    void draw(RenderWindow& window);

private:
    Texture backgroundTexture;
    Sprite backgroundSprite;
    PlayerUI lman;
};

#endif // !GAMEMAPUI
