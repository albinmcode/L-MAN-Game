#ifndef LETTERSUI_HPP
#define LETTERSUI_HPP
#define ELEMENTS_ROWS 22
#define ELEMENTS_COLS 11
#define ELEMENTSMATRIX_SIZE ELEMENTS_ROWS*ELEMENTS_COLS

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <random>

class LettersUI {
public:
    LettersUI(sf::Vector2f spawnPoint);
    // draw letters in every empty space of the map
    void draw(sf::RenderWindow& window);
    // Vector that contains the path for every letter texture file
    std::vector<std::string> createLetterTextures();
    // Obtain a random value between the minimum and maximum
    int getRandomIndex(int min, int max);
    // Obtain a letter from the alphabet
    const char getLetter(size_t index);
    // Obtain an element from the elementsMap
    const char& getElement(const size_t row, const size_t column);
    const char& getElement(const size_t index);
    // Save an element into the elementsMap
    void saveElement(const char element, const size_t row, const size_t column);
    void saveElement(const char element, const size_t index);
    // Remove an specified letter texture
    void removeLetter(const size_t row, const size_t column);
    // Restart letters with a new random set
    void restartLetters();

 private:
     // Set empty the letters and dictionaries map
     void resetElements();

private:
    sf::Vector2f spawnPoint;
    // Vector para almacenar las texturas de las letras
    std::vector<sf::Texture> textures;
    // Matrix to save the elements on the map
    char elementsMap[ELEMENTSMATRIX_SIZE] = {0};
    char emptyElementsMap[ELEMENTSMATRIX_SIZE] = {
         0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,3
        ,0,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1,0
        ,0,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,0,1,0,1,0
        ,0,1,0,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0
        ,0,1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,0
        ,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,0,0,0,0,0
        ,0,1,0,1,1,1,1,0,1,1,1,1,1,0,1,0,0,0,1,0,1,0
        ,0,1,1,1,3,0,0,0,0,1,1,1,0,0,1,1,1,1,1,0,1,0
        ,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0
        ,0,1,0,1,0,0,0,1,0,1,1,1,0,1,1,1,1,1,1,1,1,0
        ,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0
    };
};

#endif // LETTERSUI_HPP