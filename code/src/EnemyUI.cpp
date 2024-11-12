#include "EnemyUI.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

EnemyUI::EnemyUI(Vector2f spawnPoint, const std::string& textureFile, std::int32_t corx, std::int32_t cory)
    :
    EntityUI(spawnPoint) {
    this->scaledPosition = Vector2<int32_t>(corx, cory);
    this->position = Vector2<int32_t>((corx-1)*32, (cory - 1) * 32);
    this->movementFactor[0] = 0;
    this->movementFactor[1] = 1;
    // Load textures
    if (!rightTexture.loadFromFile(textureFile)) {
        std::cerr << "Error al cargar la textura del enemigo." << std::endl;
    }
    if (!leftTexture.loadFromFile(textureFile)) {
        std::cerr << "Error al cargar la textura del personaje." << std::endl;
    }
    // Right texture as default
    this->sprite.setTexture(rightTexture);
}

int32_t EnemyUI::getRandom(int32_t min, int32_t max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int32_t> dist(min, max);
    return dist(gen);
}

void EnemyUI::changeDirection() {
    std::int32_t numrandom = this->getRandom(1, 4);
    if (numrandom == 1) {
        key = 'A'; //A
    }
    else {
        if (numrandom == 2) {
            key = 'W'; //W
        }
        else {
            if (numrandom == 3) {
                key = 'D'; //D
            }
            else {
                if (numrandom == 4) {
                    key = 'S'; //S
                }
            }
        }
    }
}

void EnemyUI::actionEnemy(RenderWindow& window) {
    std::int32_t xcords = this->getScale().x;
    std::int32_t ycords = this->getScale().y;
    std::cout << xcords << '\n';
    std::cout << ycords << '\n';
    std::cout << this->getPosition().x << ',' << this->getPosition().y << '\n';
    std::int32_t input = 0;
    if (((this->getPosition().x + 32) % 32 == 0)
        && ((this->getPosition().y + 32) % 32 == 0)) {
        // Player Input
        this->changeDirection();
        input = movInput(movementFactor, key);
    }
    if (input != 2) {
        if (checkColision(movementFactor, xcords, ycords) == 0
            || checkColision(movementFactor, xcords, ycords) == 2) {
            //this->changeDirection();
            this->move(window, movementFactor);
        }
      }
        
    
}
