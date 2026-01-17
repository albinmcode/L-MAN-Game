#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

#include "MenuUI.hpp"
#include "GameMapUI.hpp"

using namespace sf;

int main() {
    

    // Crear la ventana con resolución 910x512 y sin opción de redimensionar
    RenderWindow window(VideoMode(910, 512), "L-MAN", Style::Titlebar | Style::Close);
    // Icon
    sf::Image icon;
    if (!icon.loadFromFile("assets/img/lman_right.png")) {
        std::cerr << "Error al cargar icono: " << std::endl;
        return -1;
    }
    window.setIcon(32, 32, icon.getPixelsPtr());
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
            // Restablecer ventana escalable
            window.create(sf::VideoMode(910, 512), "L-MAN");
            window.setFramerateLimit(60);
            window.setIcon(32, 32, icon.getPixelsPtr());
            try {
                gameMap->run(window);
            } catch (const std::exception& ex) {
                std::cerr << "ERROR: " << ex.what() << std::endl;
                window.close();
            }
        }
        else {
            menu.draw(window);
        }
        window.display();
    }

    return 0;
}
