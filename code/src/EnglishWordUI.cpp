#include "EnglishWordUI.hpp"
#include <iostream>

EnglishWordUI::EnglishWordUI(int x)
: RoundWordUI(x) {}

void EnglishWordUI::restartBuffers() {
	this->palabra.clear();
	this->word = "";
	this->length = 1;
	this->wordString.clear();
	this->wordSprite.setTexture(sf::Texture());
	this->loadWordFromString(" ");
}

