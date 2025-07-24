#include "PossibleMoveMarker.hpp"


chess::PossibleMoveMarker::PossibleMoveMarker(chess::ChessCoordinates coordinates, float& tile_width, sf::RenderWindow& window) 
: window_(window), coordinates_(coordinates), tile_width_(tile_width), circle_(sf::CircleShape(tile_width_ * 0.8))
{}

void chess::PossibleMoveMarker::resize(int new_tile_width) {
    tile_width_ = new_tile_width;
    circle_.setRadius(tile_width_ * 0.8);
    update_position();
}

void chess::PossibleMoveMarker::update_position() {
    sf::Vector2i indexes = coordinates_.to_index();
    position_ = sf::Vector2f({tile_width_ * indexes.x, tile_width_ * 7 - tile_width_ * indexes.y});
    circle_.setPosition(position_);
}

void chess::PossibleMoveMarker::draw() {
    window_.draw(circle_);
}