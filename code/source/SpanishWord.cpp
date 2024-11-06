#include "SpanishWordUI.hpp"
#include <iostream>

WordSUI::WordSUI(sf::Vector2f spawnPoint,std::string spanishWord):
spanishWord{spanishWord}
{
    // Set points positions
    this->wordS.setPosition(spawnPoint);
    // Load textures
    if (!wordSTexture.loadFromFile("assets/img/fuente/a.png")) {
        std::cerr << "Error al cargar la textura del dgito." << std::endl;
    }
    // Initialize as filled hearts
    this->wordS.setTexture(wordSTexture);
    this->wordS.setScale(2.0f,2.0f);

}

void WordSUI::draw(sf::RenderWindow& window) {
    loadWordS(wordS,0);
    window.draw(wordS);
}

void WordSUI::loadWordS(sf::Sprite& wordSSprite,int index) {
    char letter=spanishWord[index];
    std::string str = std::string(1, letter); 
    // load digit sprite texture
    if (!wordSTexture.loadFromFile("assets/img/fuente/" +str+ ".png")) {
        std::cerr << "Error al cargar la textura del dgito." << std::endl;
    }
    wordSSprite.setTexture(wordSTexture);
}

