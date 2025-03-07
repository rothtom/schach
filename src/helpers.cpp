#include "helpers.hpp"

std::array<unsigned short, 2> chess_cord_to_index(ChessCoordinates chess) {
    std::array<unsigned short, 2> indexes = {0, 0};
    indexes[0] = chess.row;
    indexes[1] = (short)chess.collumn - 'A';
    return indexes;
}