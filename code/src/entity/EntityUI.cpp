#include "EntityUI.hpp"
#include <iostream>

EntityUI::EntityUI(Vector2f spawnPoint) 
: position(0,0),
scaledPosition(1, 1),
movementFactor{0}
{
    this->sprite.setPosition(spawnPoint);
}

void EntityUI::move(RenderWindow& window) {
    // increment or decrement the coordinates according to the parameters
    this->sprite.move(static_cast<float>(movementFactor[0] * speed)
        , static_cast<float>(movementFactor[1] * speed));
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
    this->position.x += this->movementFactor[0] * this->speed;
    this->position.y += this->movementFactor[1] * this->speed;
    // every 32 pixels update the logical scaled position
    if (this->position.x % 32 == 0) {
        this->scaledPosition.x = (this->position.x / 32) +1;
    }
    if (this->position.y % 32 == 0) {
        this->scaledPosition.y = (this->position.y / 32) +1;
    }
}

void EntityUI::restartPosition(std::int32_t xOffset, std::int32_t yOffset) {
    this->scaledPosition = sf::Vector2<std::int32_t>(xOffset+1, yOffset+1);
    this->position = sf::Vector2<std::int32_t>(xOffset*32, yOffset*32 );
    this->sprite.setPosition(static_cast<float>(xOffset * 32 + 64)
        , static_cast<float>(yOffset * 32 + 128));
    this->sprite.setTexture(this->rightTexture);
}

void EntityUI::restartMovement() {
    this->movementFactor[0] = 0;
    this->movementFactor[1] = 0;
}

void movInput(int32_t* movementFactor, int8_t key) {
  int8_t lowerKey =  (int8_t)std::tolower(key);
  if (lowerKey == 'w') {  // up
    movementFactor[0] = 0;
    movementFactor[1] = -1;
  } else if (lowerKey == 'a') {  // left
    movementFactor[0] = -1;
    movementFactor[1] = 0;
  } else if (lowerKey == 's') {  // down
    movementFactor[0] = 0;
    movementFactor[1] = 1;
  } else if (lowerKey == 'd') {  // right
    movementFactor[0] = 1;
    movementFactor[1] = 0;
  }
}