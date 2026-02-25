#include "RoundWordUI.hpp"

#include <iostream>

#include "Dictionary.hpp"

RoundWordUI::RoundWordUI(int yCord)
: wordString()
, yCord(yCord)
{
    this->wordSprite.setScale(2.0f, 2.0f);
}

void RoundWordUI::draw(sf::RenderWindow& window) {
    float spaceBetwen = 0;
    // draw all textures from the vector
    for (const sf::Texture& texture : this->letters) {
        // sprite texture
        this->wordSprite.setTexture(texture);
        // position + space betwen letters
        this->wordSprite.setPosition(64 + spaceBetwen, 32+yCord);
        spaceBetwen += 32;
        // draw sprite
        window.draw(this->wordSprite);
        
    }
}

void RoundWordUI::loadLetterTexture(const std::int32_t index,
    sf::Texture& letterTexture, const std::wstring& wordStr) {
    //   std::wstring wLetter;
    //   wLetter = wordStr.at(index);
  std::string letter = wStrConverter.to_bytes(wordStr.at(index));
  if (letter == " ") {
    return;  // space
  }
  if (!letterTexture.loadFromFile("../assets/img/fuente/" + letter + ".png")) {
    std::cerr << "Error al cargar la textura de palabra." << std::endl;
  }
}

size_t RoundWordUI::getlength() const {
    return this->wordString.size();
}

const std::string& RoundWordUI::getString() {
    return this->wordString;
}

void RoundWordUI::changeWord(std::int32_t index) {
    this->wordString = Dictionary::getInstance().at(index).word;
    this->loadWordTexture();
}

void RoundWordUI::loadWordTexture() {
    this->letters.clear();
    // to handle characters like ñ or á
    std::wstring wide_word = wStrConverter.from_bytes(this->wordString);
    for (unsigned int i = 0; i < wide_word.length(); ++i) {
        sf::Texture letterTexture;
        // obtain texture of a character
        loadLetterTexture(i, letterTexture, wide_word);
        // save in the textures vector
        this->letters.push_back(letterTexture);
    }
}

void RoundWordUI::loadWordFromString(const std::string& newWord) {
    // Set the new word
    this->wordString = newWord;
    // Load textures for each character in the word
    this->loadWordTexture();
}
