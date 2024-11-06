#pragma once
#include <SFML/Graphics.hpp>

class WordSUI {

public:
std::string spanishWord;

public:
	// Default constructor
	WordSUI(sf::Vector2f spawnPoint,std::string spanishWord);
	// Draw points
	void draw(sf::RenderWindow& window);
	void loadWordS(sf::Sprite& wordSSprite,int index);
protected:
	sf::Texture wordSTexture;
	sf::Sprite wordS;
	// amount of points obtained
};