#include <Pieces.hpp>
#include <iostream>

Piece::Piece(sf::Texture& texture, colors color, types type, ChessCoordinates coordinates, sf::Vector2f& piece_scale) :
    sprite_(texture), color_(color), type_(type), coordinates_(coordinates)
{
    sprite_.setScale(piece_scale);
    sprite_.setColor(sf::Color::Black);
};

void Piece::set_position(PixelCoordinates coordinates) {
    sprite_.setPosition({coordinates.x, coordinates.y});
}

void Piece::draw(sf::RenderWindow& window) {
    window.draw(sprite_);
}

Pawn::Pawn(sf::Texture texture, colors color, ChessCoordinates coordinates, sf::Vector2f piece_scale) :
    Piece(texture, color, PAWN, coordinates, piece_scale)
{};

Bishop::Bishop(sf::Texture texture, colors color, ChessCoordinates coordinates, sf::Vector2f piece_scale) :
    Piece(texture, color, BISHOP, coordinates, piece_scale)
{};

Knight::Knight(sf::Texture texture, colors color, ChessCoordinates coordinates, sf::Vector2f piece_scale) :
    Piece(texture, color, KNIGHT, coordinates, piece_scale)
{};

Rook::Rook(sf::Texture texture, colors color, ChessCoordinates coordinates, sf::Vector2f piece_scale) :
    Piece(texture, color, ROOK, coordinates, piece_scale)
{};

Queen::Queen(sf::Texture texture, colors color, ChessCoordinates coordinates, sf::Vector2f piece_scale) :
    Piece(texture, color, QUEEN, coordinates, piece_scale)
{};

King::King(sf::Texture texture, colors color, ChessCoordinates coordinates, sf::Vector2f piece_scale) :
    Piece(texture, color, KING, coordinates, piece_scale)
{};


std::vector<ChessCoordinates> Pawn::possible_moves() {
   
}

std::vector<ChessCoordinates> Bishop::possible_moves() {

}

std::vector<ChessCoordinates> Knight::possible_moves() {

}

std::vector<ChessCoordinates> Rook::possible_moves() {

}

std::vector<ChessCoordinates> Queen::possible_moves() {

}

std::vector<ChessCoordinates> King::possible_moves() {

}
