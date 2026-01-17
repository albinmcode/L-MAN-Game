#include "MenuUI.hpp"
#include <iostream>

Menu::Menu() :
    playButton(sf::Vector2f(256, 160), "../assets/img/menu_inicio.png", sf::Vector2f(384, 128)),
    infoButton(sf::Vector2f(256, 240), "../assets/img/menu_info.png", sf::Vector2f(384, 128)),
    exitButton(sf::Vector2f(256, 320), "../assets/img/menu_salir.png", sf::Vector2f(384, 128)),
    inInfoPage(false)
{
    if (!backgroundTexture.loadFromFile("../assets/img/menu_titulo.png")) {
        std::cerr << "Error al cargar la textura del fondo del menú." << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(sf::Vector2f(256, 30));
}

void Menu::handleEvent(sf::RenderWindow& window, sf::Event& event, bool& isPlaying, bool& backToMenu) {
    if (inInfoPage) {
        info.handleEvent(window, event, backToMenu);
        if (backToMenu) {
            inInfoPage = false;  // Volver al menú principal
            backToMenu = false;  // Reiniciar la bandera
        }
    } else if (event.type == sf::Event::MouseButtonPressed) {
        if (playButton.isMouseOver(window)) {
            isPlaying = true;
        } else if (infoButton.isMouseOver(window)) {
            inInfoPage = true;
            info.reset();  // Recargar la pantalla de info al ingresar
        } else if (exitButton.isMouseOver(window)) {
            window.close();
        }
    }
}

void Menu::draw(sf::RenderWindow& window) {
    if (inInfoPage) {
        info.draw(window);
    } else {
        window.draw(backgroundSprite);
        playButton.draw(window);
        infoButton.draw(window);
        exitButton.draw(window);
    }
}
