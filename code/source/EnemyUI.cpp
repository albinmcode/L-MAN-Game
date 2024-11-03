#include "EnemyUI.hpp"
#include <iostream>

EnemyUI::EnemyUI(Vector2f spawnPoint, const std::string& textureFile)
    : EntityUI(spawnPoint) {
    // Load textures
    if (!rightTexture.loadFromFile(textureFile)) {
        std::cerr << "Error al cargar la textura del enemigo." << std::endl;
    }
    // Right texture as default
    this->sprite.setTexture(rightTexture);
}