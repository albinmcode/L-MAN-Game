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
    Vector2f origin(64+2, 128);
    this->playerSprite.setPosition(origin);
}

void PlayerUI::move(RenderWindow& window, const std::int32_t (&movementFactor)[2]) {
    // sprite orientation
    if (movementFactor[0] == -1) {
        this->playerSprite.setTexture(leftTexture);
    }
    else {
        this->playerSprite.setTexture(rightTexture);
    }
    // increment or decrement the coordinates according to the parameters
    this->playerSprite.move(movementFactor[0], movementFactor[1]);
    this->draw(window);
    window.display();
}

void PlayerUI::draw(RenderWindow& window) {
    window.draw(playerSprite);
}

const sf::Vector2i PlayerUI::getPosition() {
    sf::Vector2i position;
    position.x = round(this->playerSprite.getPosition().x);
    position.y = round(this->playerSprite.getPosition().y);
    return position;
}
