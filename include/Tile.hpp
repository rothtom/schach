#pragma once

#include <SFML/Graphics.hpp>

#include "Pieces.hpp"

class Tile {
    public:
        Tile(sf::RenderWindow& window, sf::RectangleShape);
        std::shared_ptr<Piece> piece;

        void draw();

    private:
        sf::RectangleShape rect_;
        sf::RenderWindow& window_;

};