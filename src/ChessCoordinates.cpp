#include "ChessCoordinates.hpp"


chess::ChessCoordinates::ChessCoordinates(char coll, unsigned short row)
: row(row), coll(coll)
{}

sf::Vector2f chess::ChessCoordinates::to_index() {
    int x = int(coll) - int('a');
    int y = row - 1;
    return {static_cast<float>(x), static_cast<float>(y)};
}