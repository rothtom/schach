#include "Move.hpp"

namespace chess {
    class NormalMove : public Move {
        public:
            NormalMove(const ChessCoordinates& piece_cords, const ChessCoordinates& target_cords, Board& board);
            std::unique_ptr<Move> deep_copy(Board& board) const override;
    };
}