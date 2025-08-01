#include "Bishop.hpp"
#include "directions.hpp"

#include "Board.hpp"
#include "Move.hpp"
#include "NormalMove.hpp"
#include <iostream>

chess::Bishop::Bishop(chess::color piece_color, ChessCoordinates coordinates, sf::Texture& texture, sf::RenderWindow& window, Board& board)
: Piece(piece_color, coordinates, texture, window, board)
{}

std::vector<std::unique_ptr<chess::Move>> chess::Bishop::get_possible_moves() {
    std::vector<std::unique_ptr<Move>> possible_moves;
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

            if (board_->is_piece_at(considered_cords)) {
                if (board_->get_piece_at(considered_cords)->get_color() != color_) {
                    possible_moves.emplace_back(std::make_unique<NormalMove>(coordinates_, considered_cords, *board_));
                }
                break;
            }
            else {
                possible_moves.emplace_back(std::make_unique<NormalMove>(coordinates_, considered_cords, *board_));
            }
        }
    }

    // possible_moves = check_discovered_check(possible_moves);
    // moved above to board

    return possible_moves;
}

std::unique_ptr<chess::Piece> chess::Bishop::deep_copy(Board& board) {
    std::unique_ptr<Bishop> copy = std::make_unique<Bishop>(*this);
    copy->setTexture(texture_);
    copy->setBoard(board);
    /*
    for (const std::unique_ptr<Move>& move : possible_moves_) {
        copy->possible_moves_.emplace_back(move->deep_copy(board));
    }
    */
    return copy;
}
