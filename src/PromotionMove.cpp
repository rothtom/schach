#include "PromotionMove.hpp"
#include "Board.hpp"

chess::PromotionMove::PromotionMove(const ChessCoordinates& piece_cords, const ChessCoordinates& target_cords, piece_name piece_to_promote_to, Board& board) 
: Move(piece_cords, target_cords, board), piece_to_promote_to_(piece_to_promote_to)
{}

void chess::PromotionMove::make_move() {
    if (board_->is_piece_at(target_cords_)) {
        std::cout << "Taking piece to promote" << std::endl;
        board_->take_piece_at(target_cords_);
    }
    board_->take_piece_at(piece_cords_);
    if (target_cords_.row == 8) {
        board_->add_piece(piece_to_promote_to_, WHITE, target_cords_);
    }
    else if (target_cords_.row == 1) {
        board_->add_piece(piece_to_promote_to_, BLACK, target_cords_);
    }
    else {
        throw std::runtime_error("Pawn promoted but not on right row");
    }
    board_->get_current_player() == WHITE ? board_->current_player = BLACK : board_->current_player = WHITE;
    board_->all_possible_moves();
}

void chess::PromotionMove::hypothetically_make_move() {
    if (board_->is_piece_at(target_cords_)) {
        board_->take_piece_at(target_cords_);
    }
    board_->take_piece_at(piece_cords_);
    if (target_cords_.row == 8) {
        board_->add_piece(piece_to_promote_to_, WHITE, target_cords_);
    }
    else if (target_cords_.row == 1) {
        board_->add_piece(piece_to_promote_to_, BLACK, target_cords_);
    }
    else {
        throw std::runtime_error("Pawn promoted but not on right row");
    }
    board_->get_current_player() == WHITE ? board_->current_player = BLACK : board_->current_player = WHITE;
}

chess::piece_name chess::PromotionMove::get_piece_name_to_promote_to() const {
    return piece_to_promote_to_;
}


std::unique_ptr<chess::Move> chess::PromotionMove::deep_copy(chess::Board& new_board) const {
    PromotionMove move_copy(*this);
    move_copy.set_board(new_board);
    return std::make_unique<PromotionMove>(std::move(move_copy));
}
