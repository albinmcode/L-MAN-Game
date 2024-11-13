#pragma once
#include <SFML/Graphics.hpp>

extern "C" const char* getWordByIndex(std::int32_t index);

class RoundWordUI {
public:
	// Default constructor
	RoundWordUI(int x);
	// Draw points
	void draw(sf::RenderWindow& window);
	// Load texture from a character indexed from the word
	sf::Texture loadChrTexture(std::int32_t index);
	// Set a new word string
	void changeWord(std::int32_t index);
	// Load actual word string characters texture
	std::vector<sf::Texture> loadWordTexture();

	void loadWordFromString(const std::string& newWord);
protected:
	std::string wordString;
	sf::Texture wordSTexture;
	sf::Sprite wordSprite;
	std::vector<sf::Texture> letters;
	int yCord;
};
