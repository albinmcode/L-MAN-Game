#include "SpanishWordUI.hpp"
#include <iostream>

WordSUI::WordSUI(sf::Vector2f spawnPoint,std::string spanishWord):
spanishWord{spanishWord}
{
    wordS.setScale(2.0f, 2.0f);
    // Initialize vector of textures
    sf::Texture* letter = nullptr;
    for (int i = 0; i < spanishWord.length(); i++) {
        // obtain a sprite of a character
        letter = loadWordS(i);
        if (letter == nullptr) {
            std::cerr << "Error al cargar sprite" << std::endl;
        }
        // letter->setPosition(spawnPoint.x + 32*i, spawnPoint.y);
        // save the character sprite in the vector
        letters.push_back(letter);
    }
    

}

void WordSUI::draw(sf::RenderWindow& window) {
    float mov = 0;
    for (const sf::Texture* texture : this->letters) {
        this->wordS.setTexture(*texture);
        this->wordS.setPosition(64 + mov, 32);
        window.draw(wordS);
        mov += 32;
    }
}

sf::Texture* WordSUI::loadWordS(int index) {
    char letter = spanishWord[index];
    sf::Texture word;
    std::string str = std::string(1, letter);
    if (!word.loadFromFile("assets/img/fuente/" + str + ".png")) {
        std::cerr << "Error al cargar la textura de palabra." << std::endl;
    }
    return new sf::Texture(word);
}

