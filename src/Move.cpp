#include "Move.hpp"
#include "Board.hpp"

chess::Move::Move(const ChessCoordinates& piece_cords, const ChessCoordinates& target_cords, Board& board) 
: piece_cords_(piece_cords), target_cords_(target_cords)
{
    board_ = &board;
}

chess::Move::Move() 
: piece_cords_('x', 9), target_cords_('x', 9), board_(nullptr)
{}

void chess::Move::make_move() {
    if (board_->is_piece_at(target_cords_)) {
        board_->get_pieces().erase(board_->get_piece_iterator_at(target_cords_));
    }
    board_->get_piece_at(piece_cords_)->move(target_cords_);
    if (board_->is_checkmate()) {
        board_->get_current_player() == WHITE ? board_->status = WHITE_WON : board_->status = BLACK_WON;
        std::cout << "Checkmate!" << std::endl;
    }
    board_->get_current_player() == WHITE ? board_->current_player = BLACK : board_->current_player = WHITE;
    board_->all_possible_moves();
}

void chess::Move::hypothetically_make_move() {
    if (board_->is_piece_at(target_cords_)) {
        board_->get_pieces().erase(board_->get_piece_iterator_at(target_cords_));
    }
    board_->get_piece_at(piece_cords_)->move(target_cords_);
    if (board_->is_checkmate()) {
        board_->get_current_player() == WHITE ? board_->status = WHITE_WON : board_->status = BLACK_WON;
        std::cout << "Checkmate!" << std::endl;
    }
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

chess::Move chess::Move::deep_copy(chess::Board& new_board) {
    return Move(piece_cords_, target_cords_, new_board);
}