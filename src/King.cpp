#include "King.hpp"

chess::King::King(chess::color piece_color, ChessCoordinates coordinates, sf::Texture& texture, sf::RenderWindow& window, std::vector<std::unique_ptr<Piece>>& other_pieces)
: Piece(piece_color, coordinates, texture, window, other_pieces)
{}

std::vector<chess::ChessCoordinates> chess::King::get_possible_moves() {

}