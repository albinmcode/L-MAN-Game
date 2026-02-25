#pragma once
#include <SFML/Graphics.hpp>
#include "RoundWordUI.hpp"

class EnglishWordUI : public RoundWordUI {
public:
	// Default constructor
	explicit EnglishWordUI(int yCord);
	// Set a new word string
	void changeWord(std::int32_t index) override;
	// Getters
	size_t getTotalLength() const;
	const std::string& getObjective();
	// Append a collected char
	void collectChr(char collected);
	// Control valid letter collection
	bool validCollected(size_t size);
	bool completedWord();
	// Pop the last element
	void popCollected();
	// Obtain the next letter from the objective word
	void winChr();
	// Reload textures
	void refreshWord();

private:
	// Restart collected word buffer
	std::string objectiveWord;
};