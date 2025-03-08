#include <Pieces.hpp>
#include <iostream>

Piece::Piece(sf::Texture& texture, colors color, types type, ChessCoordinates coordinates,float square_length, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker, sf::RenderWindow& window) :
    sprite_(texture), color(color), type_(type), coordinates_(coordinates), possible_move_marker_(possible_move_marker), piece_scale_(piece_scale), square_length_(square_length), window_(window)
{
    float radius = possible_move_marker_.getLocalBounds().size.x / 2;
    possible_move_marker_.setOrigin({radius, radius});
    possible_move_marker_.setFillColor(sf::Color(75, 72, 71, 80));
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
        for (PossibleMoveField possible_move : possible_moves()) {
            possible_move.draw();
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


Pawn::Pawn(sf::Texture& texture, colors color, ChessCoordinates coordinates, float square_length, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker, sf::RenderWindow& window) :
    Piece(texture, color, PAWN, coordinates, square_length, piece_scale, possible_move_marker, window)
{};

Bishop::Bishop(sf::Texture& texture, colors color, ChessCoordinates coordinates, float square_length, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker, sf::RenderWindow& window) :
    Piece(texture, color, BISHOP, coordinates, square_length, piece_scale, possible_move_marker, window)
{};

Knight::Knight(sf::Texture& texture, colors color, ChessCoordinates coordinates, float square_length, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker, sf::RenderWindow& window) :
    Piece(texture, color, KNIGHT, coordinates, square_length, piece_scale, possible_move_marker, window)
{};

Rook::Rook(sf::Texture& texture, colors color, ChessCoordinates coordinates, float square_length, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker, sf::RenderWindow& window) :
    Piece(texture, color, ROOK, coordinates, square_length, piece_scale, possible_move_marker, window)
{};

Queen::Queen(sf::Texture& texture, colors color, ChessCoordinates coordinates, float square_length, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker, sf::RenderWindow& window) :
    Piece(texture, color, QUEEN, coordinates, square_length, piece_scale, possible_move_marker, window)
{};

King::King(sf::Texture& texture, colors color, ChessCoordinates coordinates, float square_length, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker, sf::RenderWindow& window) :
    Piece(texture, color, KING, coordinates, square_length, piece_scale, possible_move_marker, window)
{};


std::vector<PossibleMoveField> Pawn::possible_moves() {
    std::vector<PossibleMoveField> possible_move_fields;
    ChessCoordinates coordinates;
    if (color == WHITE) {
        coordinates = {static_cast<unsigned short>(coordinates_.row + 1), coordinates_.collumn};
        possible_move_fields.emplace_back(PossibleMoveField(coordinates, square_length_, window_, possible_move_marker_));
        if (coordinates_.row == 2) {
            coordinates.row++;
            possible_move_fields.emplace_back(PossibleMoveField(coordinates, square_length_, window_, possible_move_marker_));
        }
    }
    else {
        ChessCoordinates coordinates{coordinates_.row - 1, coordinates_.collumn};
        possible_move_fields.emplace_back(PossibleMoveField(coordinates, square_length_, window_, possible_move_marker_));
        if (coordinates_.row == 7) {
            coordinates.row--;
            possible_move_fields.emplace_back(PossibleMoveField(coordinates, square_length_, window_, possible_move_marker_));
        }
    }
    return possible_move_fields;
}

std::vector<PossibleMoveField> Bishop::possible_moves() {

}

std::vector<PossibleMoveField> Knight::possible_moves() {

}

std::vector<PossibleMoveField> Rook::possible_moves() {

}

std::vector<PossibleMoveField> Queen::possible_moves() {

}

std::vector<PossibleMoveField> King::possible_moves() {

}
