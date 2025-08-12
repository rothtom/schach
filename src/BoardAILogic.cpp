#include "Board.hpp"

#include "King.hpp"
#include "Queen.hpp"
#include "Rook.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"
#include "Pawn.hpp"

#include "Move.hpp"



float chess::Board::evaluate() {
    std::map<chess::color, int> score;
    for (auto& piece : pieces_) {
        if (auto queen = dynamic_cast<chess::Queen*>(piece.get())) {
            score[queen->get_color()] += 90;
        }
        else if (auto rook = dynamic_cast<chess::Rook*>(piece.get())) {
            score[rook->get_color()] += 50;
        }
        else if (auto bishop = dynamic_cast<chess::Bishop*>(piece.get())) {
            score[bishop->get_color()] += 30;
        }
        else if (auto knight = dynamic_cast<chess::Knight*>(piece.get())) {
            score[knight->get_color()] += 30;
        }
        else if (auto pawn = dynamic_cast<chess::Pawn*>(piece.get())) {
            score[pawn->get_color()] += 10;
        }
    }
    if (current_player == WHITE) {
        score[WHITE] += all_possible_moves().size();
        current_player == WHITE ? current_player = BLACK : current_player = WHITE;
        score[BLACK] += all_possible_moves().size();
        current_player == WHITE ? current_player = BLACK : current_player = WHITE;
    }
    else {
        score[BLACK] += all_possible_moves().size() * 3;
        current_player == WHITE ? current_player = BLACK : current_player = WHITE;
        score[WHITE] += all_possible_moves().size() * 3;
        current_player == WHITE ? current_player = BLACK : current_player = WHITE;
    }
   
    current_player == WHITE ? current_player = BLACK : current_player = WHITE;
    if (is_checkmate()) {
        return current_player == WHITE ? 10000 : -10000;
    }
    current_player == WHITE ? current_player = BLACK : current_player = WHITE;
    return score[WHITE] - score[BLACK];
}

std::unique_ptr<chess::Move> chess::Board::best_move(int max_depth) {
    if (current_player == WHITE) {
        return best_move_white(1, max_depth, -10000, 10000);
    } else {
        return best_move_black(1, max_depth, -10000, 10000);
    }
}

std::unique_ptr<chess::Move> chess::Board::best_move_white(int depth, int max_depth, int alpha, int beta) {
    std::unique_ptr<Move> best_move = nullptr;
    int best_score = -10000;

    for (auto& move : all_possible_moves()) {
        Board board_copy = this->deep_copy();
        std::unique_ptr<Move> current_move = move->deep_copy(board_copy);
        current_move->hypothetically_make_move();

        int score;
        if (depth == max_depth) {
            score = board_copy.evaluate();
        } 
        else {
            std::unique_ptr<Move> response = board_copy.best_move_black(depth + 1, max_depth, alpha, beta);
            if (response) {
                response->hypothetically_make_move();
            }
            score = board_copy.evaluate();
        }

        if (score > best_score) {
            best_score = score;
            best_move = current_move->deep_copy(*this);
        }

        alpha = std::max(alpha, best_score);
        if (beta <= alpha) {
            break; // beta cut-off
        }
    }

    return best_move;
}

std::unique_ptr<chess::Move> chess::Board::best_move_black(int depth, int max_depth, int alpha, int beta) {
    std::unique_ptr<Move> best_move = nullptr;
    int best_score = 10000;

    for (auto& move : all_possible_moves()) {
        Board board_copy = this->deep_copy();
        std::unique_ptr<Move> current_move = move->deep_copy(board_copy);
        current_move->hypothetically_make_move();

        int score;
        if (depth == max_depth) {
            score = board_copy.evaluate();
        } else {
            std::unique_ptr<Move> response = board_copy.best_move_white(depth + 1, max_depth, alpha, beta);
            if (response) {
                response->hypothetically_make_move();
            }
            score = board_copy.evaluate();
        }

        if (score < best_score) {
            best_score = score;
            best_move = current_move->deep_copy(*this);
        }

        beta = std::min(beta, best_score);
        if (beta <= alpha) {
            break; // alpha cut-off
        }
    }

    return best_move;
}
