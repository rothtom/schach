#include <SFML/Graphics.hpp>

#include "ChessCoordinates.hpp"

namespace chess {
    class Piece;
    class PossibleMoveMarker {
        public:
            PossibleMoveMarker(ChessCoordinates coordinates, float& tile_width, sf::RenderWindow& window);
            bool is_hovered(sf::Vector2i mouse_pos);
            bool is_clicked(sf::Vector2i mouse_pos);
            
            void draw();
            void update_position();
            void resize(int new_tile_width);
        private:
            sf::RenderWindow& window_;
            ChessCoordinates coordinates_;
            float tile_width_;
            sf::Vector2f position_;
            sf::CircleShape circle_;
    };
}