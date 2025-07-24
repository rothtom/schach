#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "colors.hpp"
#include "ChessCoordinates.hpp"

namespace chess {
    class Piece {
        public:
            Piece(chess::color piece_color, chess::ChessCoordinates coordinates, sf::Texture& texture, sf::RenderWindow& window);
            void draw();
            void update();
            void resize(int tile_width);
            void update_position();
            virtual ~Piece() = default;
        protected:
            chess::color color_;
            ChessCoordinates coordinates_;
            sf::Vector2i position_;
            std::vector<ChessCoordinates> possible_moves();
            sf::Texture& texture_;
            sf::Sprite sprite_;
            float sprite_scale_;
            float tile_width_;
            sf::RenderWindow& window_;
    };
} // chess
