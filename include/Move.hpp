#pragma once

#include "ChessCoordinates.hpp"
#include "piece_name.hpp"

namespace chess {
    class Board;
    class Move {
        public:
            Move() = default;
            virtual ~Move() = default;
            Move(const Move& other);
            Move(const ChessCoordinates& piece_cords, const ChessCoordinates& target_cords, Board& board);
            void set_board(Board& board);
            virtual void make_move();
            virtual void hypothetically_make_move();
            ChessCoordinates get_piece_cords() const;
            ChessCoordinates get_target_cords() const;
            virtual std::unique_ptr<Move> deep_copy(Board& new_board) const;
            virtual piece_name get_piece_name_to_promote_to() const;

        protected:
            ChessCoordinates piece_cords_;
            ChessCoordinates target_cords_;
            Board* board_;
    };
}