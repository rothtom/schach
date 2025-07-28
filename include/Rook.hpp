

#include "Piece.hpp"

namespace chess {
    class Rook: public Piece {
        public:
            Rook(color piece_color, ChessCoordinates coordinates, sf::Texture& texture, sf::RenderWindow& window, Board& board);
            std::vector<ChessCoordinates> get_possible_moves();
            virtual std::unique_ptr<Piece> deep_copy(Board& board) override;
        private:
            
    };
}