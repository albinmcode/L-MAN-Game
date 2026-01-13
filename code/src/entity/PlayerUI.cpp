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

void PlayerUI::action(RenderWindow& window, std::int8_t& key) {
    this->collectFlag = false;
    int32_t tempMovFactor[2] = { 0 };
    // Process input only if the player has moved an entire 32x32 cell
    if (((this->getPosition().x+32) % 32 == 0)
        && ((this->getPosition().y+32) % 32 == 0)) {
        // Player Input
        movInput(tempMovFactor, key);
        // Only change movement factor if there is no colision
        if (checkColision(tempMovFactor,
            this->getScale().x, this->getScale().y) == 0) {
            movInput(this->movementFactor, key);
        }
        else key = 0;
    }
    
    // Space pressed
    if (key == ' ') {
        this->collectFlag = true;
        key = 0;
    }
    // update logical position
    // checkColision == 0 -> valid move
    if (checkColision(this->movementFactor,
            this->getScale().x, this->getScale().y) == 0) {
        this->move(window);
        // Sprite orientation
        if (movementFactor[0] == -1) {
            this->sprite.setTexture(leftTexture);
        }
        else if (movementFactor[0] == 1) {
            this->sprite.setTexture(rightTexture);
        }
    }
}

void PlayerUI::setBoost() {
    this->speed = 1;
}

void PlayerUI::setNormal() {
    this->speed = 1;
}