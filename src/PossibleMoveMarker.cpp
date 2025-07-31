#include "PossibleMoveMarker.hpp"

#include <iostream>


chess::PossibleMoveMarker::PossibleMoveMarker(chess::ChessCoordinates coordinates, float& tile_width, Move& move, sf::RenderWindow& window) 
: move_(move), window_(window), coordinates_(coordinates), tile_width_(tile_width), circle_(sf::CircleShape(tile_width_ * 0.5 / 2))
{
    circle_.setFillColor({0, 255, 255});
    update_position();
}

void chess::PossibleMoveMarker::resize(int new_tile_width) {
    tile_width_ = new_tile_width;
    circle_.setRadius(tile_width_ * 0.5 / 2);
    update_position();
}

void chess::PossibleMoveMarker::update_position() {
    circle_.setOrigin({circle_.getRadius(), circle_.getRadius()});
    sf::Vector2i indexes = coordinates_.to_index();
    // upper left corner of tile
    position_ = sf::Vector2f({tile_width_ * indexes.x, tile_width_ * 7 - tile_width_ * indexes.y});
    //adjust to middle
    position_.x += tile_width_ / 2;
    position_.y += tile_width_ / 2;
    circle_.setPosition(position_);
}

void chess::PossibleMoveMarker::draw() {
    window_.draw(circle_);
}

bool chess::PossibleMoveMarker::is_clicked(sf::Vector2i& mouse_pos) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) and is_hovered(mouse_pos)) {
        return true;
    }
    return false;
}

bool chess::PossibleMoveMarker::is_hovered(sf::Vector2i& mouse_pos) {
    float radius = circle_.getRadius();
    if (mouse_pos.x > position_.x - radius and mouse_pos.x < position_.x + radius and
        mouse_pos.y > position_.y - radius and mouse_pos.y < position_.y + radius) {
            return true;
    }
    return false;
}

chess::ChessCoordinates chess::PossibleMoveMarker::get_coordinates() const {
    return coordinates_;
}

sf::Vector2f chess::PossibleMoveMarker::get_position() const {
    return position_;
}

float chess::PossibleMoveMarker::get_radius() const {
    return circle_.getRadius();
}

chess::Move& chess::PossibleMoveMarker::get_move() const {
    return move_;
}