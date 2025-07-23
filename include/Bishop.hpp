

#include "Piece.hpp"

namespace chess {
    class Bishop: public Piece {
        public:
            Bishop(color piece_color, ChessCoordinates coordinates, sf::Texture& texture, sf::RenderWindow& window);
        private:
            
    };
}