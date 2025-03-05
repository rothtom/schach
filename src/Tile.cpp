#include <SFML/Graphics.hpp>

#include "colors.hpp"
#include "Coordinates.hpp"

class Tile {
    public:
        Tile(colors color, Coordinates board_coordinates) : color_(color) {};

        void draw(sf::RenderWindow& window, Coordinates pixel_coordinates, float length) {
            sf::RectangleShape square(sf::Vector2f(length, length));
            color_ == WHITE ? square.setFillColor(sf::Color(255, 255, 255)) : square.setFillColor(sf::Color(78,120,55));
            window.draw(square);
        }

    private:
        colors color_;
};