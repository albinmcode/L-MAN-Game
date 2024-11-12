#ifndef GAMEMAPUI
#define GAMEMAPUI

#include <SFML/Graphics.hpp>

#include "PlayerUI.hpp"
#include "EnemyUI.hpp"
#include "HeartsUI.hpp"
#include "PointsUI.hpp"
#include "WordUI.hpp"
#include "SpanishWordUI.hpp"

extern "C" std::int32_t loadMap(std::int8_t*, std::int32_t);

using namespace sf;

class GameMap {
public:
    // default constructor
    GameMap();
    // Game events
    void run(RenderWindow& window);
    void handleEvent(RenderWindow& window, Event& event, std::int8_t& key);
    // Collecting objects on the map
    void collectEvent();
    // update the window
    void draw(RenderWindow& window);

private:
    // background
    Texture backgroundTexture;
    Sprite backgroundSprite;
    // map representations
    std::int32_t mapSize;
    std::int8_t map[13][24];
    // Entities
    PlayerUI lman;
    EnemyUI kanji;
    EnemyUI question;
    // hearts and points
    HeartsUI hearts;
    PointsUI points;
    //Words
    WordUI word;
    WordSUI wordSpanish;
};

#endif // !GAMEMAPUI
