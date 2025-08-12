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
            score[queen->get_color()] += 9;
        }
        else if (auto rook = dynamic_cast<chess::Rook*>(piece.get())) {
            score[rook->get_color()] += 5;
        }
        else if (auto bishop = dynamic_cast<chess::Bishop*>(piece.get())) {
            score[bishop->get_color()] += 3;
        }
        else if (auto knight = dynamic_cast<chess::Knight*>(piece.get())) {
            score[knight->get_color()] += 3;
        }
        else if (auto pawn = dynamic_cast<chess::Pawn*>(piece.get())) {
            score[pawn->get_color()] += 1;
        }
    }
    if (status == BLACK_WON) {
            score[BLACK] += 50;
        }
    else if (status == WHITE_WON) {
        score[WHITE] += 50;
    }
    return score[WHITE] - score[BLACK];
}

std::unique_ptr<chess::Move> chess::Board::best_move(int max_depth) {
    if (current_player == WHITE) {
        return best_move_white(1, max_depth);
    }
    else {
        return best_move_black(1, max_depth);
    }
}

std::unique_ptr<chess::Move> chess::Board::best_move_white(int depth, int max_depth) {
    if (depth == max_depth) {
        int best_score = -1000;
        int score;
        std::unique_ptr<chess::Move> best_move = nullptr;
        for (auto& move : all_possible_moves()) {
            Board board_copy = this->deep_copy();
            // std::cout << "not yet" << std::endl;
            std::unique_ptr<chess::Move> current_move = move->deep_copy(board_copy);
            // std::cout << "not yet" << std::endl;
            current_move->hypothetically_make_move();
            score = board_copy.evaluate();
            if (best_score < score) {
                best_score = score;
                best_move = current_move->deep_copy(*this);
            }
        }
        // std::cout << "white base case completed" << std::endl;
        return best_move;
    }
    int best_score = -1000;
    int score;
    std::unique_ptr<Move> current_move = nullptr;
    std::unique_ptr<Move> best_move = nullptr;
    for (auto& move : all_possible_moves()) {
        Board board_copy = this->deep_copy();
        current_move = move->deep_copy(board_copy);
        current_move->hypothetically_make_move();
        std::unique_ptr<Move> blacks_best_move = board_copy.best_move_black(depth + 1, max_depth)->deep_copy(board_copy);
        blacks_best_move->hypothetically_make_move();
        score = board_copy.evaluate();
        if (best_score < score) {
            best_score = score;
            best_move = current_move->deep_copy(*this);
        }
    }
    return best_move;
}

std::unique_ptr<chess::Move> chess::Board::best_move_black(int depth, int max_depth) {
    if (depth == max_depth) {
        int best_score = 1000;
        int score;
        std::unique_ptr<Move> best_move = nullptr;
        for (auto& move : all_possible_moves()) {
            Board board_copy = this->deep_copy();
            std::unique_ptr<Move> current_move = move->deep_copy(board_copy);
            current_move->hypothetically_make_move();
            score = board_copy.evaluate();
            if (best_score > score) {
                best_score = score;
                best_move = current_move->deep_copy(*this);
            }
        }
        // std::cout << "black base case completed" << std::endl;
        return best_move;
    }
    std::unique_ptr<Move> current_move = nullptr;
    std::unique_ptr<Move> best_move = nullptr;
    int best_score = 1000;
    int score;
    for (auto& move : all_possible_moves()) {
        Board board_copy = this->deep_copy();
        current_move = move->deep_copy(board_copy);
        current_move->hypothetically_make_move();
        std::unique_ptr<Move> whites_best_move = board_copy.best_move_white(depth + 1, max_depth)->deep_copy(board_copy);
        whites_best_move->hypothetically_make_move();
        score = board_copy.evaluate();
        if (best_score > score) {
            best_score = score;
            best_move = current_move->deep_copy(*this);
        }
    }
    return best_move;
}