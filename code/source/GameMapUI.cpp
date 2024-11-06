#include "GameMapUI.hpp"
#include <iostream>

GameMap::GameMap()
: mapSize(13*24)
, map()
, lman(Vector2f(64, 128))
, kanji(Vector2f(384 + 2, 288), "assets/img/kanji.png")
, question(Vector2f(384 + 2, 320 + 2), "assets/img/pregunta.png")
{
    // Load background
    if (!backgroundTexture.loadFromFile("assets/img/background.png")) {
        std::cerr << "Error al cargar la textura del fondo." << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    // Center background
    backgroundSprite.setPosition(Vector2f(35, 0));
    
    // load map representation
    std::int8_t tempVector[312] = { 0 };
    if (loadMap(tempVector, this->mapSize) == 0) {
        int count = 0;
        for (int i = 0; i < 13; ++i) {
            for (int j = 0; j < 24; ++j) {      
                this->map[i][j] = tempVector[i*24 + j];
                std::cout << static_cast <int>(this->map[i][j]);
                ++count;
            }
            std::cout << std::endl;
        }
    }
}

void GameMap::run(RenderWindow& window) {
    std::int32_t movementFactor[] = { 0, 0 };
    std::int32_t input = 0;
    std::int8_t key = 0;
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            this->handleEvent(window, event, key);
        }
        window.clear();
        // Sprites draw
        this->draw(window);
        this->lman.draw(window);
        this->kanji.draw(window);
        this->question.draw(window);
        // player movement
        this->lman.action(window, key);
        window.display();
    }
}

void GameMap::handleEvent(RenderWindow& window, Event& event, std::int8_t& key) {
    if (event.type == Event::Closed) {
        window.close();
    }
    if (event.type == Event::KeyPressed) {
        // Convert from SFML key.code to ASCII
        if (event.key.code >= sf::Keyboard::A && event.key.code <= sf::Keyboard::Z) {
            key = static_cast<std::int8_t>(event.key.code - sf::Keyboard::A + 'A');
        }
        else if (event.key.code == sf::Keyboard::Space) {
            key = 32;
        }
    }
}

void GameMap::draw(RenderWindow& window) {
    // Draw background
    window.draw(backgroundSprite);
}
