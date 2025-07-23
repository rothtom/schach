#include "Piece.hpp"

namespace chess {
    class Queen: public Piece {
        public:
            Queen(color piece_color, ChessCoordinates coordinates, sf::Texture& texture, sf::RenderWindow& window);
        private:
            
    };
}