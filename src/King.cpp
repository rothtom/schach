#include "King.hpp"

chess::King::King(chess::color piece_color, ChessCoordinates coordinates, sf::Texture& texture, sf::RenderWindow& window)
: Piece(piece_color, coordinates, texture, window)
{}