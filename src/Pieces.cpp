#include <Pieces.hpp>
#include <iostream>

Piece::Piece(sf::Texture& texture, colors color, types type, ChessCoordinates coordinates, sf::Vector2f piece_scale) :
    sprite_(texture), color(color), type_(type), coordinates_(coordinates)
{
    sprite_.setTexture(texture);
    sprite_.setScale(piece_scale);
    // sprite_.setColor(sf::Color::Black);
};

void Piece::set_position(sf::Vector2f coordinates) {
    sprite_.setPosition(coordinates);
}

void Piece::draw(sf::RenderWindow& window) {
    window.draw(sprite_);
}

bool Piece::check_clicked(sf::Vector2i& mousepos) {
    if (sprite_.getGlobalBounds().contains({mousepos.x, mousepos.y})) {
        return true;
    }
    return false;
}

void Piece::select() {
    color == WHITE ? sprite_.move({0, 10}) : sprite_.move({0, -10});
    selected = true;
}

void Piece::disselect() {
    if (selected) {
        color == WHITE ? sprite_.move({0, -10}) : sprite_.move({0, 10});
    }
    selected = false;
}


Pawn::Pawn(sf::Texture& texture, colors color, ChessCoordinates coordinates, sf::Vector2f piece_scale) :
    Piece(texture, color, PAWN, coordinates, piece_scale)
{};

Bishop::Bishop(sf::Texture& texture, colors color, ChessCoordinates coordinates, sf::Vector2f piece_scale) :
    Piece(texture, color, BISHOP, coordinates, piece_scale)
{};

Knight::Knight(sf::Texture& texture, colors color, ChessCoordinates coordinates, sf::Vector2f piece_scale) :
    Piece(texture, color, KNIGHT, coordinates, piece_scale)
{};

Rook::Rook(sf::Texture& texture, colors color, ChessCoordinates coordinates, sf::Vector2f piece_scale) :
    Piece(texture, color, ROOK, coordinates, piece_scale)
{};

Queen::Queen(sf::Texture& texture, colors color, ChessCoordinates coordinates, sf::Vector2f piece_scale) :
    Piece(texture, color, QUEEN, coordinates, piece_scale)
{};

King::King(sf::Texture& texture, colors color, ChessCoordinates coordinates, sf::Vector2f piece_scale) :
    Piece(texture, color, KING, coordinates, piece_scale)
{};


std::vector<ChessCoordinates> Pawn::possible_moves() {
    std::vector<ChessCoordinates> possible_moves;
    possible_moves.resize(2);
    if (color == WHITE) {
        ChessCoordinates coordinates{coordinates_.collumn, coordinates_.row + 1};
        possible_moves.emplace_back(coordinates);
        if (coordinates_.row == 2) {
            coordinates.row++;
            possible_moves.emplace_back(coordinates);
        }
        return possible_moves;
    }
    ChessCoordinates coordinates{coordinates_.collumn, coordinates_.row - 1};
        possible_moves.emplace_back(coordinates);
        if (coordinates_.row == 7) {
            coordinates.row--;
            possible_moves.emplace_back(coordinates);
        }
        return possible_moves;
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
