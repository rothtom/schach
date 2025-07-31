#include "ChessCoordinates.hpp"

namespace chess {
    class Board;
    class Move {
        public:
            Move();
            Move(const ChessCoordinates& piece_cords, const ChessCoordinates& target_cords, Board& board);
            void set_board(Board& board);
            virtual void make_move();
            virtual void hypothetically_make_move();
            ChessCoordinates get_piece_cords() const;
            ChessCoordinates get_target_cords() const;
            Move deep_copy(Board& new_board);

        private:
            ChessCoordinates piece_cords_;
            ChessCoordinates target_cords_;
            Board* board_;
    };
}