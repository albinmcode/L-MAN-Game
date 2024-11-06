#pragma once
#include <SFML/Graphics.hpp>

class HeartsUI {
public:
	// Default constructor
	HeartsUI(sf::Vector2f spawnPoint);
	void draw(sf::RenderWindow& window);
	// Method to decrease the number of available hearts when the player dies
	void loseHeart();
protected:
	sf::Texture emptyTexture;
	sf::Texture filledTexture;
	sf::Sprite heart1;
	sf::Sprite heart2;
	sf::Sprite heart3;
	// amount of hearts remaining
	int heartsCount;
};
