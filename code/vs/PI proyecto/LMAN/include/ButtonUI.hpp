#ifndef BUTTONUI_HPP
#define BUTTONUI_HPP

#include <SFML/Graphics.hpp>

class Button {
public:
    Button(const sf::Vector2f& position, const std::string& textureFile, const sf::Vector2f& size = sf::Vector2f(100, 50));
    
    void draw(sf::RenderWindow& window);
    bool isMouseOver(const sf::RenderWindow& window) const;
    void setSize(const sf::Vector2f& size);  // Método para ajustar el tamaño

private:
    sf::RectangleShape buttonShape;
    sf::Texture buttonTexture;
};

#endif
