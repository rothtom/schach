#include "Move.hpp"
#include "Board.hpp"
#include "King.hpp"

chess::Move::Move(const ChessCoordinates& piece_cords, const ChessCoordinates& target_cords, Board& board) 
: piece_cords_(piece_cords), target_cords_(target_cords)
{
    board_ = &board;
}

void chess::Move::make_move() {
    if (board_->is_piece_at(target_cords_)) {
        board_->take_piece_at(target_cords_);
    }
    board_->get_piece_at(piece_cords_)->move(target_cords_);
    board_->get_current_player() == WHITE ? board_->current_player = BLACK : board_->current_player = WHITE;
    std::vector<std::unique_ptr<Move>> possible_moves = board_->all_possible_moves();
    board_->set_possible_moves(possible_moves);
}

void chess::Move::hypothetically_make_move() {
    if (board_->is_piece_at(target_cords_)) {
        board_->take_piece_at(target_cords_);
    }
    board_->get_piece_at(piece_cords_)->move(target_cords_);
    board_->get_current_player() == WHITE ? board_->current_player = BLACK : board_->current_player = WHITE;
}

chess::ChessCoordinates chess::Move::get_piece_cords() const {
    return piece_cords_;
}

chess::ChessCoordinates chess::Move::get_target_cords() const {
    return target_cords_;
}

void chess::Move::set_board(Board& board) {
    board_ = &board;
}

chess::piece_name chess::Move::get_piece_name_to_promote_to() const {
    throw std::logic_error("Dont call this on non promoting moves!");
}