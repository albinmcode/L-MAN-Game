#include "WordUI.hpp"
#include <iostream>

WordUI::WordUI(sf::Vector2f spawnPoint)
{
    // Set points positions
    this->word.setPosition(spawnPoint);
    // Load textures
    if (!wordTexture.loadFromFile("assets/img/fuente/0.png")) {
        std::cerr << "Error al cargar la textura del dgito." << std::endl;
    }
    // Initialize as filled hearts
    this->word.setTexture(wordTexture);
    this->word.setScale(2.0f,2.0f);

}

void WordUI::draw(sf::RenderWindow& window) {
    loadWord(word);
    window.draw(word);
    
}

 void WordUI::loadWord(sf::Sprite& wordSprite) {
     std::string digit;
    
     if (!wordTexture.loadFromFile("assets/img/fuente/k.png")) {
         std::cerr << "Error al cargar la textura del dgito." << std::endl;
     }
     wordSprite.setTexture(wordTexture);
 }

