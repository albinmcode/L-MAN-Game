#ifndef GAMEMAPUI
#define GAMEMAPUI

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "EnemyUI.hpp"
#include "EnglishWordUI.hpp"
#include "HeartsUI.hpp"
#include "LettersUI.hpp"
#include "PlayerUI.hpp"
#include "PointsUI.hpp"
#include "SpanishWordUI.hpp"
#include "SoundUI.hpp"

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
    bool checkEndCondition();
    // update the window
    void draw(RenderWindow& window);
    void vulnerability();
    bool getColision();
    bool getEntityColision(EnemyUI enemy);
    void dead();

    const float calculateDistance(sf::Vector2i pos1, sf::Vector2i pos2);

private:
    // Game flow control
    std::int8_t key = 0;
    sf::Clock clock;
    sf::Music backgroundMusic;
    sf::Clock vulnerabilityClock;
    SoundUI sound;
    float delayBetweenLives = 3.0f;
    bool canLoseLife = true;
    float collisionDistance = 10.0f;

    // background
    Texture backgroundTexture;
    Sprite backgroundSprite;
    // Entities
    PlayerUI lman;
    EnemyUI kanji;
    EnemyUI question;
    // hearts and points
    HeartsUI hearts;
    PointsUI points;
    //Words
    LettersUI letters;
    SpanishWordUI wordSpanish;
    EnglishWordUI wordEnglish;
};

#endif // !GAMEMAPUI
