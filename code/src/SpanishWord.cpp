#include "SpanishWordUI.hpp"
#include <iostream>

WordSUI::WordSUI(sf::Vector2f spawnPoint,std::string spanishWord):
spanishWord{spanishWord}
{
    wordS.setPosition(spawnPoint);
    wordS.setScale(2.0f, 2.0f);
    // Initialize vector of textures
    sf::Texture letter;
    for (int i = 0; i < spanishWord.length(); i++) {
        // obtain texture of a character
        letter = loadWordS(i);
        // save in the textures vector
        letters.push_back(letter);
    }
    

}

void WordSUI::draw(sf::RenderWindow& window) {
    float spaceBetwen = 0;
    // draw all textures from the vector
    for (const sf::Texture texture : this->letters) {
        // sprite texture
        this->wordS.setTexture(texture);
        // position + space betwen letters
        this->wordS.setPosition(64 + spaceBetwen, 32);
        spaceBetwen += 32;
        // draw sprite
        window.draw(wordS);
        
    }
}

sf::Texture WordSUI::loadWordS(int index) {
    char letter = this->spanishWord[index];
    sf::Texture word;
    std::string str = std::string(1, letter);
    if (!word.loadFromFile("assets/img/fuente/" + str + ".png")) {
        std::cerr << "Error al cargar la textura de palabra." << std::endl;
    }
    return sf::Texture(word);
}

