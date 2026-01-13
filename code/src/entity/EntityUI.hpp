#pragma once
#include <cstdint>
#include <SFML/Graphics.hpp>

/**
/ Validates the movement factor according to the player coordinates and the map
*/
extern "C"	std::int32_t checkColision(std::int32_t * movementFactor,
	std::int32_t xCords, std::int32_t yCords);

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
	void move(RenderWindow& window);
	void draw(RenderWindow& window);
	// No modifiable reference to the scaled entity position 
	const Vector2<std::int32_t>& getScale();
	// No modifiable reference to the entity position 
	const Vector2<std::int32_t>& getPosition();
	// Method to increment the position vector according to the movement factor
	void updatePosition();
	// Restart position according to the given offset
	void restartPosition(std::int32_t xOffset, std::int32_t yOffset);
	// Set to no movement
	void restartMovement();

protected:
	Texture rightTexture;
	Texture leftTexture;
	Texture vulnerableTexture;
	Sprite sprite;
	Vector2<std::int32_t> position;
	Vector2<std::int32_t> scaledPosition;
	std::int32_t movementFactor[2];
	std::int32_t speed = 1;
};

/// @brief Establish the directio to take on {W,A,S,D}
/// @param movementFactor two dimensional vector that indicates a direction
/// @param key input key
void movInput(int32_t* movementFactor, int8_t key);
