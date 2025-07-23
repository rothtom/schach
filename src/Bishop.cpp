#include "Bishop.hpp"

chess::Bishop::Bishop(chess::color piece_color, ChessCoordinates coordinates, sf::Texture& texture, sf::RenderWindow& window)
: Piece(piece_color, coordinates, texture, window)
{}