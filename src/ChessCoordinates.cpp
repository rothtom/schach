#include "ChessCoordinates.hpp"


chess::ChessCoordinates::ChessCoordinates(char coll, unsigned short row)
: row(row), coll(coll)
{}

sf::Vector2i chess::ChessCoordinates::to_index() {
    int x = int(coll) - int('a');
    int y = row - 1;
    return {(x), (y)};
}

bool chess::ChessCoordinates::operator==(const ChessCoordinates& other) const {
    return (row == other.row) && (coll == other.coll);
}

void chess::ChessCoordinates::operator=(const ChessCoordinates& other) {
    row = other.row;
    coll = other.coll;
}

