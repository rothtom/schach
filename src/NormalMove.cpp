#include "NormalMove.hpp"


chess::NormalMove::NormalMove(const ChessCoordinates& piece_cords, const ChessCoordinates& target_cords, Board& board) 
: Move(piece_cords, target_cords, board)
{}

std::unique_ptr<chess::Move> chess::NormalMove::deep_copy(chess::Board& new_board) const {
    std::unique_ptr<NormalMove> move_copy = std::make_unique<NormalMove>(*this);
    move_copy->set_board(new_board);
    return move_copy;
}