#pragma once
#include <SFML/Graphics.hpp>

#include "EntityUI.hpp"
#include <random>
extern "C" std::int32_t movInput(std::int32_t*, std::int8_t);

using namespace sf;

class EnemyUI : public EntityUI {
public:
	// Default constructor
	EnemyUI(Vector2f spawnPoint, const std::string& textureFile, std::int32_t corx, std::int32_t cory);
	void actionEnemy(RenderWindow& window);
	
private:
	static int32_t getRandom(std::int32_t min, std::int32_t max);
	std::int8_t key=2;
	void changeDirection();
};