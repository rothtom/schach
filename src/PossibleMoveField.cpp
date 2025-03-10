#include "PossibleMoveField.hpp"

PossibleMoveField::PossibleMoveField(ChessCoordinates coordinates, float square_length, sf::RenderWindow& window, sf::CircleShape circle) : 
chess_coordinates(coordinates), square_length_(square_length) , window_(window), circle_(circle)
{
    sf::Vector2f square_pos = chess_cord_to_abs_pos(chess_coordinates, square_length, window.getSize());
    pixel_coordinates_ = {square_pos.x + square_length_ / 2, square_pos.y + square_length_ / 2};
    circle_.setPosition(pixel_coordinates_);
};

void PossibleMoveField::draw() {
    window_.draw(circle_);
}

bool PossibleMoveField::check_clicked(sf::Vector2i& mousepos) {
    if (circle_.getGlobalBounds().contains({mousepos.x, mousepos.y})) {
        return true;
    }
    return false;
}