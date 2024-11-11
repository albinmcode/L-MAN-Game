#pragma once
#include <SFML/Graphics.hpp>

/**
/ Validates the movement factor according to the player coordinates and the map
/ checkColision(movementFactor, xcords, ycords)
*/
extern "C" std::int32_t checkColision(std::int32_t*, std::int32_t, std::int32_t);

using namespace sf;

class EntityUI {
public:

	// Default constructor
	EntityUI(Vector2f spawnPoint);
	/// <summary>
	/// Change entity coordinates according to the recieved parameters
	/// </summary>
	/// <param name="window">
	/// Window rendered to draw over
	/// </param>
	/// <param name="movementFactor">
	/// Two 1 byte numbers that indicate the increment factor for width and height.
	/// Negatives indicate decrement
	/// </param>
	void move(RenderWindow& window, const std::int32_t(&movementFactor)[2]);
	void draw(RenderWindow& window);
	// No modifiable reference to the scaled entity position 
	const Vector2<std::int32_t>& getScale();
	// No modifiable reference to the entity position 
	const Vector2<std::int32_t>& getPosition();
	// Method to increment the position vector according to the movement factor
	void updatePosition();
protected:
	Texture rightTexture;
	Texture leftTexture;
	Sprite sprite;
	Vector2<std::int32_t> position;
	Vector2<std::int32_t> scaledPosition;
	std::int32_t movementFactor[2];
};
