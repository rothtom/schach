#include "Piece.hpp"

chess::Piece::Piece(color piece_color, ChessCoordinates coordinates, sf::Texture& texture, sf::RenderWindow& window, std::vector<std::unique_ptr<Piece>>& other_pieces) 
: color_(piece_color), coordinates_(coordinates), texture_(texture), sprite_(texture), selected_(false), window_(window), other_pieces_(other_pieces)
{}

void chess::Piece::resize(int tile_width) {
    tile_width_ = tile_width;
    sprite_scale_ = tile_width_ / sprite_.getTexture().getSize().x;
    sprite_.setScale({sprite_scale_, sprite_scale_});
    update_position();
}

void chess::Piece::draw() {
    window_.draw(sprite_);
    for (PossibleMoveMarker marker : possible_move_markers_) {
        marker.draw();
    }
}

void chess::Piece::update() {
    
}

bool chess::Piece::is_clicked(sf::Vector2i mouse_pos) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) and is_hovered(mouse_pos)) {
        return true;
    }
    return false;
}

bool chess::Piece::is_hovered(sf::Vector2i mouse_pos) {
    if (mouse_pos.x > position_.x and mouse_pos.x < position_.x + tile_width_ and
        mouse_pos.y > position_.y and mouse_pos.y < position_.y + tile_width_) {
            return true;
    }
    return false;
}

void chess::Piece::select() {
    selected_ = true;
    std::cout << "Selected" << std::endl;
    std::vector<ChessCoordinates> possible_fields;
    possible_move_markers_.reserve(possible_fields.capacity());
    for (ChessCoordinates coordinate : possible_fields) {
        possible_move_markers_.emplace_back(PossibleMoveMarker(coordinate, tile_width_, window_));
    }
}

void chess::Piece::disselect() {
    selected_ = false;
    std::cout << "Disselected" << std::endl;
    possible_move_markers_.clear();
}

void chess::Piece::update_position() {
    sf::Vector2i indexes = coordinates_.to_index();
    position_ = sf::Vector2f({tile_width_ * indexes.x, tile_width_ * 7 - tile_width_ * indexes.y});
    sprite_.setPosition(position_);
}

const chess::ChessCoordinates& chess::Piece::get_coordinates() const {
    return coordinates_;
}

const chess::color& chess::Piece::get_color() const {
    return color_;
}

void chess::Piece::move(ChessCoordinates new_coordinates) {
    coordinates_ = new_coordinates;
    update_position();
}


