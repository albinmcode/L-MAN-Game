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
	// Method to decrease the number of available hearts when the player dies
	void winPoint();
protected:
	sf::Texture digitTexture;
	sf::Sprite hundred;
	sf::Sprite ten;
	sf::Sprite unit;
	// amount of points obtained
	int pointCount;
};
