#pragma once
#include <SFML/Graphics.hpp>

#include "EntityUI.hpp"

extern "C" std::int32_t movInput(std::int32_t*, std::int8_t);

using namespace sf;

class PlayerUI : public EntityUI {
 public:
	// Default constructor
	PlayerUI(Vector2f spawnPoint);
	void action(RenderWindow& window, std::int8_t key);
	// flag value for collection elements on the map
	const bool collectChr();

 private:
	 // flag that indicates if the player pressed the specified button to collect a letter
	 bool collectFlag;
};
