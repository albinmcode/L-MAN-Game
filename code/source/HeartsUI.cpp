#include "HeartsUI.hpp"
#include <iostream>

HeartsUI::HeartsUI(sf::Vector2f spawnPoint)
: heartsCount(3)
{
    // Set hearts positions
    this->heart1.setPosition(spawnPoint);
    this->heart2.setPosition(spawnPoint.x + 34, spawnPoint.y);
    this->heart3.setPosition(spawnPoint.x + 66, spawnPoint.y);
    // Load textures
    if (!emptyTexture.loadFromFile("assets/img/heart_empty.png")) {
        std::cerr << "Error al cargar la textura del corazon." << std::endl;
    }
    if (!filledTexture.loadFromFile("assets/img/heart.png")) {
        std::cerr << "Error al cargar la textura del corazon." << std::endl;
    }
    // Initialize as filled hearts
    this->heart1.setTexture(filledTexture);
    this->heart2.setTexture(filledTexture);
    this->heart3.setTexture(filledTexture);
}

void HeartsUI::draw(sf::RenderWindow& window) {
    if (this->heartsCount < 3) {
        this->heart1.setTexture(emptyTexture);
    }
    if (this->heartsCount < 2) {
        this->heart2.setTexture(emptyTexture);
    }
    if (this->heartsCount < 1) {
        this->heart1.setTexture(emptyTexture);
    }
    window.draw(heart1);
    window.draw(heart2);
    window.draw(heart3);
}

void HeartsUI::loseHeart() {
    if (this->heartsCount > 0) {
        --this->heartsCount;
    }
}