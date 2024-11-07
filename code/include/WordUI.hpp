#pragma once
#include <SFML/Graphics.hpp>

class WordUI {
public:
	// Default constructor
	WordUI(sf::Vector2f spawnPoint);
	// Draw points
	void draw(sf::RenderWindow& window);
	// Load an specified digit according to the pointsCount
	void loadWord(sf::Sprite& wordSprite);
protected:
	sf::Texture wordTexture;
	sf::Sprite word;
	// amount of points obtained
};
