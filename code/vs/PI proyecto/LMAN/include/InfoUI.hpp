#ifndef INFOUI_HPP
#define INFOUI_HPP

#include <SFML/Graphics.hpp>
#include "ButtonUI.hpp"
#include "Link.hpp"

class InfoPage {
 public:
    InfoPage();  // Constructor
    void reset();  // Recarga las texturas
    void handleEvent(sf::RenderWindow& window, sf::Event& event, bool& backToMenu);  // Maneja los eventos
    void draw(sf::RenderWindow& window);  // Dibuja los elementos

 private:
    void linksFormat();

 private:
    sf::Texture manualTexture;
    sf::Texture creditsTexture;
    sf::Sprite backgroundSprite;
    bool inCredits = false;
    Button backButton;  // Botón para regresar al menú principal
    Button manualButton;  // Botón para ver instrucciones
    Button creditsButton;  // Botón para ver créditos
    // Font
    sf::Font retropix;
    // Links
    std::vector<sf::Link> links;
};

#endif // INFOUI_HPP
