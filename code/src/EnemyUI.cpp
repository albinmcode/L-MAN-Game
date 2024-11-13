#include "EnemyUI.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

/*
Constructor initializes the enemy object at a given spawn point, sets the scaled position
and initial pixel position based on grid coordinates, sets the initial movement direction,
and loads textures for the enemy. Sets the right texture as default for the sprite.
*/
EnemyUI::EnemyUI(Vector2f spawnPoint, const std::string& textureFile, std::int32_t corx, std::int32_t cory)
    : EntityUI(spawnPoint) {
    this->scaledPosition = Vector2<int32_t>(corx, cory);
    this->position = Vector2<int32_t>((corx-1) * 32, (cory - 1) * 32);
    this->movementFactor[0] = 0;
    this->movementFactor[1] = 1;
    if (!rightTexture.loadFromFile(textureFile)) {
        std::cerr << "Error loading enemy texture." << std::endl;
    }
    if (!leftTexture.loadFromFile(textureFile)) {
        std::cerr << "Error loading player texture." << std::endl;
    }
    this->sprite.setTexture(rightTexture);
}

/*
Generates and returns a random integer between the specified min and max values.
Uses std::random_device and std::mt19937 to ensure randomness.
*/
int32_t EnemyUI::getRandom(int32_t min, int32_t max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int32_t> dist(min, max);
    return dist(gen);
}

/*
Randomly changes the enemy's movement direction by assigning one of four possible
directional keys ('A', 'W', 'D', or 'S') based on a randomly generated integer.
*/
void EnemyUI::changeDirection() {
    std::int32_t numrandom = this->getRandom(1, 4);
    if (numrandom == 1) {
        key = 'A'; // Move left
    } else if (numrandom == 2) {
        key = 'W'; // Move up
    } else if (numrandom == 3) {
        key = 'D'; // Move right
    } else if (numrandom == 4) {
        key = 'S'; // Move down
    }
}

/*
Controls enemy behavior on each game cycle. Retrieves current grid coordinates and prints them for debugging.
If the enemy is aligned within the grid (multiple of 32), it changes direction and calculates the new movement direction.
If no collision is detected, it moves the enemy sprite within the game window according to movementFactor.
*/
void EnemyUI::actionEnemy(RenderWindow& window) {
    std::int32_t xcords = this->getScale().x;
    std::int32_t ycords = this->getScale().y;
    //std::cout << xcords << '\n';
    //std::cout << ycords << '\n';
    //std::cout << this->getPosition().x << ',' << this->getPosition().y << '\n';
    std::int32_t input = 0;
    int32_t collisionStatus = checkColision(movementFactor, xcords, ycords);
    if (collisionStatus == 1) {
        // Si hay una colisión, cambia de dirección
        this->changeDirection();
        input = movInput(movementFactor, key);  // Actualiza movimiento después del cambio de dirección
    }
    else {
        // Si no hay colisión o es una salida (2), permite el movimiento sin cambiar de dirección
        this->move(window, movementFactor);
    }
}

