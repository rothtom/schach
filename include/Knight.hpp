

#include "Piece.hpp"

namespace chess {
    class Knight: public Piece {
        public:
            Knight(color piece_color, ChessCoordinates coordinates, sf::Texture& texture, sf::RenderWindow& window, Board& board);
            std::vector<ChessCoordinates> get_possible_moves(int depth);
            std::unique_ptr<Piece> deep_copy();
        private:
            
    };
}