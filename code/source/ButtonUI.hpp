#ifndef BUTTONUI_HPP
#define BUTTONUI_HPP

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Button {
public:
    Button(const Vector2f& position, const string& textureFile);

    void draw(sf::RenderWindow& window);
    bool isMouseOver(const sf::RenderWindow& window) const;

private:
    RectangleShape buttonShape;
    Texture buttonTexture;
};

#endif
