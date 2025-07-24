

#include "Piece.hpp"

namespace chess {
    class Rook: public Piece {
        public:
            Rook(color piece_color, ChessCoordinates coordinates, sf::Texture& texture, sf::RenderWindow& window, std::vector<std::unique_ptr<Piece>>& other_pieces);
            std::vector<ChessCoordinates> get_possible_moves();
        private:
            
    };
}