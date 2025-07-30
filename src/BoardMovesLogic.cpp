#include "Board.hpp"

#include "King.hpp"

moves chess::Board::pieces_moves(std::unique_ptr<chess::Piece>& piece) {
    std::vector<ChessCoordinates> pieces_possible_tiles;
    for (ChessCoordinates& target_tile : piece->get_possible_moves()) {
        if (not is_now_in_check(std::pair<std::unique_ptr<Piece>&, ChessCoordinates>(piece, target_tile))) {
            pieces_possible_tiles.emplace_back(target_tile);
        }
    }
    // set possible moves for piece
    return moves(piece, pieces_possible_tiles);
}

void chess::Board::set_possible_moves(moves moves) {
    moves.first->set_possible_moves(moves.second);
}

std::vector<moves> chess::Board::all_possible_moves() {
    std::vector<moves> possible_moves;
    for (std::unique_ptr<Piece>& piece : pieces_) {
        if (piece->get_color() == current_player) {
            moves pieces_possible_moves = pieces_moves(piece);
            set_possible_moves(pieces_possible_moves);
            possible_moves.emplace_back(pieces_possible_moves);
        }
    }
    return possible_moves;
}

bool chess::Board::is_now_in_check(move move) {
    Board board_copy = this->deep_copy();
    Piece* piece = board_copy.get_piece_at(move.first->get_coordinates());
    board_copy.hypothetically_make_move(piece, move.second);
    bool now_check;
    
    if ((now_check = board_copy.is_in_check())) {
        // std::cout << "eliminated move: " << move.second.coll << move.second.row << std::endl;
    }
    return now_check;
}

bool chess::Board::is_in_check() {
    color kings_color;
    current_player == WHITE ? kings_color = BLACK : kings_color = WHITE;
    const chess::King* king = get_king(kings_color);
    for (const std::unique_ptr<Piece>& piece : pieces_) {
        if (piece->get_color() == king->get_color()) {
            continue;
        }
        for (chess::ChessCoordinates coordinates : piece->get_possible_moves()) {
            if (coordinates == king->get_coordinates()) {
                return true;
            }
        }
    }
    return false;
}


void chess::Board::make_move(chess::Piece* piece, chess::ChessCoordinates new_cords) {
    if (is_piece_at(new_cords)) {
        pieces_.erase(get_piece_iterator_at(new_cords));
    }
    piece->move(new_cords);
    if (is_checkmate()) {
        current_player == WHITE ? status = WHITE_WON : status = BLACK_WON;
        std::cout << "Checkmate!" << std::endl;
    }
    current_player == WHITE ? current_player = BLACK : current_player = WHITE;
    all_possible_moves();
}


void chess::Board::hypothetically_make_move(chess::Piece* piece, chess::ChessCoordinates new_cords) {
    if (is_piece_at(new_cords)) {
        pieces_.erase(get_piece_iterator_at(new_cords));
    }
    piece->move(new_cords);
    current_player == WHITE ? current_player = BLACK : current_player = WHITE;
}


bool chess::Board::is_checkmate() {
    if (not is_in_check()) {
        std::cout << "Not in check" << std::endl;
        return false;
    }
    for (moves& moves : all_possible_moves()) {
        if (not moves.second.empty()) {
            std::cout << "Still moves available" << std::endl;
            std::cout << moves.second.at(0).coll << moves.second.at(0).row << std::endl;
            return false;
        }
    }
    return true;
}

chess::King* chess::Board::get_king(chess::color kings_color) const {
    for (const auto& piece : pieces_) {
        if (auto king = dynamic_cast<chess::King*>(piece.get())) {
            if (king->get_color() == kings_color) {
                // std::cout << typeid(*king).name() << std::endl;
                // std::cout << "Piece_cords: " << piece->get_coordinates().coll << piece->get_coordinates().row << std::endl;
                // std::cout << "Kings_cord: " << king->get_coordinates().coll << king->get_coordinates().row << std::endl;
                return king;
            }
        }
    }
    kings_color == WHITE ? throw std::runtime_error("no white king found") : throw std::runtime_error("no black king found");
}