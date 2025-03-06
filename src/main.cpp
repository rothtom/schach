#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <Board.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 800)), "Chess", sf::State::Fullscreen);
    window.setFramerateLimit(60);
    Board board(window);

    while (window.isOpen()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {window.close();}
        
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        
        window.clear(sf::Color(0, 0, 0));

        board.draw();

        window.display();               
    }
}