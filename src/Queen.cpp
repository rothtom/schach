#include "Queen.hpp"

#include "Board.hpp"

chess::Queen::Queen(chess::color piece_color, ChessCoordinates coordinates, sf::Texture& texture, sf::RenderWindow& window, Board& board)
: Piece(piece_color, coordinates, texture, window, board)
{}

std::vector<chess::ChessCoordinates> chess::Queen::get_possible_moves(int depth) {
    std::vector<chess::ChessCoordinates> possible_moves;
    std::vector<std::pair<int, int>> directions = {
        {1, 1},
        {1, 0},
        {1, -1},
        {-1, 1},
        {-1, 0},
        {-1, -1},
        {0, 1},
        {0, -1},
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
    return possible_moves;
}

std::unique_ptr<chess::Piece> chess::Queen::deep_copy() {
    return std::make_unique<Queen>(*this);
}