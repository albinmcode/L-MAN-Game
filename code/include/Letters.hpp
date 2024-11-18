#ifndef LETTERSUI_HPP
#define LETTERSUI_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <random>

extern "C" {
    std::int32_t resetElementsMap();
    std::int32_t getElement(std::int32_t index);
    std::int32_t getElementXY(std::int32_t row, std::int32_t column);
    std::int32_t saveElement(std::int8_t value, std::int32_t index);
    std::int32_t saveElementXY(std::int8_t value, std::int32_t row, std::int32_t column);
}

class LettersUI {
public:
    LettersUI(sf::Vector2f spawnPoint);
    // draw letters in every empty space of the map
    void draw(sf::RenderWindow& window);
    // Vector that contains the path for every letter texture file
    std::vector<std::string> createLetterTextures();
    // Obtain a random letter
    int getRandomIndex(int min, int max);
    std::string getLetter(int index);
    // Remove an especified letter texture
    void removeLetter(size_t index);
    // Restar letters with a new random set
    void restartLetters();

private:
    sf::Vector2f spawnPoint;
    std::vector<sf::Texture> textures; // Vector para almacenar las texturas de las letras
};

#endif // LETTERSUI_HPP