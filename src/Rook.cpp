#include "Rook.hpp"

chess::Rook::Rook(chess::color piece_color, ChessCoordinates coordinates, sf::Texture& texture, sf::RenderWindow& window, std::vector<std::unique_ptr<Piece>>& other_pieces)
: Piece(piece_color, coordinates, texture,window, other_pieces)
{}

std::vector<chess::ChessCoordinates> chess::Rook::get_possible_moves() {
    std::vector<chess::ChessCoordinates> possible_moves;
    std::vector<std::pair<int, int>> directions = {
        {0, 1},
        {0, -1},
        {-1, 0},
        {1, 0},
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

            if (chess::is_piece_at(other_pieces_, considered_cords)) {
                if (chess::get_piece_at(other_pieces_, considered_cords)->get_color() != color_) {
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