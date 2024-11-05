#include "EntityUI.hpp"
#include <iostream>

EntityUI::EntityUI(Vector2f spawnPoint) 
: movementFactor()
, position(1,1)
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
    this->draw(window);
    // window.display();
}

void EntityUI::draw(RenderWindow& window) {
    window.draw(this->sprite);
}

const sf::Vector2<std::int32_t> EntityUI::getPosition() {
    // scale from 32 to 1
    sf::Vector2<std::int32_t> scaledPosition;
    // Int division to scale + start adjustment 
    scaledPosition.x = (this->position.x / 32) + 1;
    scaledPosition.y = (this->position.y / 32) + 1;
    return scaledPosition;
}

void EntityUI::updatePosition() {
    this->position.x += this->movementFactor[0];
    this->position.y += this->movementFactor[1];
}
