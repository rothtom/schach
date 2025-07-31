#include "Move.hpp"
#include "piece_name.hpp"

namespace chess {
    class PromotionMove : public Move {
        public:
            PromotionMove(ChessCoordinates& piece_cords, ChessCoordinates& target_cords, piece_name piece_name);
            virtual void make_move() override;
            virtual void hypothetically_make_move() override;
    };
}