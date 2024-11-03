#include "GameMapUI.hpp"
#include <iostream>

GameMap::GameMap()
: lman(Vector2f(64+2, 128))
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
        this->draw(window);
        this->lman.draw(window);
        this->kanji.draw(window);
        this->question.draw(window);
        // player movement
        this->lman.action(window, key);
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
