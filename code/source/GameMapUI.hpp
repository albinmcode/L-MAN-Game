#ifndef GAMEMAPUI
#define GAMEMAPUI

#include <SFML/Graphics.hpp>

#include "PlayerUI.hpp"
#include "EnemyUI.hpp"

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
    PlayerUI lman;
    EnemyUI kanji;
    EnemyUI question;
};

#endif // !GAMEMAPUI
