#include "MenuUI.hpp"
#include <iostream>

Menu::Menu() :
    playButton(Vector2f(128, 80), "assets/menu_inicio.png"),
    infoButton(Vector2f(128, 120), "assets/menu_info.png"),
    exitButton(Vector2f(128, 160), "assets/menu_salir.png") {

    // Load menu background
    if (!backgroundTexture.loadFromFile("assets/menu_titulo.png")) {
        std::cerr << "Error al cargar la textura del fondo." << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(Vector2f(128, 15));
    
}

void Menu::handleEvent(RenderWindow& window, Event& event, bool& isPlaying) {
    if (event.type == Event::MouseButtonPressed) {
        // Start game
        if (playButton.isMouseOver(window)) {
            isPlaying = true;
            cout << "hola";
        }
        // Instrucctions and credits
        if (infoButton.isMouseOver(window)) {
            this->info.draw(window);
        }
        // End program
        else if (exitButton.isMouseOver(window)) {
            window.close();
        }
    }
}

void Menu::draw(RenderWindow& window) {
    // Draw background first
    window.draw(backgroundSprite);

    // Draw buttons
    playButton.draw(window);
    infoButton.draw(window);
    exitButton.draw(window);
}
