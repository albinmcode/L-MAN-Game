#include "WordUI.hpp"
#include <iostream>

WordUI::WordUI(sf::Vector2f spawnPoint, const std::vector<std::string>& texturePaths, const std::vector<int>& controlValues)
    : spawnPoint(spawnPoint), controlValues(controlValues) {

    // Cargar cada textura desde los archivos proporcionados en texturePaths
    for (const auto& path : texturePaths) {
        sf::Texture texture;
        if (!texture.loadFromFile(path)) {
            std::cerr << "Error al cargar la textura: " << path << std::endl;
        } else {
            textures.push_back(texture); // Agregar la textura cargada al vector
        }
    }
}

void WordUI::draw(sf::RenderWindow& window) {
    float xOffset = 32.0f;  
    float yOffset = 32.0f;  
    int lettersPerLine = 22; 

    for (size_t i = 0; i < textures.size(); ++i) {
        // Dibujar solo si el valor de control en la posición actual es 0
        if (controlValues[i] == 0) {
            sf::Sprite letterSprite;
            letterSprite.setTexture(textures[i]); // Asignar la textura correspondiente

            // Calcular la posición en función de la línea y la columna actual
            float xPosition = spawnPoint.x + (i % lettersPerLine) * xOffset;
            float yPosition = spawnPoint.y + (i / lettersPerLine) * yOffset;

            letterSprite.setPosition(xPosition, yPosition);
            letterSprite.setScale(1.5f, 1.5f);
            window.draw(letterSprite);
        }
    }
}
int WordUI::getRandomIndex() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 25);
    return dis(gen);
}

std::string WordUI::getLetter(int index){
    const std::string letterSpanish[26] = {
        "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"
    };
    return letterSpanish[index];
}

std::vector<std::string> WordUI::createLetterTextures() {
    std::vector<std::string> letters;
    for(int i = 0; i < 243; i++) {
        letters.push_back("assets/img/fuente/" + getLetter(getRandomIndex()) + ".png");
    }
    return letters;
}

void WordUI::removeLetter(size_t index) {
    if (index < textures.size()) {
        textures[index] = sf::Texture();  // Reemplaza la textura en el índice especificado con una textura vacía
    }
}


std::vector<int> WordUI::index() {
    return {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
            0,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1,0,
            0,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,0,1,0,1,0,
            0,1,0,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,
            0,1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,0,
            0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,0,0,0,0,0,
            0,1,0,1,1,1,1,0,1,1,1,1,1,0,1,0,0,0,1,0,1,0,
            0,1,1,1,0,0,0,0,0,1,1,1,0,0,1,1,1,1,1,0,1,0,
            0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
            0,1,0,1,0,0,0,1,0,1,1,1,0,1,1,1,1,1,1,1,1,0,
            0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0};
}