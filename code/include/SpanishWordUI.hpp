#pragma once
#include <SFML/Graphics.hpp>

class WordSUI {
public:
	// Default constructor
	WordSUI(sf::Vector2f spawnPoint,std::string spanishWord);
	// Draw points
	void draw(sf::RenderWindow& window);
	sf::Texture* loadWordS(int index);
private:
	std::string spanishWord;
	sf::Texture wordSTexture;
	sf::Sprite wordS;
	std::vector<sf::Texture*> letters;
};