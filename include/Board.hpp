#pragma once

#include <SFML/Graphics.hpp>

#include "colors.hpp"
#include "Coordinates.hpp"

class Board {
    public:
        Board(sf::RenderWindow& window);
        void draw();

    private:
        sf::RenderWindow& window_;
        float square_length_;
        sf::RectangleShape tile_;
        void draw_tiles_();
};