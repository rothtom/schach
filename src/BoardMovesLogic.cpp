#include "Board.hpp"

#include "King.hpp"

std::vector<move> chess::Board::pieces_moves(std::unique_ptr<chess::Piece>& piece) {
    std::vector<move> pieces_possible_moves = {};
    move current_move(piece->get_coordinates(), ChessCoordinates('z', -1));
    for (ChessCoordinates& target_tile : piece->get_possible_moves()) {
        current_move.second = target_tile;
        if (not is_now_in_check(current_move) and not is_in_check()) {
            pieces_possible_moves.emplace_back(current_move);
        }
    }
    // set possible moves for piece
    
    return pieces_possible_moves;
}

void chess::Board::set_possible_moves(std::vector<move> moves) {
    for (auto& [start, target] : moves) {
        get_piece_at(start)->add_possible_move(target);
    }
}

std::vector<move> chess::Board::all_possible_moves() {
    std::vector<move> possible_moves;
    std::vector<move>pieces_possible_moves;
    for (std::unique_ptr<Piece>& piece : pieces_) {
        if (piece->get_color() == current_player) {
            pieces_possible_moves = pieces_moves(piece);
            piece->reset_possible_moves();
            for (auto& pieces_possible_move : pieces_possible_moves) {
                piece->add_possible_move(pieces_possible_move.second);
                possible_moves.emplace_back(pieces_possible_move);
            }
        }
        if (dynamic_cast<chess::King*>(piece.get())) {
            move possible_rochade_move;
            if (piece->get_color() == WHITE) {
                
                for (rochade_types rochade_type : rochade_rights) {
                    switch (rochade_type) {
                        case K:
                            if (is_piece_at(ChessCoordinates('f', 1))) {continue;}
                            else if (is_piece_at(ChessCoordinates('g', 1))) {continue;}
                            possible_rochade_move = move(ChessCoordinates({'e', 1}), ChessCoordinates({'g', 1}));
                            possible_moves.emplace_back(possible_rochade_move);
                            piece->add_possible_move(possible_rochade_move.second);
                        case Q:
                            if (is_piece_at(ChessCoordinates('b', 1))) {continue;}
                            else if (is_piece_at(ChessCoordinates('c', 1))) {continue;}
                            else if (is_piece_at(ChessCoordinates('d', 1))) {continue;}
                            possible_rochade_move = move(ChessCoordinates({'e', 1}), ChessCoordinates({'c', 8}));
                            possible_moves.emplace_back(possible_rochade_move);
                            piece->add_possible_move(possible_rochade_move.second);
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
                            possible_rochade_move = move(ChessCoordinates({'e', 8}), ChessCoordinates({'g', 8}));
                            possible_moves.emplace_back(possible_rochade_move);
                            piece->add_possible_move(possible_rochade_move.second);
                        case q:
                            if (is_piece_at(ChessCoordinates('b', 8))) {continue;}
                            else if (is_piece_at(ChessCoordinates('c', 8))) {continue;}
                            else if (is_piece_at(ChessCoordinates('d', 8))) {continue;}
                            possible_rochade_move = move(ChessCoordinates({'e', 8}), ChessCoordinates({'c', 8}));
                            possible_moves.emplace_back(possible_rochade_move);
                            piece->add_possible_move(possible_rochade_move.second);
                        default:
                            break;
                    }
                }
            }
        }
    }
    return possible_moves;
}





bool chess::Board::is_attacked(const chess::ChessCoordinates& tile) {
    color attacking_color;
    current_player == WHITE ? attacking_color = BLACK : attacking_color = WHITE;
    for (const std::unique_ptr<Piece>& piece : pieces_) {
        if (piece->get_color() == attacking_color) {
            continue;
        }
        for (chess::ChessCoordinates coordinates : piece->get_possible_moves()) {
            if (coordinates == tile) {
                return true;
            }
        }
    }
    return false;
}

bool chess::Board::is_in_check() {
    color kings_color;
    current_player == WHITE ? kings_color = BLACK : kings_color = WHITE;
    return is_attacked(get_king(kings_color)->get_coordinates());
}

bool chess::Board::is_now_in_check(move move) {
    Board board_copy = this->deep_copy();
    Piece* piece = board_copy.get_piece_at(move.first);
    board_copy.hypothetically_make_move(piece, move.second);
    bool now_check;
    
    if ((now_check = board_copy.is_in_check())) {
        // std::cout << "eliminated move: " << move.second.coll << move.second.row << std::endl;
    }
    return now_check;
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