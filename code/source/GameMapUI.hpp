#ifndef GAMEMAPUI
#define GAMEMAPUI

#include <SFML/Graphics.hpp>

#include "PlayerUI.hpp"
#include "EnemyUI.hpp"

extern "C" std::int32_t loadMap(std::int8_t*, std::int32_t);

using namespace sf;

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
    std::int32_t mapSize;
    std::int8_t map[13][24];
    PlayerUI lman;
    EnemyUI kanji;
    EnemyUI question;
};

#endif // !GAMEMAPUI
