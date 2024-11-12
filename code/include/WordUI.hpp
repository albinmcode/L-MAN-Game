#ifndef WORDUI_HPP
#define WORDUI_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <random>

class WordUI {
public:
    WordUI(sf::Vector2f spawnPoint, const std::vector<std::string>& texturePaths, const std::vector<int>& controlValues);
    void draw(sf::RenderWindow& window);
    std::vector<std::string> createLetterTextures();
    int getRandomIndex();
    std::string getLetter(int index);
    void removeLetter(size_t index);
    std::vector<int> controlValues;
    std::vector<int> index();


private:
    sf::Vector2f spawnPoint;
    std::vector<sf::Texture> textures; // Vector para almacenar las texturas de las letras
};

#endif