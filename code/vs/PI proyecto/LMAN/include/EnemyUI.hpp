#pragma once
#include <SFML/Graphics.hpp>

#include "EntityUI.hpp"
#include <random>
extern "C" std::int32_t movInput(std::int32_t*, std::int8_t);
extern "C" std::int32_t checkObstacleHorizontal(std::int32_t* playerCoords, std::int32_t* enemyCoords);
extern "C" std::int32_t checkObstacleVertical(std::int32_t* playerCoords, std::int32_t* enemyCoords);

using namespace sf;

class EnemyUI : public EntityUI {
public:
	// Default constructor
	EnemyUI(Vector2f spawnPoint, const std::string& textureFile, std::int32_t corx, std::int32_t cory, EntityUI& target); //Initializes the resources and positions needed for the enemy
	void actionEnemy(RenderWindow& window); // Perform the movement, with different directions
	
private:
	static int32_t getRandom(std::int32_t min, std::int32_t max); //Generates a random number with the computer clock
	std::int8_t key=2; //Save the enemy's new address
	EntityUI& target; // target entity to chase
	void changeDirection(std::int32_t numrandom); //Change the random number to its respective letter in ascii and then use movinput
	std::int32_t playerCoord[2] = { 0 };
	std::int32_t enemyCoord[2] = { 0 };
};