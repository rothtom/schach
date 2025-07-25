#include "Pawn.hpp"

chess::Pawn::Pawn(chess::color piece_color, ChessCoordinates coordinates, sf::Texture& texture, sf::RenderWindow& window, std::vector<std::unique_ptr<Piece>>& other_pieces)
: Piece(piece_color, coordinates, texture, window, other_pieces)
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
    if (not chess::is_piece_at(other_pieces_, tile_infront_1)) {
        possible_moves.emplace_back(tile_infront_1);
    }
    else { // there has to be a piece of the same color infront
        return possible_moves;
    }

    chess::ChessCoordinates tile_infront_2;
    if (color_ == WHITE) {
        tile_infront_2 = chess::ChessCoordinates({coordinates_.coll, static_cast<unsigned short>(coordinates_.row + 2)});
        if (coordinates_.row == 2) {
        if (not chess::is_piece_at(other_pieces_, tile_infront_2)) {
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
        if (not chess::is_piece_at(other_pieces_, tile_infront_2)) {
            possible_moves.emplace_back(tile_infront_2);
        }
        // piece of opposit color infront
        else if (chess::get_piece_at(other_pieces_, tile_infront_2)->get_color() != color_) {
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
    if (chess::is_piece_at(other_pieces_, tile_diagonal_1)) {
        if (chess::get_piece_at(other_pieces_, tile_diagonal_1)->get_color() != color_) {
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
    if (chess::is_piece_at(other_pieces_, tile_diagonal_2)) {
        if (chess::get_piece_at(other_pieces_, tile_diagonal_2)->get_color() != color_) {
            possible_moves.emplace_back(tile_diagonal_2);
        }
    }

    return possible_moves;
}

