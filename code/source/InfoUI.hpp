#ifndef INFOUI
#define INFOUI

#include <SFML/Graphics.hpp>

using namespace sf;

class InfoPage {
public:
    // default constructor
    InfoPage();
    void handleEvent(RenderWindow& window, Event& event);
    // update the window
    void draw(RenderWindow& window);

private:
    Texture backgroundTexture;
    Sprite backgroundSprite;
};

#endif // !INFOUI