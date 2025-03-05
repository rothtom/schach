#pragma once

#include <SFML/Graphics.hpp>

#include "colors.hpp"
#include "Coordinates.hpp"

class Tile {
    public:
        Tile(colors color, Coordinates board_coordinates);
    
        void draw(sf::RenderWindow& window, Coordinates pixel_coordinates, float length);
    
    private:
        colors color_;
};