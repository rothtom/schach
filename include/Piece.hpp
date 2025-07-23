#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "colors.hpp"
#include "ChessCoordinates.hpp"

namespace chess {
    class Piece {
        public:
            Piece(chess::color piece_color, chess::ChessCoordinates coordinates, sf::Texture texture);
            void draw();
            void update();
        protected:
            chess::color color_;
            ChessCoordinates coordinates_;
            sf::Vector2i position_;
            std::vector<ChessCoordinates> possible_moves();
            sf::Texture texture_;
            sf::Sprite sprite_;
    };
} // chess
