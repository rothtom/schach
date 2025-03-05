#include <iostream>
#include <SFML/Graphics.hpp>

#include <Board.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "Chess");
    
    Board board(window);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        window.clear(sf::Color(0, 0, 0));

        // board.draw();

        window.display();               
    }
}