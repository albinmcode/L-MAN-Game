#ifndef MENUUI_HPP
#define MENUUI_HPP

#include <SFML/Graphics.hpp>
#include "ButtonUI.hpp"
#include "InfoUI.hpp"

class Menu {
public:
    Menu();
    void handleEvent(sf::RenderWindow& window, sf::Event& event, bool& isPlaying, bool& backToMenu);
    void draw(sf::RenderWindow& window);

private:
    Button playButton;
    Button infoButton;
    Button exitButton;
    InfoPage info;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    bool inInfoPage;  // Bandera para saber si estamos en la página de info
};

#endif
