#ifndef GAMEMAPUI
#define GAMEMAPUI

#include <SFML/Graphics.hpp>

using namespace sf;

class GameMap {
public:
    // default constructor
    GameMap();
    // Game events
    void start(RenderWindow& window);
    void handleEvent(RenderWindow& window, Event& event,bool& isPlaying);
    // update the window
    void draw(RenderWindow& window);

private:
    Texture backgroundTexture;
    Sprite backgroundSprite;
};

#endif // !GAMEMAPUI
