#include "Piece.hpp"

namespace chess {
    class Pawn: public Piece {
        public:
            Pawn(color piece_color, ChessCoordinates coordinates, sf::Texture& texture, sf::RenderWindow& window);
        private:
            
    };
}