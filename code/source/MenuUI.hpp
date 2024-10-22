#ifndef MENUUI_HPP
#define MENUUI_HPP

#include <SFML/Graphics.hpp>
#include "ButtonUI.hpp"

using namespace sf;

class Menu {
public:
    Menu();
    void handleEvent(RenderWindow& window, Event& event, bool& isPlaying);
    void draw(RenderWindow& window);

private:
    Button playButton;
    Button infoButton;
    Button exitButton;
    Texture backgroundTexture;
    Sprite backgroundSprite;
};

#endif
