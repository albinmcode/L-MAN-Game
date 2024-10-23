#include <SFML/Graphics.hpp>
#include "MenuUI.hpp"
#include "GameMapUI.hpp"

using namespace sf;

int main() {
    // Crear la ventana con resolución 455x256 y sin opción de redimensionar
    RenderWindow window(VideoMode(455, 256), "Juego SFML", Style::Titlebar | Style::Close);
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
            gameMap.start(window);
        } else {
            menu.draw(window);
        }
        window.display();
    }

    return 0;
}
