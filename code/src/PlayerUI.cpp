#include "PlayerUI.hpp"
#include <iostream>

PlayerUI::PlayerUI(Vector2f spawnPoint)
: EntityUI(spawnPoint) 
, collectFlag(false) 
{
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

const bool PlayerUI::collectChr() {
    return this->collectFlag;
}

void PlayerUI::action(RenderWindow& window, std::int8_t key) {
    this->collectFlag = false;
    std::int32_t input = 0;
    // std::cout << this->getPosition().x << ',' << this->getPosition().y << '\n';
    // Process input only if the player has moved an entire 32x32 cell
    if (((this->getPosition().x+32) % 32 == 0)
        && ((this->getPosition().y+32) % 32 == 0)) {
        // Player Input
        input = movInput(movementFactor, key);
    }
    
    // Space pressed
    if (input == 2) {
        this->collectFlag = true;
    }
    // move player
    else {
        // update logical position
        // checkColision == 0 -> valid move
        if (checkColision(movementFactor,
                this->getScale().x, this->getScale().y) == 0) {
            this->move(window, movementFactor);
        }
    }
}
