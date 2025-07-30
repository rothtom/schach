#include "Board.hpp"

#include "King.hpp"
#include "Queen.hpp"
#include "Rook.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"
#include "Pawn.hpp"



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
    
    return score[WHITE] - score[BLACK];
}

move chess::Board::best_move() {
    std::chrono::seconds time_elapsed(0);
    
}

move chess::Board::best_move_white() {

}

move chess::Board::best_move_black() {

}