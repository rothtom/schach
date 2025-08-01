#include "Pawn.hpp"

#include "Board.hpp"
#include "Move.hpp"
#include "NormalMove.hpp"
#include "PromotionMove.hpp"
#include "PossibleMoveMarker.hpp"
#include "PossiblePromotionMarker.hpp"

chess::Pawn::Pawn(chess::color piece_color, ChessCoordinates coordinates, sf::Texture& texture, sf::RenderWindow& window, Board& board)
: Piece(piece_color, coordinates, texture, window, board)
{}

std::vector<std::unique_ptr<chess::Move>> chess::Pawn::get_possible_moves() {
    std::vector<std::unique_ptr<Move>> possible_moves;
    possible_moves.reserve(4);
    chess::ChessCoordinates tile_infront_1;
    if (color_ == WHITE) {
        tile_infront_1 = chess::ChessCoordinates({coordinates_.coll, static_cast<unsigned short>(coordinates_.row + 1)});
    }
    else {
        tile_infront_1 = chess::ChessCoordinates({coordinates_.coll, static_cast<unsigned short>(coordinates_.row - 1)});
    }
    // no piece infront
    if (not board_->is_piece_at(tile_infront_1)) {
        if (tile_infront_1.row == 8 or tile_infront_1.row == 1) {
            possible_moves.emplace_back(std::make_unique<PromotionMove>(coordinates_, tile_infront_1, QUEEN, *board_));
            possible_moves.emplace_back(std::make_unique<PromotionMove>(coordinates_, tile_infront_1, ROOK, *board_));
            possible_moves.emplace_back(std::make_unique<PromotionMove>(coordinates_, tile_infront_1, BISHOP, *board_));
            possible_moves.emplace_back(std::make_unique<PromotionMove>(coordinates_, tile_infront_1, KNIGHT, *board_));
        }
        else {
            possible_moves.emplace_back(std::make_unique<NormalMove>(coordinates_, tile_infront_1, *board_));
        }
        chess::ChessCoordinates tile_infront_2;
        if (color_ == WHITE ) {
            if (coordinates_.row == 2) {
                tile_infront_2 = chess::ChessCoordinates({coordinates_.coll, static_cast<unsigned short>(coordinates_.row + 2)});
                if (not board_->is_piece_at(tile_infront_2)) {
                    possible_moves.emplace_back(std::make_unique<NormalMove>(coordinates_, tile_infront_2, *board_));
                }
            }
        }
        else {
            if (coordinates_.row == 7) {
                tile_infront_2 = chess::ChessCoordinates({coordinates_.coll, static_cast<unsigned short>(coordinates_.row - 2)});
                if (coordinates_.row == 7) {
                    if (not board_->is_piece_at(tile_infront_2)) {
                        possible_moves.emplace_back(std::make_unique<NormalMove>(coordinates_, tile_infront_2, *board_));
                    }
                }
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

    if (board_->is_piece_at(tile_diagonal_1) && (tile_diagonal_1.coll >= 'a' and tile_diagonal_1.coll <= 'h')) {
        if (board_->get_piece_at(tile_diagonal_1)->get_color() != color_) {
            if (tile_diagonal_1.row == 8 or tile_diagonal_1.row == 1) {    
                possible_moves.emplace_back(std::make_unique<PromotionMove>(coordinates_, tile_diagonal_1, QUEEN, *board_));
                possible_moves.emplace_back(std::make_unique<PromotionMove>(coordinates_, tile_diagonal_1, ROOK, *board_));
                possible_moves.emplace_back(std::make_unique<PromotionMove>(coordinates_, tile_diagonal_1, BISHOP, *board_));
                possible_moves.emplace_back(std::make_unique<PromotionMove>(coordinates_, tile_diagonal_1, KNIGHT, *board_));
            }
            else {
                possible_moves.emplace_back(std::make_unique<NormalMove>(coordinates_, tile_diagonal_1, *board_));
            }
        }
    }

    chess::ChessCoordinates tile_diagonal_2;
    if (color_ == WHITE) {
        tile_diagonal_2 = {static_cast<char>(coordinates_.coll + 1), static_cast<unsigned short>(coordinates_.row + 1)};
    }
    else {
        tile_diagonal_2 = {static_cast<char>(coordinates_.coll + 1), static_cast<unsigned short>(coordinates_.row - 1)};
    }
    if (board_->is_piece_at(tile_diagonal_2) && (tile_diagonal_2.coll >= 'a' and tile_diagonal_2.coll <= 'h')) {
        if (board_->get_piece_at(tile_diagonal_2)->get_color() != color_) {
            if (tile_diagonal_2.row == 8 or tile_diagonal_2.row == 1) {    
                possible_moves.emplace_back(std::make_unique<PromotionMove>(coordinates_, tile_diagonal_2, QUEEN, *board_));
                possible_moves.emplace_back(std::make_unique<PromotionMove>(coordinates_, tile_diagonal_2, ROOK, *board_));
                possible_moves.emplace_back(std::make_unique<PromotionMove>(coordinates_, tile_diagonal_2, BISHOP, *board_));
                possible_moves.emplace_back(std::make_unique<PromotionMove>(coordinates_, tile_diagonal_2, KNIGHT, *board_));
            }
            else {
                possible_moves.emplace_back(std::make_unique<NormalMove>(coordinates_, tile_diagonal_2, *board_));
            }
        }
    }

    return possible_moves;
}

std::unique_ptr<chess::Piece> chess::Pawn::deep_copy(Board& board) {
    std::unique_ptr<Pawn> copy = std::make_unique<Pawn>(*this);
    copy->setTexture(texture_);
    copy->setBoard(board);
    /*
    for (const std::unique_ptr<Move>& move : possible_moves_) {
        copy->possible_moves_.emplace_back(move->deep_copy(board));
    }
    */
    return copy;
}

