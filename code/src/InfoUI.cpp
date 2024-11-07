#include "InfoUI.hpp"
#include <iostream>

InfoPage::InfoPage() :
    backButton(Vector2f(20, 10), "assets/img/menu_salir.png", Vector2f(128, 47))  // Tamaño reducido
{
    reset();
}

void InfoPage::reset() {
    if (!backgroundTexture.loadFromFile("assets/img/info.png")) {
        std::cerr << "Error al cargar la textura del fondo de información." << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Escalar el fondo a 455x256
    // float scaleX = 910.0f / backgroundTexture.getSize().x;
    // float scaleY = 512.0f / backgroundTexture.getSize().y;
    // backgroundSprite.setScale(scaleX, scaleY);
}

void InfoPage::handleEvent(RenderWindow& window, Event& event, bool& backToMenu) {
    if (event.type == Event::MouseButtonPressed) {
        if (backButton.isMouseOver(window)) {
            backToMenu = true;  // Volver al menú principal
        }
    }
}

void InfoPage::draw(RenderWindow& window) {
    window.draw(backgroundSprite);
    backButton.draw(window);
}
