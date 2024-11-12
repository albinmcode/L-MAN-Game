#include "SpanishWordUI.hpp"
#include <iostream>

WordSUI::WordSUI(sf::Vector2f spawnPoint)
{
    wordS.setPosition(spawnPoint);
    wordS.setScale(2.0f, 2.0f);
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

sf::Texture WordSUI::loadChrTexture(const std::int32_t index) {
    char letter = this->spanishWord[index];
    sf::Texture word;
    std::string str = std::string(1, letter);
    if (!word.loadFromFile("assets/img/fuente/" + str + ".png")) {
        std::cerr << "Error al cargar la textura de palabra." << std::endl;
    }
    return sf::Texture(word);
}

void WordSUI::changeWord(std::int32_t index) {
    this->spanishWord = getWordByIndex(index);
    this->letters = this->loadWordTexture();
}

std::vector<sf::Texture> WordSUI::loadWordTexture() {
    sf::Texture letter;
    std::vector<sf::Texture> tempLetters;

    for (int i = 0; i < this->spanishWord.length(); i++) {
        // obtain texture of a character
        letter = loadChrTexture(i);
        // save in the textures vector
        tempLetters.push_back(letter);
    }
    return tempLetters;
}
