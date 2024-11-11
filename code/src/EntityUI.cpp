#include "EntityUI.hpp"
#include <iostream>

EntityUI::EntityUI(Vector2f spawnPoint) 
: movementFactor()
, position(0,0)
, scaledPosition(1, 1)
{
    this->sprite.setPosition(spawnPoint);
}

void EntityUI::move(RenderWindow& window, const std::int32_t(&movementFactor)[2]) {
    // sprite orientation
    if (movementFactor[0] == -1) {
        this->sprite.setTexture(leftTexture);
    }
    else if (movementFactor[0] == 1) {
        this->sprite.setTexture(rightTexture);
    }
    // increment or decrement the coordinates according to the parameters
    this->sprite.move(movementFactor[0], movementFactor[1]);
    // update logical position
    this->updatePosition();
    // draw sprite
    this->draw(window);
    // window.display();
}

void EntityUI::draw(RenderWindow& window) {
    window.draw(this->sprite);
}

const sf::Vector2<std::int32_t>& EntityUI::getScale() {
    return this->scaledPosition;
}

const sf::Vector2<std::int32_t>& EntityUI::getPosition() {
    return this->position;
}

void EntityUI::updatePosition() {
    // increment according to the movement factor
    this->position.x += this->movementFactor[0];
    this->position.y += this->movementFactor[1];
    // every 32 pixels update the logical scaled position
    if (this->position.x % 32 == 0) {
        this->scaledPosition.x = (this->position.x / 32) +1;
    }
    if (this->position.y % 32 == 0) {
        this->scaledPosition.y = (this->position.y / 32) +1;
    }
}
