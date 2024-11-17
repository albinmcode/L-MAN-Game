#pragma once
#include <SFML/Graphics.hpp>
#include "RoundWordUI.hpp"

class EnglishWordUI : public RoundWordUI {
public:
	// Default constructor
	EnglishWordUI(int yCord);
	// Set a new word string
	void changeWord(std::int32_t index) override;
	// Getters
	const int getTotalLength();
	const char* getObjective();
	// Append a collected char
	void collectChr(char collected);
	// Pop the last element
	void popCollected();
	// Reload textures
	void refreshWord();

private:
	// Restart collected word buffer
	std::string objectiveWord;
};