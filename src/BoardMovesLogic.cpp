#include "Board.hpp"

#include "King.hpp"
#include "Move.hpp"

std::vector<chess::Move> chess::Board::pieces_moves(std::unique_ptr<chess::Piece>& piece) {
    std::vector<Move> pieces_possible_moves = {};
    Move current_move;
    for (std::unique_ptr<Move>& move : piece->get_possible_moves()) {
        current_move = Move(move->get_piece_cords(), move->get_target_cords(), *this);
        if (not is_now_in_check(current_move) and not is_in_check()) {
            pieces_possible_moves.emplace_back(current_move);
        }
    }
    // set possible moves for piece
    return pieces_possible_moves;
}

void chess::Board::set_possible_moves(std::vector<Move> moves) {
    for (Move& move : moves) {
        get_piece_at(move.get_piece_cords())->add_possible_move(move);
    }
}

std::vector<chess::Move> chess::Board::all_possible_moves() {
    std::vector<Move> possible_moves;
    std::vector<Move>pieces_possible_moves;
    for (std::unique_ptr<Piece>& piece : pieces_) {
        if (piece->get_color() != current_player) {
            continue;
        }
        // set possible moves for the piece
        pieces_possible_moves = pieces_moves(piece);
        piece->reset_possible_moves();
        for (Move& pieces_possible_move : pieces_possible_moves) {
            piece->add_possible_move(pieces_possible_move);
            possible_moves.emplace_back(pieces_possible_move);
        }
        if (dynamic_cast<chess::King*>(piece.get())) {
            Move possible_rochade_move;
            if (piece->get_color() == WHITE) {
                
                for (rochade_types rochade_type : rochade_rights) {
                    switch (rochade_type) {
                        case K:
                            if (is_piece_at(ChessCoordinates('f', 1))) {continue;}
                            else if (is_piece_at(ChessCoordinates('g', 1))) {continue;}
                            if (is_attacked(ChessCoordinates('e', 1), BLACK)) {continue;}
                            else if (is_attacked(ChessCoordinates('f', 1), BLACK)) {continue;}
                            else if (is_attacked(ChessCoordinates('g', 1), BLACK)) {continue;}
                            else if (is_attacked(ChessCoordinates('h', 1), BLACK)) {continue;}
                            possible_rochade_move = Move(ChessCoordinates('e', 1), ChessCoordinates('g', 1), *this);
                            possible_moves.emplace_back(possible_rochade_move);
                            piece->add_possible_move(possible_rochade_move);
                        case Q:
                            if (is_piece_at(ChessCoordinates('b', 1))) {continue;}
                            else if (is_piece_at(ChessCoordinates('c', 1))) {continue;}
                            else if (is_piece_at(ChessCoordinates('d', 1))) {continue;}
                            if (is_attacked(ChessCoordinates('a', 1), BLACK)) {continue;}
                            else if (is_attacked(ChessCoordinates('b', 1), BLACK)) {continue;}
                            else if (is_attacked(ChessCoordinates('c', 1), BLACK)) {continue;}
                            else if (is_attacked(ChessCoordinates('d', 1), BLACK)) {continue;}
                            else if (is_attacked(ChessCoordinates('e', 1), BLACK)) {continue;}
                            possible_rochade_move = Move(ChessCoordinates('e', 1), ChessCoordinates('c', 1), *this);
                            possible_moves.emplace_back(possible_rochade_move);
                            piece->add_possible_move(possible_rochade_move);
                        default:
                            break;
                    }
                }
            }
            else {
                for (rochade_types rochade_type : rochade_rights) {
                    switch (rochade_type) {
                        case k:
                            if (is_piece_at(ChessCoordinates('f', 8))) {continue;}
                            else if (is_piece_at(ChessCoordinates('g', 8))) {continue;}
                            if (is_attacked(ChessCoordinates('e', 8), WHITE)) {continue;}
                            else if (is_attacked(ChessCoordinates('f', 8), WHITE)) {continue;}
                            else if (is_attacked(ChessCoordinates('g', 8), WHITE)) {continue;}
                            else if (is_attacked(ChessCoordinates('h', 8), WHITE)) {continue;}
                            possible_rochade_move = Move(ChessCoordinates({'e', 8}), ChessCoordinates({'g', 8}), *this);
                            possible_moves.emplace_back(possible_rochade_move);
                            piece->add_possible_move(possible_rochade_move);
                        case q:
                            if (is_piece_at(ChessCoordinates('b', 8))) {continue;}
                            else if (is_piece_at(ChessCoordinates('c', 8))) {continue;}
                            else if (is_piece_at(ChessCoordinates('d', 8))) {continue;}
                            if (is_attacked(ChessCoordinates('a', 8), WHITE)) {continue;}
                            else if (is_attacked(ChessCoordinates('b', 8), WHITE)) {continue;}
                            else if (is_attacked(ChessCoordinates('c', 8), WHITE)) {continue;}
                            else if (is_attacked(ChessCoordinates('d', 8), WHITE)) {continue;}
                            else if (is_attacked(ChessCoordinates('e', 8), WHITE)) {continue;}
                            possible_rochade_move = Move(ChessCoordinates({'e', 8}), ChessCoordinates({'c', 8}), *this);
                            possible_moves.emplace_back(possible_rochade_move);
                            piece->add_possible_move(possible_rochade_move);
                        default:
                            break;
                    }
                }
            }
        }
    }
    return possible_moves;
}





bool chess::Board::is_attacked(const chess::ChessCoordinates& tile, color attacking_color) {
    for (const std::unique_ptr<Piece>& piece : pieces_) {
        if (piece->get_color() != attacking_color) {
            continue;
        }
        for (std::unique_ptr<Move>& move : piece->get_possible_moves()) {
            if (move->get_target_cords() == tile) {
                return true;
            }
        }
    }
    return false;
}

bool chess::Board::is_in_check() {
    color kings_color;
    current_player == WHITE ? kings_color = BLACK : kings_color = WHITE;
    return is_attacked(get_king(kings_color)->get_coordinates(), current_player);
}

bool chess::Board::is_now_in_check(Move move) {
    Board board_copy = this->deep_copy();
    std::unique_ptr<Move> move_copy = move.deep_copy(board_copy);
    move_copy->hypothetically_make_move();
    bool now_check;
    
    if ((now_check = board_copy.is_in_check())) {
        // std::cout << "eliminated move: " << move.second.coll << move.second.row << std::endl;
    }
    return now_check;
}

bool chess::Board::is_checkmate() {
    if (not is_in_check()) {
        return false;
    }
    if (not all_possible_moves().empty()) {
        return false;
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


void chess::Board::take_piece_at(chess::ChessCoordinates target_cords) {
    pieces_.erase(get_piece_iterator_at(target_cords));
}