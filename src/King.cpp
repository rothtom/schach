#include "King.hpp"

#include "Board.hpp"

chess::King::King(chess::color piece_color, ChessCoordinates coordinates, sf::Texture& texture, sf::RenderWindow& window, Board& board)
: Piece(piece_color, coordinates, texture, window, board)
{}

std::vector<chess::ChessCoordinates> chess::King::get_possible_moves() {
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

        if (board_->is_piece_at(considered_cords)) {
            if (board_->get_piece_at(considered_cords)->get_color() != color_) {
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

std::unique_ptr<chess::Piece> chess::King::deep_copy(Board& board) {
    std::unique_ptr<King> copy = std::make_unique<King>(*this);
    copy->setTexture(texture_);
    copy->setBoard(board);
    return copy;
}

void chess::King::move(chess::ChessCoordinates new_cords) {
    if (new_cords == ChessCoordinates('g', 1)) {
        coordinates_ = new_cords;
        board_->get_piece_at(ChessCoordinates('h', 1))->move(ChessCoordinates('f', 1));
    }
    else if (new_cords == ChessCoordinates('c', 1)) {
        coordinates_ = new_cords;
        board_->get_piece_at(ChessCoordinates('a', 1))->move(ChessCoordinates('d', 1));
    }
    else if (new_cords == ChessCoordinates('g', 8)) {
        coordinates_ = new_cords;
        board_->get_piece_at(ChessCoordinates('h', 8))->move(ChessCoordinates('f', 8));
    }
    else if (new_cords == ChessCoordinates('c', 8)) {
        coordinates_ = new_cords;
        board_->get_piece_at(ChessCoordinates('a', 8))->move(ChessCoordinates('d', 8));
    }
    possible_move_markers_.clear();
    disselect();
    update_position();
}