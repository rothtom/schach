#include "Piece.hpp"

chess::Piece::Piece(color piece_color, ChessCoordinates coordinates, sf::Texture texture) 
: color_(piece_color), coordinates_(coordinates), texture_(texture), sprite_(texture)
{}

void chess::Piece::draw() {
    return;
}

void chess::Piece::update() {
    
}
