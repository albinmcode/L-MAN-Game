#include "LettersUI.hpp"
#include <iostream>

LettersUI::LettersUI(sf::Vector2f spawnPoint)
    : spawnPoint(spawnPoint) {
    // Load first set of letters
    this->restartLetters();
}

void LettersUI::draw(sf::RenderWindow& window) {
    float xOffset = 32.0f;
    float yOffset = 32.0f;
    int lettersPerLine = 22;

    for (size_t i = 0; i < textures.size(); ++i) {
        // Dibujar solo si el valor de control en la posición actual es:
        // (caracter)
        // (diccionario)
        if (getElement(i) != 1 || getElement(i) != 0) {
            sf::Sprite letterSprite;
            letterSprite.setTexture(textures[i]); // Asignar la textura correspondiente

            // Calcular la posición en función de la línea y la columna actual
            float xPosition = spawnPoint.x + (i % lettersPerLine) * xOffset;
            float yPosition = spawnPoint.y + (i / lettersPerLine) * yOffset;
            letterSprite.setPosition(xPosition, yPosition);

            // Diccionario
            if (getElement(i) == 3) {
                letterSprite.setScale(2, 2);
                letterSprite.move(-8, -8);
            }
            if (letterSprite.getTexture() != nullptr) {
                window.draw(letterSprite);
            }
        }
    }
}
int LettersUI::getRandomIndex(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);

    return dis(gen);
}

std::string LettersUI::getLetter(int index) {
    const std::string letterSpanish[27] = {
        "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "3"
    };
    if (index < 0 || index >= 27) {
        std::cerr << "Índice fuera de rango en getLetter: " << index << std::endl;
        return "";
    }
    return letterSpanish[index];
}

std::vector<std::string> LettersUI::createLetterTextures() {
    std::vector<std::string> letters;
    int n = 0;
    int mod = 0;
    std::string chr = "";
    int inv = 25;
    try {
        for (int i = 0; i < 242; i++) {
            n = getRandomIndex(0, 25);
            if (getElement(i) == 1) { // discard walls
                letters.push_back(" ");
            } 
            // set diccionario texture
            else if (getElement(i) == 3) {
                letters.push_back("assets/img/diccionario.png");
            }
            // set random letter texture
            else if ((i % 5 == 0) && (mod < 25) && (getElement(i) == 0)) {
                saveElement(static_cast<std::int8_t>((this->getLetter(mod)[0])), i);
                chr = getElement(i);
                letters.push_back("assets/img/fuente/" + chr + ".png");
                mod++;
                // std::cout <<"-"<< i;
            }
            else if ((i % 5 == 3) && (inv > 0) && (getElement(i) == 0)) {
                saveElement(static_cast<std::int8_t>((this->getLetter(inv)[0])), i);
                chr = getElement(i);
                letters.push_back("assets/img/fuente/" + chr + ".png");
                inv--;
                // std::cout << "-" << i;
            }
            else {
                saveElement(static_cast<std::int8_t>((this->getLetter(n)[0])), i);
                chr = getElement(i);
                letters.push_back("assets/img/fuente/" + chr + ".png");
            }

        }
    }
    catch (std::out_of_range& err){
        std::cerr << "Out of range error: " << err.what() << '\n';
    }
    return letters;
}

void LettersUI::removeLetter(size_t index) {
    if (index < textures.size()) {
        textures[index] = sf::Texture();  // Reemplaza la textura en el índice especificado con una textura vacía
    }
}

void LettersUI::restartLetters() {
    // Restore vectors data
    this->textures.clear();
    this->textures.shrink_to_fit();
    std::vector<std::string> texturesPath = this->createLetterTextures();
    // Cargar cada textura desde los archivos proporcionados en texturePaths
    for (const std::string path : texturesPath) {
        sf::Texture texture = sf::Texture();
        if (path != " "){
            if (!texture.loadFromFile(path)) {
                std::cerr << "Error al cargar la textura: " << path << std::endl;
            }
        }
        textures.push_back(texture); // Agregar la textura cargada al vector
    }
}
