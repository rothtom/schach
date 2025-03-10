#include "Pieces.hpp"
#include <iostream>


Piece::Piece(const std::map<ChessCoordinates, std::shared_ptr<Piece>>& pieces, sf::Texture& texture, colors color, types type, ChessCoordinates coordinates,float square_length, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker, sf::RenderWindow& window) :
    pieces_(pieces), sprite_(texture), color(color), type_(type), coordinates_(coordinates), possible_move_marker_(possible_move_marker), piece_scale_(piece_scale), square_length_(square_length), window_(window)
{
    possible_move_marker_.setOrigin({possible_move_marker_.getRadius(), possible_move_marker_.getRadius()});
    possible_move_marker_.setFillColor(sf::Color(75, 72, 71, 80));
    sprite_.setTexture(texture);
    sprite_.setScale(piece_scale);
    possible_moves_ = std::vector<PossibleMoveField>{};
    pixel_coordinates_ = chess_cord_to_abs_pos(coordinates_, square_length_, window_.getSize());
    // sprite_.setColor(sf::Color::Black);
};

void Piece::set_position() {
    pixel_coordinates_ = chess_cord_to_abs_pos(coordinates_, square_length_, window_.getSize());
    sprite_.setPosition(pixel_coordinates_);
}

void Piece::draw(sf::RenderWindow& window) {
    window.draw(sprite_);
    if (selected) {
        // float square_length = 45;
        /*
        for (ChessCoordinates possible_move : possible_moves()) {
            std::cout << "Collumn: " << possible_move.collumn << std::endl << "Row: " << possible_move.row << std::endl;
            sf::Vector2f square_pos = chess_cord_to_abs_pos(possible_move, square_length, window.getSize());
            possible_move_marker_.setPosition({square_pos.x + square_length / 2, square_pos.y + square_length / 2});
            possible_move_marker_.setFillColor(sf::Color::Magenta);
            window.draw(possible_move_marker_);
        }
        */
        for (PossibleMoveField possible_move : possible_moves_) {
            possible_move.draw();
        }
    }
}

void Piece::check_clicked(sf::Vector2i& mousepos, bool& moved) {
    if (sprite_.getGlobalBounds().contains({mousepos.x, mousepos.y})) {
        selected ? disselect() : select();
    }
    for (PossibleMoveField possible_move : possible_moves_) {
        if (possible_move.check_clicked(mousepos)) {
            selected ? disselect() : select();
            move(possible_move.chess_coordinates);
            moved = true;
        }
    }
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

void Piece::move(ChessCoordinates new_coordinates) {
    coordinates_ = new_coordinates;
    set_position();
    possible_moves();
}


Pawn::Pawn(const std::map<ChessCoordinates, std::shared_ptr<Piece>>& pieces, sf::Texture& texture, colors color, ChessCoordinates coordinates, float square_length, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker, sf::RenderWindow& window) :
    Piece(pieces, texture, color, PAWN, coordinates, square_length, piece_scale, possible_move_marker, window)
{};

Bishop::Bishop(const std::map<ChessCoordinates, std::shared_ptr<Piece>>& pieces, sf::Texture& texture, colors color, ChessCoordinates coordinates, float square_length, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker, sf::RenderWindow& window) :
    Piece(pieces, texture, color, BISHOP, coordinates, square_length, piece_scale, possible_move_marker, window)
{};

Knight::Knight(const std::map<ChessCoordinates, std::shared_ptr<Piece>>& pieces, sf::Texture& texture, colors color, ChessCoordinates coordinates, float square_length, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker, sf::RenderWindow& window) :
    Piece(pieces, texture, color, KNIGHT, coordinates, square_length, piece_scale, possible_move_marker, window)
{};

Rook::Rook(const std::map<ChessCoordinates, std::shared_ptr<Piece>>& pieces, sf::Texture& texture, colors color, ChessCoordinates coordinates, float square_length, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker, sf::RenderWindow& window) :
    Piece(pieces, texture, color, ROOK, coordinates, square_length, piece_scale, possible_move_marker, window)
{};

Queen::Queen(const std::map<ChessCoordinates, std::shared_ptr<Piece>>& pieces, sf::Texture& texture, colors color, ChessCoordinates coordinates, float square_length, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker, sf::RenderWindow& window) :
    Piece(pieces, texture, color, QUEEN, coordinates, square_length, piece_scale, possible_move_marker, window)
{};

King::King(const std::map<ChessCoordinates, std::shared_ptr<Piece>>& pieces, sf::Texture& texture, colors color, ChessCoordinates coordinates, float square_length, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker, sf::RenderWindow& window) :
    Piece(pieces, texture, color, KING, coordinates, square_length, piece_scale, possible_move_marker, window)
{};


void Pawn::possible_moves() {
    possible_moves_.clear();
    ChessCoordinates coordinates;
    if (color == WHITE) {
        coordinates = {static_cast<unsigned short>(coordinates_.row + 1), coordinates_.collumn};
        possible_moves_.emplace_back(PossibleMoveField(coordinates, square_length_, window_, possible_move_marker_));
        if (coordinates_.row == 2) {
            coordinates.row++;
            possible_moves_.emplace_back(PossibleMoveField(coordinates, square_length_, window_, possible_move_marker_));
        }
    }
    else {
        ChessCoordinates coordinates{coordinates_.row - 1, coordinates_.collumn};
        possible_moves_.emplace_back(PossibleMoveField(coordinates, square_length_, window_, possible_move_marker_));
        if (coordinates_.row == 7) {
            coordinates.row--;
            possible_moves_.emplace_back(PossibleMoveField(coordinates, square_length_, window_, possible_move_marker_));
        }
    }
}

void Bishop::possible_moves() {

}

void Knight::possible_moves() {

}

void Rook::possible_moves() {

}

void Queen::possible_moves() {

}

void King::possible_moves() {

}
