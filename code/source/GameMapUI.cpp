#include "GameMapUI.hpp"
#include <iostream>

GameMap::GameMap(){
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

        // Player Input
        input = movInput(movementFactor, key);
        // Check borders
        if ((this->lman.getPosition().x > 0+2 && this->lman.getPosition().x < 910-164)
            && (this->lman.getPosition().y > 0+2 && this->lman.getPosition().y < 512-64)) {
            // Space pressed
            if (input == 2) {
                // TODO(any): manage character collection
                // std::cout << "space" << std::endl;
            }
            // move player
            else {
                this->lman.move(window, movementFactor);
            }
        }
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
            // key = static_cast<std::int8_t>(character);
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
