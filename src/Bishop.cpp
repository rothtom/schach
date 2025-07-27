#include "Bishop.hpp"
#include "directions.hpp"

#include "Board.hpp"

#include <iostream>

chess::Bishop::Bishop(chess::color piece_color, ChessCoordinates coordinates, sf::Texture& texture, sf::RenderWindow& window, Board& board)
: Piece(piece_color, coordinates, texture, window, board)
{}

std::vector<chess::ChessCoordinates> chess::Bishop::get_possible_moves(int depth) {
    std::vector<chess::ChessCoordinates> possible_moves;
    std::vector<std::pair<int, int>> directions = {
        {1, -1},
        {1, 1},
        {-1, -1},
        {-1, 1},
    };
    for (auto& [dcoll, drow] : directions) {
        ChessCoordinates considered_cords = coordinates_;
        while (true) {
            considered_cords.coll += dcoll;
            considered_cords.row += drow;

            if (considered_cords.coll <  'a' or considered_cords.coll > 'h' 
                or considered_cords.row > 8 or considered_cords.row < 1) {
                    break;
            }

            if (chess::is_piece_at(board_.get_pieces(), considered_cords)) {
                if (chess::get_piece_at(board_.get_pieces(), considered_cords)->get_color() != color_) {
                    possible_moves.emplace_back(considered_cords);
                }
                break;
            }
            else {
                possible_moves.emplace_back(considered_cords);
            }
        }
    }

    possible_moves = check_discovered_check(possible_moves, depth);

    return possible_moves;
}

std::unique_ptr<chess::Piece> chess::Bishop::deep_copy() {
    return std::make_unique<Bishop>(*this);
}
