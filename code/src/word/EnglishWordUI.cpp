#include "EnglishWordUI.hpp"
#include <iostream>

#include "Dictionary.hpp"

EnglishWordUI::EnglishWordUI(int yCord)
: RoundWordUI(yCord) 
, objectiveWord(" ") {}

void EnglishWordUI::changeWord(std::int32_t index) {
	this->objectiveWord = Dictionary::getInstance().at(index).translation;
}

const size_t EnglishWordUI::getTotalLength() {
	return this->objectiveWord.size();
}

const std::string& EnglishWordUI::getObjective() {
	return this->objectiveWord;
}

void EnglishWordUI::collectChr(char collected) {
	this->wordString += collected;
}

bool EnglishWordUI::validCollected(size_t size) {
	try {
		for (size_t index = 0; index < size; ++index) {
			if (this->objectiveWord.at(index) != this->wordString.at(index)) {
				return false;
			}
		}
	}
	catch (std::out_of_range err){
		std::cerr << "validCollected: Index out of bounds";
	}
	return true;
}

bool EnglishWordUI::completedWord() {
	if (this->objectiveWord.size() == this->wordString.size()) {
		return this->validCollected(this->objectiveWord.size());
	}
	return false;
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
