#include "Queen.hpp"

chess::Queen::Queen(chess::color piece_color, ChessCoordinates coordinates, sf::Texture& texture, sf::RenderWindow& window)
: Piece(piece_color, coordinates, texture, window)
{}