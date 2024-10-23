#include "PlayerUI.hpp"
#include <iostream>

PlayerUI::PlayerUI() {
    // Load textures
    if (!rightTexture.loadFromFile("assets/img/lman_right.png")) {
        std::cerr << "Error al cargar la textura del personaje." << std::endl;
    }
    if (!leftTexture.loadFromFile("assets/img/lman_left.png")) {
        std::cerr << "Error al cargar la textura del personaje." << std::endl;
    }
    // Right texture as default
    this->playerSprite.setTexture(rightTexture);
    // origin position
    Vector2f origin(48+2, 128);
    this->playerSprite.setScale(2,2);
    this->playerSprite.setPosition(origin);
}

void PlayerUI::draw(RenderWindow& window, const int (&movementFactor)[2]) {
    // increment or decrement the coordinates according to the parameters
    this->playerSprite.move(movementFactor[0] * 32, movementFactor[1] * 32);
    // sprite orientation
    if (movementFactor[0] == -1) {
        this->playerSprite.setTexture(leftTexture);
    }
    else {
        this->playerSprite.setTexture(rightTexture);
    }
    
    window.draw(playerSprite);
}
