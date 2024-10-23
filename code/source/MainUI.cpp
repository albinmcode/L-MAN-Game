#include <SFML/Graphics.hpp>
#include "MenuUI.hpp"
#include "GameMapUI.hpp"

using namespace sf;

int main() {

    sf::Image icon;
    if(!icon.loadFromFile("assets/img/lman_right.png")) return -1;

    // Crear la ventana con resolución 455x256 y sin opción de redimensionar
    RenderWindow window(VideoMode(910, 512), "Juego SFML", Style::Titlebar | Style::Close);
    window.setFramerateLimit(60);

    Menu menu;
    GameMap gameMap;
    bool isPlaying = false;
    bool backToMenu = false;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            menu.handleEvent(window, event, isPlaying, backToMenu);
        }

        window.clear();
        if (isPlaying) {
            gameMap.run(window);
        } else {
            menu.draw(window);
        }
        window.display();
    }

    return 0;
}
