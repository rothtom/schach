#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Board.hpp"

int main() {
    std::cout << "starting..." << std::endl;

    sf::RenderWindow window(sf::VideoMode({500, 500}), "Chess");

    std::cout << "Successfully opened window" << std::endl;

    // chess::Board board(window, "8/8/8/2k5/4K3/8/8/8 w KQkq - 0 1");
    chess::Board board(window);

    std::cout << "Successfully created Board" << std::endl;

    while (window.isOpen()) {
        board.update();
 
        // Clear screen
        window.clear();
 
        board.draw();

        window.display();
    }
}