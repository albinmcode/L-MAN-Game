#include "WordUI.hpp"
#include <iostream>

WordUI::WordUI(sf::Vector2f spawnPoint, const std::vector<int>& controlValues)
    : spawnPoint(spawnPoint), controlValues(controlValues) {
    std::vector<std::string> texturesPath = this->createLetterTextures();
    // Cargar cada textura desde los archivos proporcionados en texturePaths
    for (const std::string path : texturesPath) {
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

    for (size_t i = 0; i < textures.size()-1; ++i) {
        // Dibujar solo si el valor de control en la posición actual es:
        // 0 (caracter)
        // 3 (diccionario)
        if (controlValues[i] == 0 || controlValues[i] == 3) {
            sf::Sprite letterSprite;
            letterSprite.setTexture(textures[i]); // Asignar la textura correspondiente

            // Calcular la posición en función de la línea y la columna actual
            float xPosition = spawnPoint.x + (i % lettersPerLine) * xOffset;
            float yPosition = spawnPoint.y + (i / lettersPerLine) * yOffset;
            letterSprite.setPosition(xPosition, yPosition);

            // Diccionario
            if (controlValues[i] == 3) {
                letterSprite.setScale(2, 2);
                letterSprite.move(-8, -8);
            }
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

std::string WordUI::getLetter(int index) {
    const std::string letterSpanish[27] = {
        "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "3"
    };
    if (index < 0 || index >= 27) {
        std::cerr << "Índice fuera de rango en getLetter: " << index << std::endl;
        return "";
    }
    return letterSpanish[index];
}

std::vector<std::string> WordUI::createLetterTextures() {
    std::vector<std::string> letters;
    int n = 0;
    int mod = 0;
    int inv = 25;
    for(int i = 1; i < 243; i++) {
        n = getRandomIndex();
        // set diccionario texture
        if (this->index()[i-1] == 3) {
            values.push_back(26);
            letters.push_back("assets/img/diccionario.png");
        }
        // set random letter texture
        else if((i%5==0) && (mod<25) && (controlValues[i]==0)) {
            values.push_back(mod);
            letters.push_back("assets/img/fuente/" + getLetter(mod) + ".png");
            mod++;
            std::cout <<"-"<< i;
        }
        else if ((i % 5 == 3) && (inv >0 ) && (controlValues[i] == 0)) {
            values.push_back(inv);
            letters.push_back("assets/img/fuente/" + getLetter(inv) + ".png");
            inv--;
            std::cout << "-" << i;
        }
        else {
            values.push_back(n);
            letters.push_back("assets/img/fuente/" + getLetter(n) + ".png");
        }
        
    }
    return letters;
}

void WordUI::removeLetter(size_t index) {
    if (index < textures.size()) {
        textures[index] = sf::Texture();  // Reemplaza la textura en el índice especificado con una textura vacía
    }
}


std::vector<int> WordUI::index() {
    // 1 = wall, 0 = empty, 3 = diccionario
    return {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,3,
            0,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1,0,
            0,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,0,1,0,1,0,
            0,1,0,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,
            0,1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,0,
            0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,0,0,0,0,0,
            0,1,0,1,1,1,1,0,1,1,1,1,1,0,1,0,0,0,1,0,1,0,
            0,1,1,1,3,0,0,0,0,1,1,1,0,0,1,1,1,1,1,0,1,0,
            0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
            0,1,0,1,0,0,0,1,0,1,1,1,0,1,1,1,1,1,1,1,1,0,
            3,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0};
}