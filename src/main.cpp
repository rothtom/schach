#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Board.hpp"

int main() {
    std::cout << "starting..." << std::endl;

    sf::RenderWindow window(sf::VideoMode({500, 500}), "Chess");

    std::cout << "Successfully opened window" << std::endl;

    chess::Board board(window);

    std::cout << "Successfully created Board" << std::endl;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (event->is<sf::Event::Resized>()) {
                board.resize();
            }
        }
 
        // Clear screen
        window.clear();
 
        board.draw();

        window.display();
    }
}