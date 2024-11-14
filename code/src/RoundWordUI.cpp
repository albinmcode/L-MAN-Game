#include "RoundWordUI.hpp"
#include <iostream>

RoundWordUI::RoundWordUI(int y)
{
    this->wordSprite.setScale(2.0f, 2.0f);
    yCord = y;
}

void RoundWordUI::draw(sf::RenderWindow& window) {
    float spaceBetwen = 0;
    // draw all textures from the vector
    for (const sf::Texture texture : this->letters) {
        // sprite texture
        this->wordSprite.setTexture(texture);
        // position + space betwen letters
        this->wordSprite.setPosition(64 + spaceBetwen, 32+yCord);
        spaceBetwen += 32;
        // draw sprite
        window.draw(this->wordSprite);
        
    }
}

sf::Texture RoundWordUI::loadChrTexture(const std::int32_t index) {
    char letter = this->wordString[index];
    sf::Texture word;
    std::string str = std::string(1, letter);
    if (str != " ") {
        if (!word.loadFromFile("assets/img/fuente/" + str + ".png")) {
            std::cerr << "Error al cargar la textura de palabra." << std::endl;
        }
    }
    return sf::Texture(word);
}

void RoundWordUI::changeWord(std::int32_t index) {
    this->wordString = getWordByIndex(index);
    this->letters = this->loadWordTexture();
}

std::vector<sf::Texture> RoundWordUI::loadWordTexture() {
    sf::Texture letter;
    std::vector<sf::Texture> tempLetters;

    for (unsigned int i = 0; i < this->wordString.length(); i++) {
        // obtain texture of a character
        letter = loadChrTexture(i);
        // save in the textures vector
        tempLetters.push_back(letter);
    }
    return tempLetters;
}

void RoundWordUI::loadWordFromString(const std::string& newWord) {
    // Set the new word
    this->wordString = newWord;
    // Load textures for each character in the word
    this->letters = this->loadWordTexture();
}
