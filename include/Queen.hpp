#include "Piece.hpp"

namespace chess {
    class Queen: public Piece {
        public:
            Queen(color piece_color, ChessCoordinates coordinates, sf::Texture& texture, sf::RenderWindow& window, Board& board);
            std::vector<std::unique_ptr<Move>> get_possible_moves() override;
            virtual std::unique_ptr<Piece> deep_copy(Board& board) override;
        private:
            
    };
}