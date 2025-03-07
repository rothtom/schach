#include <Pieces.hpp>
#include <iostream>

Piece::Piece(sf::Texture& texture, colors color, types type, ChessCoordinates coordinates, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker) :
    sprite_(texture), color(color), type_(type), coordinates_(coordinates), possible_move_marker_(possible_move_marker), piece_scale_(piece_scale)
{
    possible_move_marker_.setScale(piece_scale);
    float radius = possible_move_marker_.getLocalBounds().size.x / 2;
    possible_move_marker_.setOrigin({radius, radius});
    sprite_.setTexture(texture);
    sprite_.setScale(piece_scale);
    // sprite_.setColor(sf::Color::Black);
};

void Piece::set_position(sf::Vector2f coordinates) {
    sprite_.setPosition(coordinates);
}

void Piece::draw(sf::RenderWindow& window) {
    window.draw(sprite_);
    if (selected) {
        float square_length = 480 * piece_scale_.x;
        // float square_length = 45;
        for (ChessCoordinates possible_move : possible_moves()) {
            std::cout << "Collumn: " << possible_move.collumn << std::endl << "Row: " << possible_move.row << std::endl;
            sf::Vector2f square_pos = chess_cord_to_abs_pos(possible_move, square_length, window.getSize());
            possible_move_marker_.setPosition({square_pos.x + square_length / 2, square_pos.y + square_length / 2});
            possible_move_marker_.setFillColor(sf::Color::Magenta);
            window.draw(possible_move_marker_);
        }
    }
}

bool Piece::check_clicked(sf::Vector2i& mousepos) {
    if (sprite_.getGlobalBounds().contains({mousepos.x, mousepos.y})) {
        return true;
    }
    return false;
}

void Piece::select() {
    color == WHITE ? sprite_.move({0, -10}) : sprite_.move({0, 10});
    selected = true;
}

void Piece::disselect() {
    if (selected) {
        color == WHITE ? sprite_.move({0, 10}) : sprite_.move({0, -10});
    }
    selected = false;
}


Pawn::Pawn(sf::Texture& texture, colors color, ChessCoordinates coordinates, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker) :
    Piece(texture, color, PAWN, coordinates, piece_scale, possible_move_marker)
{};

Bishop::Bishop(sf::Texture& texture, colors color, ChessCoordinates coordinates, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker) :
    Piece(texture, color, BISHOP, coordinates, piece_scale, possible_move_marker)
{};

Knight::Knight(sf::Texture& texture, colors color, ChessCoordinates coordinates, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker) :
    Piece(texture, color, KNIGHT, coordinates, piece_scale, possible_move_marker)
{};

Rook::Rook(sf::Texture& texture, colors color, ChessCoordinates coordinates, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker) :
    Piece(texture, color, ROOK, coordinates, piece_scale, possible_move_marker)
{};

Queen::Queen(sf::Texture& texture, colors color, ChessCoordinates coordinates, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker) :
    Piece(texture, color, QUEEN, coordinates, piece_scale, possible_move_marker)
{};

King::King(sf::Texture& texture, colors color, ChessCoordinates coordinates, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker) :
    Piece(texture, color, KING, coordinates, piece_scale, possible_move_marker)
{};


std::vector<ChessCoordinates> Pawn::possible_moves() {
    std::vector<ChessCoordinates> possible_moves;
    if (color == WHITE) {
        std::cout << "row before: " << coordinates_.row << std::endl;
        ChessCoordinates coordinates{coordinates_.row + 1, coordinates_.collumn};
        possible_moves.emplace_back(coordinates);
        if (coordinates_.row == 2) {
            coordinates.row++;
            possible_moves.emplace_back(coordinates);
        }
    }
    else {
        ChessCoordinates coordinates{coordinates_.row - 1, coordinates_.collumn};
        possible_moves.emplace_back(coordinates);
        if (coordinates_.row == 7) {
            coordinates.row--;
            possible_moves.emplace_back(coordinates);
        }
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
