#pragma once
#include <SFML/Graphics.hpp>

class PointsUI {
public:
	// Default constructor
	PointsUI(sf::Vector2f spawnPoint);
	// Draw points
	void draw(sf::RenderWindow& window);
	// Load an specified digit according to the pointsCount
	void loadDigit(sf::Sprite& digitSprite,const int place);
	// Method to increment by one the obtained points counter
	void winPoint();
	// Restart to zero the pointsCounter
	void restart();
protected:
	sf::Texture digitTexture;
	sf::Sprite hundred;
	sf::Sprite ten;
	sf::Sprite unit;
	// amount of points obtained
	int pointCount;
};
