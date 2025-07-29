#include "Pawn.hpp"

#include "Board.hpp"

chess::Pawn::Pawn(chess::color piece_color, ChessCoordinates coordinates, sf::Texture& texture, sf::RenderWindow& window, Board& board)
: Piece(piece_color, coordinates, texture, window, board)
{}

std::vector<chess::ChessCoordinates> chess::Pawn::get_possible_moves() {
    std::vector<chess::ChessCoordinates> possible_moves;
    possible_moves.reserve(6);
    chess::ChessCoordinates tile_infront_1;
    if (color_ == WHITE) {
        tile_infront_1 = chess::ChessCoordinates({coordinates_.coll, static_cast<unsigned short>(coordinates_.row + 1)});
    }
    else {
        tile_infront_1 = chess::ChessCoordinates({coordinates_.coll, static_cast<unsigned short>(coordinates_.row - 1)});
    }
    // no piece infront
    if (not board_->is_piece_at(tile_infront_1)) {
        possible_moves.emplace_back(tile_infront_1);
    }
    else { // there has to be a piece of the same color infront
        return possible_moves;
    }

    chess::ChessCoordinates tile_infront_2;
    if (color_ == WHITE) {
        tile_infront_2 = chess::ChessCoordinates({coordinates_.coll, static_cast<unsigned short>(coordinates_.row + 2)});
        if (coordinates_.row == 2) {
        if (not board_->is_piece_at(tile_infront_2)) {
            possible_moves.emplace_back(tile_infront_2);
        }
        else { // there has to be a piece of the same color infront
            return possible_moves;
        }
    }
    }
    else {
        tile_infront_2 = chess::ChessCoordinates({coordinates_.coll, static_cast<unsigned short>(coordinates_.row - 2)});
        if (coordinates_.row == 7) {
        if (not board_->is_piece_at(tile_infront_2)) {
            possible_moves.emplace_back(tile_infront_2);
        }
        // piece of opposit color infront
        else if (board_->get_piece_at(tile_infront_2)->get_color() != color_) {
            possible_moves.emplace_back(tile_infront_2);            
            return possible_moves;
        }
        else { // there has to be a piece of the same color infront
            return possible_moves;
        }
    }
    }

    chess::ChessCoordinates tile_diagonal_1;
    if (color_ == WHITE) {
        tile_diagonal_1 = {static_cast<char>(coordinates_.coll - 1), static_cast<unsigned short>(coordinates_.row + 1)};
    }
    else {
        tile_diagonal_1 = {static_cast<char>(coordinates_.coll - 1), static_cast<unsigned short>(coordinates_.row - 1)};
    }
    if (board_->is_piece_at(tile_diagonal_1)) {
        if (board_->get_piece_at(tile_diagonal_1)->get_color() != color_) {
            possible_moves.emplace_back(tile_diagonal_1);
        }
    }

    chess::ChessCoordinates tile_diagonal_2;
    if (color_ == WHITE) {
        tile_diagonal_2 = {static_cast<char>(coordinates_.coll + 1), static_cast<unsigned short>(coordinates_.row + 1)};
    }
    else {
        tile_diagonal_2 = {static_cast<char>(coordinates_.coll + 1), static_cast<unsigned short>(coordinates_.row - 1)};
    }
    if (board_->is_piece_at(tile_diagonal_2)) {
        if (board_->get_piece_at(tile_diagonal_2)->get_color() != color_) {
            possible_moves.emplace_back(tile_diagonal_2);
        }
    }

    
    return possible_moves;
}

std::unique_ptr<chess::Piece> chess::Pawn::deep_copy(Board& board) {
    std::unique_ptr<Pawn> copy = std::make_unique<Pawn>(*this);
    copy->setTexture(texture_);
    copy->setBoard(board);
    return copy;
}
