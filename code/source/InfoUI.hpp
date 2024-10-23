#ifndef INFOUI_HPP
#define INFOUI_HPP

#include <SFML/Graphics.hpp>
#include "ButtonUI.hpp"

using namespace sf;

class InfoPage {
public:
    InfoPage();  // Constructor

    void handleEvent(RenderWindow& window, Event& event, bool& backToMenu);  // Maneja los eventos
    void draw(RenderWindow& window);  // Dibuja los elementos
    void reset();  // Recarga las texturas

private:
    Texture backgroundTexture;
    Sprite backgroundSprite;
    Button backButton;  // Botón para regresar al menú principal
};

#endif // INFOUI_HPP
