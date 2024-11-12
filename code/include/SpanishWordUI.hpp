#pragma once
#include <SFML/Graphics.hpp>

extern "C" const char* getWordByIndex(std::int32_t index);

class WordSUI {
public:
	// Default constructor
	WordSUI(sf::Vector2f spawnPoint);
	// Draw points
	void draw(sf::RenderWindow& window);
	// Load texture from a character indexed from the word
	sf::Texture loadChrTexture(std::int32_t index);
	// Set a new word string
	void changeWord(std::int32_t index);
	// Load actual word string characters texture
	std::vector<sf::Texture> loadWordTexture();
private:
	std::string spanishWord;
	sf::Texture wordSTexture;
	sf::Sprite wordS;
	std::vector<sf::Texture> letters;
};