#include "ButtonUI.hpp"
#include <iostream>

Button::Button(const Vector2f& position, const string& textureFile) {
    // Cargar la textura del botón y manejar errores
    if (!buttonTexture.loadFromFile(textureFile)) {
        std::cerr << "Error al cargar la textura: " << textureFile << std::endl;
    }

    // Establecer la textura al botón
    buttonShape.setTexture(&buttonTexture);

    // Ajustar el tamaño del botón según la textura
    buttonShape.setSize(Vector2f(192,64));
    buttonShape.setPosition(position);
}

bool Button::isMouseOver(const RenderWindow& window) const {
    Vector2i mousePos = Mouse::getPosition(window);
    return buttonShape.getGlobalBounds().contains(static_cast<Vector2f>(mousePos));
}

void Button::draw(RenderWindow& window) {
    window.draw(buttonShape);
}
