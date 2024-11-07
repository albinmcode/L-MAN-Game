#include "PlayerUI.hpp"
#include <iostream>

PlayerUI::PlayerUI(Vector2f spawnPoint)
: EntityUI(spawnPoint) {
    // Load textures
    if (!rightTexture.loadFromFile("assets/img/lman_right.png")) {
        std::cerr << "Error al cargar la textura del personaje." << std::endl;
    }
    if (!leftTexture.loadFromFile("assets/img/lman_left.png")) {
        std::cerr << "Error al cargar la textura del personaje." << std::endl;
    }
    // Right texture as default
    this->sprite.setTexture(rightTexture);
}

void PlayerUI::action(RenderWindow& window, std::int8_t key) {
    std::int32_t xcords = this->getScale().x;
    std::int32_t ycords = this->getScale().y;
    
    // Player Input
    std::int32_t input = 0;
    input = movInput(movementFactor, key);
    // Space pressed
    if (input == 2) {
        // TODO(any): manage character collection
        // std::cout << "space" << std::endl;
    }
    // move player
    else {
        // checkColision == 0 -> valid move
        if (checkColision(movementFactor, xcords, ycords) == 0) {
            this->move(window, movementFactor);
        }
    }
}
