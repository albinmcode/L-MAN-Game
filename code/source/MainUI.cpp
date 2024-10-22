#include <SFML/Graphics.hpp>
#include <iostream>

#include "MenuUI.hpp"
#include "GameMapUI.hpp"

int main() {
    RenderWindow window(VideoMode(455, 256), "L-MAN Menu");
    // window icon
    sf::Image icon;
    if (!icon.loadFromFile("assets/lman_right.png"))
        return -1;
    window.setIcon(16, 16, icon.getPixelsPtr());

    // Create menu
    Menu menu;
    bool isPlaying = false;
    // Create map
    GameMap gameMap;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            menu.handleEvent(window, event, isPlaying);
            if (isPlaying) {
               gameMap.start(window);
            }
        }

        window.clear();
        menu.draw(window);
        window.display();
    }

    return 0;
}
