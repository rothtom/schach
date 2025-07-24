#include "Pawn.hpp"

chess::Pawn::Pawn(chess::color piece_color, ChessCoordinates coordinates, sf::Texture& texture, sf::RenderWindow& window, std::vector<std::unique_ptr<Piece>>& other_pieces)
: Piece(piece_color, coordinates, texture, window, other_pieces)
{}

std::vector<chess::ChessCoordinates> chess::Pawn::get_possible_moves() {
    std::vector<chess::ChessCoordinates> tiles;
    tiles.reserve(4);
    chess::ChessCoordinates tile_infront_1;
    if (color_ == WHITE) {
        tile_infront_1 = chess::ChessCoordinates({coordinates_.coll, static_cast<unsigned short>(coordinates_.row + 1)});
    }
    else {
        tile_infront_1 = chess::ChessCoordinates({coordinates_.coll, static_cast<unsigned short>(coordinates_.row - 1)});
    }
    // no piece infront
    if (not chess::is_piece_at(other_pieces_, tile_infront_1)) {
        tiles.emplace_back(tile_infront_1);
    }
    // piece of opposit color infront
    else if (chess::get_piece_at(other_pieces_, tile_infront_1)->get_color() != color_) {
        tiles.emplace_back(tile_infront_1);            
        return tiles;
    }
    else { // there has to be a piece of the same color infront
        return tiles;
    }

    chess::ChessCoordinates tile_infront_2;
    if (color_ == WHITE) {
        tile_infront_2 = chess::ChessCoordinates({coordinates_.coll, static_cast<unsigned short>(coordinates_.row + 2)});
    }
    else {
        tile_infront_2 = chess::ChessCoordinates({coordinates_.coll, static_cast<unsigned short>(coordinates_.row - 2)});
    }

    if (coordinates_.row == 2) {
        if (not chess::is_piece_at(other_pieces_, tile_infront_2)) {
            tiles.emplace_back(tile_infront_2);
        }
        // piece of opposit color infront
        else if (chess::get_piece_at(other_pieces_, tile_infront_2)->get_color() != color_) {
            tiles.emplace_back(tile_infront_2);            
            return tiles;
        }
        else { // there has to be a piece of the same color infront
            return tiles;
        }
    }
    return tiles;
}

