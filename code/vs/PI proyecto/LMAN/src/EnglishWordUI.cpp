#include "EnglishWordUI.hpp"
#include <iostream>

EnglishWordUI::EnglishWordUI(int yCord)
: RoundWordUI(yCord) 
, objectiveWord(" ") {}

void EnglishWordUI::changeWord(std::int32_t index) {
	this->objectiveWord = getWordByIndex(index);
}

const int EnglishWordUI::getTotalLength() {
	return this->objectiveWord.size();
}

const char* EnglishWordUI::getObjective() {
	return this->objectiveWord.c_str();
}

void EnglishWordUI::collectChr(char collected) {
	this->wordString += collected;
}

void EnglishWordUI::popCollected() {
	if (!this->wordString.empty()) this->wordString.pop_back();
}

void EnglishWordUI::winChr() {
	size_t index = this->wordString.size();
	if (index < this->objectiveWord.size()) {
		this->collectChr(this->objectiveWord.at(index));
		this->refreshWord();
	}
}

void EnglishWordUI::refreshWord() {
	this->letters = loadWordTexture();
}
