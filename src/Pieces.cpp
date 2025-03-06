#include <Pieces.hpp>


Piece::Piece(sf::Texture texture, colors color, types type, ChessCoordinates coordinates) :
    sprite_(texture), color_(color), type_(type), coordinates_(coordinates)
{};

void Piece::draw(float& tile_size, sf::Sprite& sprite) {
    // TODO
}

Pawn::Pawn(sf::Texture texture, colors color, ChessCoordinates coordinates) :
    Piece(texture, color, PAWN, coordinates)
{};

Bishop::Bishop(sf::Texture texture, colors color, ChessCoordinates coordinates) :
    Piece(texture, color, BISHOP, coordinates)
{};

Knight::Knight(sf::Texture texture, colors color, ChessCoordinates coordinates) :
    Piece(texture, color, KNIGHT, coordinates)
{};

Rook::Rook(sf::Texture texture, colors color, ChessCoordinates coordinates) :
    Piece(texture, color, ROOK, coordinates)
{};

Queen::Queen(sf::Texture texture, colors color, ChessCoordinates coordinates) :
    Piece(texture, color, QUEEN, coordinates)
{};

King::King(sf::Texture texture, colors color, ChessCoordinates coordinates) :
    Piece(texture, color, KING, coordinates)
{};


std::vector<ChessCoordinates> Pawn::possible_moves() {
    if (color_ == WHITE) {
        
    }
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
