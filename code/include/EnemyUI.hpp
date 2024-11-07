#pragma once
#include <SFML/Graphics.hpp>

#include "EntityUI.hpp"

using namespace sf;

class EnemyUI : public EntityUI {
public:
	// Default constructor
	EnemyUI(Vector2f spawnPoint, const std::string& textureFile);
};