#pragma once

#include <SFML/Graphics.hpp>

#include "ChessCoordinates.hpp"

namespace chess {
    class Piece;
    class PossibleMoveMarker {
        public:
            PossibleMoveMarker(ChessCoordinates coordinates, float& tile_width, sf::RenderWindow& window);
            
            virtual void draw();
            virtual void update_position();
            float get_radius() const;
            ChessCoordinates get_coordinates() const;
            sf::Vector2f get_position() const;
            void resize(int new_tile_width);
            virtual bool is_hovered(sf::Vector2i& mouse_pos);
            bool is_clicked(sf::Vector2i& mouse_pos);
        protected:
            sf::RenderWindow& window_;
            ChessCoordinates coordinates_;
            float tile_width_;
            sf::Vector2f position_;
            sf::CircleShape circle_;
    };
}