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

void GameMap::start(RenderWindow& window) {
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        window.clear();
        this->draw(window);
        window.display();
    }
}

void GameMap::handleEvent(RenderWindow& window, Event& event, bool& isPlaying) {
    // game events
}

void GameMap::draw(RenderWindow& window) {
    // Draw background
    window.draw(backgroundSprite);
}