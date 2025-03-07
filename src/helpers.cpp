#include "helpers.hpp"

sf::Vector2u chess_cord_to_index(ChessCoordinates chess) {
    sf::Vector2u indexes = {0, 0};
    indexes.x = chess.row;
    indexes.y = (short)chess.collumn - 'A';
    return indexes;
}

sf::Vector2f chess_cord_to_abs_pos(const ChessCoordinates& chess, const float& square_length, const sf::Vector2u& window_size) {
    float x = (static_cast<int>(chess.collumn) - 'A') * square_length;
    float y = window_size.y - (chess.row) * square_length;
    return sf::Vector2f{x, y};
}