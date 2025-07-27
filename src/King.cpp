#include "King.hpp"

#include "Board.hpp"

chess::King::King(chess::color piece_color, ChessCoordinates coordinates, sf::Texture& texture, sf::RenderWindow& window, Board& board)
: Piece(piece_color, coordinates, texture, window, board)
{}

std::vector<chess::ChessCoordinates> chess::King::get_possible_moves(int depth) {
    std::vector<chess::ChessCoordinates> possible_moves;
    std::vector<std::pair<int, int>> directions = {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0},
        {-1, 1},
        {1, 1},
        {-1, -1},
        {1, -1},
    };
    for (auto& [dcoll, drow] : directions) {
        ChessCoordinates considered_cords = coordinates_;
        considered_cords.coll += dcoll;
        considered_cords.row += drow;

        if (considered_cords.coll <  'a' or considered_cords.coll > 'h' 
            or considered_cords.row > 8 or considered_cords.row < 1) {
                continue;
        }

        if (chess::is_piece_at(board_.get_pieces(), considered_cords)) {
            if (chess::get_piece_at(board_.get_pieces(), considered_cords)->get_color() != color_) {
                possible_moves.emplace_back(considered_cords);
            }
            continue;
        }
        else {
            possible_moves.emplace_back(considered_cords);
        }
    }
    return possible_moves;
}

std::unique_ptr<chess::Piece> chess::King::deep_copy() {
    return std::make_unique<King>(*this);
}