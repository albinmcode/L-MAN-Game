#pragma once
#include <SFML/Graphics.hpp>

#include "EntityUI.hpp"
#include <random>
extern "C" std::int32_t movInput(std::int32_t*, std::int8_t);

using namespace sf;

class EnemyUI : public EntityUI {
public:
	// Default constructor
	EnemyUI(Vector2f spawnPoint, const std::string& textureFile, std::int32_t corx, std::int32_t cory); //Initializes the resources and positions needed for the enemy
	void actionEnemy(RenderWindow& window); // Perform the movement, with different directions
	
private:
	static int32_t getRandom(std::int32_t min, std::int32_t max); //Generates a random number with the computer clock
	std::int8_t key=2; //Save the enemy's new address
	void changeDirection(); //Change the random number to its respective letter in ascii and then use movinput
};