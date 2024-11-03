#include "EntityUI.hpp"
#include <iostream>

EntityUI::EntityUI(Vector2f spawnPoint) 
: movementFactor()
{
    this->sprite.setPosition(spawnPoint);
}

void EntityUI::move(RenderWindow& window, const std::int32_t(&movementFactor)[2]) {
    // sprite orientation
    if (movementFactor[0] == -1) {
        this->sprite.setTexture(leftTexture);
    }
    else {
        this->sprite.setTexture(rightTexture);
    }
    // increment or decrement the coordinates according to the parameters
    this->sprite.move(movementFactor[0], movementFactor[1]);
    this->draw(window);
    window.display();
}

void EntityUI::draw(RenderWindow& window) {
    window.draw(sprite);
}

const sf::Vector2i EntityUI::getPosition() {
    sf::Vector2i position;
    position.x = round(this->sprite.getPosition().x);
    position.y = round(this->sprite.getPosition().y);
    return position;
}
