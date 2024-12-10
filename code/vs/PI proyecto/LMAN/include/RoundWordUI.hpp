#pragma once
#include <SFML/Graphics.hpp>

extern "C" const char* getWordByIndex(std::int32_t index);

class RoundWordUI {
public:
	// Default constructor
	RoundWordUI(int yCord);
	// Draw points
	void draw(sf::RenderWindow& window);
	// Load texture from a character indexed from the word
	sf::Texture loadChrTexture(std::int32_t index);
	// Obtain wordString size
	const size_t getlength();
	// Obtain wordString
	const std::string& getString();
	// Set a new word string
	virtual void changeWord(std::int32_t index);
	// Load actual word string characters texture
	std::vector<sf::Texture> loadWordTexture();
	// Load Word textures from a new word or from the the actual wordString
	void loadWordFromString(const std::string& newWord = " ");

protected:
	std::string wordString;
	sf::Texture wordSTexture;
	sf::Sprite wordSprite;
	std::vector<sf::Texture> letters;
	int yCord;
};
