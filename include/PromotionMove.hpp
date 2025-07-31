#include "Move.hpp"
#include "piece_name.hpp"
#include "colors.hpp"

namespace chess {
    class PromotionMove : public Move {
        public:
            PromotionMove(const ChessCoordinates& piece_cords, const ChessCoordinates& target_cords, piece_name piece_name, Board& board);
            void hypothetically_make_move() override;
            void make_move() override;
            // std::unique_ptr<Move> deep_copy(Board& new_board) override;
            piece_name get_piece_name_to_promote_to() const override;

        private:
            piece_name piece_to_promote_to_;
            color pawn_color_;
    };
}