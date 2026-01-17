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

char LettersUI::getLetter(size_t index) const {
    const char letterSpanish[26] = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
    };
    if (index >= 26) {
        std::cerr << "Índice fuera de rango en getLetter: " << index << std::endl;
        return 0;
    }
    return letterSpanish[index];
}

char LettersUI::getElement(const size_t row, const size_t column) const {
    size_t index = row * ELEMENTS_ROWS + column;
    return this->getElement(index);
}

char LettersUI::getElement(const size_t index) const {
    if (index < ELEMENTSMATRIX_SIZE) {
        return this->elementsMap[index];
    }
    return 1;  // wall value
}

void LettersUI::saveElement(const char element, const size_t row, const size_t column) {
    size_t index = row * ELEMENTS_ROWS + column;
    this->saveElement(element, index);
}

void LettersUI::saveElement(const char element, const size_t index) {
    if (index < ELEMENTSMATRIX_SIZE) {
        this->elementsMap[index] = element;
    }
}

std::vector<std::string> LettersUI::createLetterTextures() {
    std::vector<std::string> texturesPath;
    int n = 0;
    int mod = 0;
    std::string chr = "";
    int inv = 25;
    try {
        for (int i = 0; i < 242; i++) {
            n = getRandomIndex(0, 25);
            if (getElement(i) == 1) { // discard walls
                texturesPath.push_back(" ");
            } 
            // set "diccionario" texture
            else if (getElement(i) == 3) {
                texturesPath.push_back("assets/img/diccionario.png");
            }
            // set random letter texture
            else if ((i % 5 == 0) && (mod < 25) && (getElement(i) == 0)) {
                saveElement(this->getLetter(mod), i);
                chr = getElement(i);
                texturesPath.push_back("assets/img/fuente/" + chr + ".png");
                ++mod;
            }
            else if ((i % 5 == 3) && (inv > 0) && (getElement(i) == 0)) {
                saveElement(this->getLetter(inv), i);
                chr = getElement(i);
                texturesPath.push_back("assets/img/fuente/" + chr + ".png");
                --inv;
            }
            else {
                saveElement(this->getLetter(n), i);
                chr = getElement(i);
                texturesPath.push_back("assets/img/fuente/" + chr + ".png");
            }

        }
    }
    catch (std::out_of_range& err){
        std::cerr << "Out of range error: " << err.what() << '\n';
    }
    return texturesPath;
}

void LettersUI::removeLetter(const size_t row, const size_t column) {
    size_t index = row * ELEMENTS_ROWS + column;
    this->saveElement(0, index);
    if (index < textures.size()) {
        textures[index] = sf::Texture();  // Reemplaza la textura en el índice especificado con una textura vacía
    }
}

void LettersUI::resetElements() {
    for (size_t index = 0; index < ELEMENTSMATRIX_SIZE; ++index) {
        this->elementsMap[index] = this->emptyElementsMap[index];
    }
}

void LettersUI::restartLetters() {
    // Restore vectors data
    this->resetElements();
    this->textures.clear();
    this->textures.shrink_to_fit();
    std::vector<std::string> texturesPath = this->createLetterTextures();
    // Cargar cada textura desde los archivos proporcionados en texturePaths
    for (const std::string& path : texturesPath) {
        sf::Texture texture = sf::Texture();
        if (path != " "){
            if (!texture.loadFromFile(path)) {
                std::cerr << "Error al cargar la textura: " << path << std::endl;
            }
        }
        textures.push_back(texture); // Agregar la textura cargada al vector
    }
}
