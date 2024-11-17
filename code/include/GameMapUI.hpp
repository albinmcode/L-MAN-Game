#ifndef GAMEMAPUI
#define GAMEMAPUI

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "PlayerUI.hpp"
#include "EnemyUI.hpp"
#include "HeartsUI.hpp"
#include "PointsUI.hpp"
#include "WordUI.hpp"
#include "SpanishWordUI.hpp"
#include "EnglishWordUI.hpp"

extern "C" std::int32_t loadMap(std::int8_t*, std::int32_t);
extern "C" int compareWords(const char* palabra1, const char* palabra2, unsigned int n);
extern "C" const char* getWordByIndex(std::int32_t index);
extern "C" int stringLength(const char* str);

using namespace sf;

class GameMap {
public:
    // default constructor
    GameMap();
    // Game events
    void run(RenderWindow& window);
    void handleEvent(RenderWindow& window, Event& event);
    // Collecting objects on the map
    void collectEvent();
    // Collecting objects on the map
    void entityColisionEvent();
    // round end control
    const bool checkEndCondition();
    // Flag that specifies if the player won
    const bool getWinFlag();
    // update the window
    void draw(RenderWindow& window);

    const float calculateDistance(sf::Vector2i pos1, sf::Vector2i pos2);

private:
    // Game flow control
    std::int8_t key = 0;
    sf::Clock clock;
    sf::Music backgroundMusic;
    float delayBetweenLives = 3.0f;
    bool canLoseLife = true;
    float collisionDistance = 10.0f;

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
    EnglishWordUI wordEnglish;
};

#endif // !GAMEMAPUI
