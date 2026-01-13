#pragma once
#include <SFML/Graphics.hpp>

#include "EntityUI.hpp"

using namespace sf;

class PlayerUI : public EntityUI {
 public:
	// Default constructor
	PlayerUI(Vector2f spawnPoint);
	void action(RenderWindow& window, std::int8_t& key);
	// flag value for collection elements on the map
	const bool collectChr();
	void setBoost();
	void setNormal();

 private:
	 // flag that indicates if the player pressed the specified button to collect a letter
	 bool collectFlag;
};
