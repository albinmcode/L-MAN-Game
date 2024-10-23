#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class PlayerUI {
 public:
	
	// Default constructor
	PlayerUI();
	/// <summary>
	/// Changes player coordinates according to the recieved parameters
	/// </summary>
	/// <param name="window">
	/// Window rendered to draw over
	/// </param>
	/// <param name="movementFactor">
	/// Two 1 byte numbers that indicate the increment factor for width and height.
	/// Negatives indicate decrement
	/// </param>
	void draw(RenderWindow& window, const int (&movementFactor)[2]);
 private:
	Texture rightTexture;
	Texture leftTexture;
	Sprite playerSprite;
};