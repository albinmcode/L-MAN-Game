#ifndef WORDUI_HPP
#define WORDUI_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <random>

class WordUI {
public:
    WordUI(sf::Vector2f spawnPoint, const std::vector<int>& controlValues);
    // draw letters in every empty space of the map
    void draw(sf::RenderWindow& window);
    // Vector that contains the path for every letter texture file
    std::vector<std::string> createLetterTextures();
    // Obtain a random letter
    int getRandomIndex();
    std::string getLetter(int index);
    // Remove an especified letter texture
    void removeLetter(size_t index);
    // Restar letters with a new random set
    void restartLetters();
    // Matrix with the map, empty, wall and dictionary conditions
    std::vector<int> controlValues;
    std::vector<int> index();
    std::vector<int> values;


private:
    sf::Vector2f spawnPoint;
    std::vector<sf::Texture> textures; // Vector para almacenar las texturas de las letras
};

#endif