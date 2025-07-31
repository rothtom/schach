#include "Knight.hpp"

#include "Board.hpp"
#include "Move.hpp"

chess::Knight::Knight(chess::color piece_color, ChessCoordinates coordinates, sf::Texture& texture, sf::RenderWindow& window, Board& board)
: Piece(piece_color, coordinates, texture, window, board)
{}

std::vector<std::unique_ptr<chess::Move>> chess::Knight::get_possible_moves() {
    std::vector<std::unique_ptr<Move>> possible_moves;
    std::vector<std::pair<int, int>> directions = {
        {-2, -1},
        {-2, 1},
        {1, -2},
        {-1, -2},
        {2, 1},
        {2, -1},
        {-1, 2},
        {1, 2},
    };
    for (auto& [dcoll, drow] : directions) {
        ChessCoordinates considered_cords = coordinates_;
        considered_cords.coll += dcoll;
        considered_cords.row += drow;

        if (considered_cords.coll <  'a' or considered_cords.coll > 'h' 
            or considered_cords.row > 8 or considered_cords.row < 1) {
                continue;
        }

        if (board_->is_piece_at(considered_cords)) {
            if (board_->get_piece_at(considered_cords)->get_color() != color_) {
                possible_moves.emplace_back(std::make_unique<Move>(coordinates_, considered_cords, *board_));
            }
            continue;
        }
        else {
            possible_moves.emplace_back(std::make_unique<Move>(coordinates_, considered_cords, *board_));
        }
    }
    return possible_moves;
}

std::unique_ptr<chess::Piece> chess::Knight::deep_copy(Board& board) {
    std::unique_ptr<Knight> copy = std::make_unique<Knight>(*this);
    copy->setTexture(texture_);
    copy->setBoard(board);
    for (const auto& move : possible_moves_) {
        copy->possible_moves_.emplace_back(move->deep_copy(board));
    }
    return copy;
}