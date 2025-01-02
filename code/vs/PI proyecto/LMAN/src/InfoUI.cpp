#include "InfoUI.hpp"
#include <iostream>

InfoPage::InfoPage() 
: backButton(sf::Vector2f(20, 10), "assets/img/menu_salir.png", sf::Vector2f(96, 48))
, manualButton(sf::Vector2f(128, 32), "assets/img/info_manual_click.png", sf::Vector2f(288, 96))
, creditsButton(sf::Vector2f(352, 32), "assets/img/info_creditos_click.png", sf::Vector2f(384, 96))
{

    if (!manualTexture.loadFromFile("assets/img/info_manual.png")) {
        std::cerr << "Error al cargar la textura del fondo de información." << std::endl;
    }
    if (!creditsTexture.loadFromFile("assets/img/info_creditos.png")) {
        std::cerr << "Error al cargar la textura del fondo de información." << std::endl;
    }
    
    this->reset();
    this->linksFormat();
}

void InfoPage::linksFormat() {
    // Links factory
    links.push_back(sf::Link("@remaxim", "https://opengameart.org/content/pacman-clone-background-music", sf::Vector2f(672, 240)));
    links.push_back(sf::Link("@freesound_community", "https://pixabay.com/es/users/freesound_community-46691455/", sf::Vector2f(672, 344)));
    links.push_back(sf::Link("@RibhavAgrawal", "https://pixabay.com/es/users/ribhavagrawal-39286533/", sf::Vector2f(672, 380)));
    links.push_back(sf::Link("@Driken5482", "https://pixabay.com/es/users/driken5482-45721595/", sf::Vector2f(672, 416)));
    
    // Load font
    if (!retropix.loadFromFile("assets/font/retropix.ttf")) {
        std::cerr << "Error al cargar fuente en Información." << std::endl;
    }
    // Text format
    for (sf::Link& link : this->links) {
        link.setFont(retropix);
        link.setCharacterSize(32);
        link.setFillColor(sf::Color::Blue);
        link.setStyle(sf::Text::Bold);
        // centered
        sf::FloatRect linkRect = link.getLocalBounds();
        link.setOrigin(linkRect.left + linkRect.width / 2.0f,
            linkRect.top + linkRect.height / 2.0f);
    }
}

void InfoPage::reset() {
    backgroundSprite.setTexture(manualTexture);
    this->inCredits = false;
}

void InfoPage::handleEvent(sf::RenderWindow& window, sf::Event& event, bool& backToMenu) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (backButton.isMouseOver(window)) {
            backToMenu = true;  // Volver al menú principal
        }
        else if (manualButton.isMouseOver(window)) {
            this->inCredits = false;
            this->backgroundSprite.setTexture(manualTexture);
        }
        else if (creditsButton.isMouseOver(window)) {
            this->inCredits = true;
            this->backgroundSprite.setTexture(creditsTexture);
        }
        // open links
        if (this->inCredits) {
            for (sf::Link& link : this->links) {
                if (link.isMouseOver(window)) {
                    link.openURL();
                }
            }   
        }
    }
}

void InfoPage::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    backButton.draw(window);
    manualButton.draw(window);
    creditsButton.draw(window);
    if (this->inCredits) {
        for (sf::Link& link : this->links) {
            window.draw(link);
        }
    }
}
