#include "Queen.hpp"

chess::Queen::Queen(chess::color piece_color, ChessCoordinates coordinates, sf::Texture& texture, sf::RenderWindow& window, std::vector<std::unique_ptr<Piece>>& other_pieces)
: Piece(piece_color, coordinates, texture, window, other_pieces)
{}

std::vector<chess::ChessCoordinates> chess::Queen::get_possible_moves() {
    
}