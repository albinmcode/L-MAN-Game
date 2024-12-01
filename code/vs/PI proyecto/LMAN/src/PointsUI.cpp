#include "PointsUI.hpp"
#include <iostream>

PointsUI::PointsUI(sf::Vector2f spawnPoint)
: pointCount(0)
{
    // Set points positions
    this->hundred.setPosition(spawnPoint);
    this->ten.setPosition(spawnPoint.x + 32, spawnPoint.y);
    this->unit.setPosition(spawnPoint.x + 66, spawnPoint.y);
    // Load textures
    if (!digitTexture.loadFromFile("assets/img/fuente/0.png")) {
        std::cerr << "Error al cargar la textura del dígito." << std::endl;
    }
    // Initialize as filled hearts
    this->hundred.setTexture(digitTexture);
    this->ten.setTexture(digitTexture);
    this->unit.setTexture(digitTexture);
}

void PointsUI::draw(sf::RenderWindow& window) {
    // Hundreds
    this->loadDigit(this->hundred, 3);
    window.draw(hundred);
    // Tens
    this->loadDigit(this->ten, 2);
    window.draw(ten);
    // Units
    this->loadDigit(this->unit, 1);
    window.draw(unit);
    
}

void PointsUI::loadDigit(sf::Sprite& digitSprite, const int place) {
    if (this->pointCount > 999) return;
    std::string digit;
    // Obtain the specific digit
    char digitChr = '0'; // start in the ascii 0
    if (place == 3) digitChr += (this->pointCount / 100); // Hundreds
    else if (place == 2) digitChr += ((this->pointCount / 10) % 10); // Tens
    else if (place == 1) digitChr += (this->pointCount % 10); // Units
    digit = digitChr;
    // load digit sprite texture
    if (!digitTexture.loadFromFile("assets/img/fuente/" + digit + ".png")) {
        std::cerr << "Error al cargar la textura del dígito." << std::endl;
    }
    digitSprite.setTexture(digitTexture);
}

void PointsUI::winPoint() {
    // 999 as the maximum obtainable points
    if (this->pointCount < 999) {
        ++this->pointCount;
    }
}

void PointsUI::restart() {
    this->pointCount = 0;
}