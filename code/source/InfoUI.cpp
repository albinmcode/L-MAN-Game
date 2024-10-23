#include "InfoUI.hpp"
#include <iostream>

InfoPage::InfoPage() {
    // Load background
    if (!backgroundTexture.loadFromFile("assets/info.png")) {
        std::cerr << "Error al cargar la textura del fondo." << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(0.5, 0.5);
}

void InfoPage::handleEvent(RenderWindow& window, Event& event) {
    // menú button
}

void InfoPage::draw(RenderWindow& window) {
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        window.clear();
        window.draw(this->backgroundSprite);
        window.display();
    }
}