#include "ButtonUI.hpp"
#include <iostream>

Button::Button(const sf::Vector2f& position, const std::string& textureFile, const sf::Vector2f& size) {
    if (!buttonTexture.loadFromFile(textureFile)) {
        std::cerr << "Error al cargar la textura del botón." << std::endl;
    }

    buttonShape.setSize(size);  // Ajustar el tamaño del botón
    buttonShape.setTexture(&buttonTexture);
    buttonShape.setPosition(position);
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(buttonShape);
}

bool Button::isMouseOver(const sf::RenderWindow& window) const {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::FloatRect buttonBounds = buttonShape.getGlobalBounds();
    return buttonBounds.contains(static_cast<sf::Vector2f>(mousePos));
}

void Button::setSize(const sf::Vector2f& size) {
    buttonShape.setSize(size);
}
