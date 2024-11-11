#include <SFML/Graphics.hpp>
#include "MenuUI.hpp"
#include "GameMapUI.hpp"

using namespace sf;

int main() {

    sf::Image icon;
    if (!icon.loadFromFile("assets/img/lman_right.png")) return -1;

    // Crear la ventana con resolución 910x512 y sin opción de redimensionar
    RenderWindow window(VideoMode(910, 512), "L-MAN", Style::Titlebar | Style::Close);
    window.setFramerateLimit(60);

    Menu menu;

    // Usa un puntero inteligente único para asegurar la liberación automática de memoria
    std::unique_ptr<GameMap> gameMap = std::make_unique<GameMap>();
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
            gameMap->run(window);
        }
        else {
            menu.draw(window);
        }
        window.display();
    }

    return 0;
}
