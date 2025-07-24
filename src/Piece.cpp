#include "Piece.hpp"

chess::Piece::Piece(color piece_color, ChessCoordinates coordinates, sf::Texture& texture, sf::RenderWindow& window) 
: color_(piece_color), coordinates_(coordinates), texture_(texture), sprite_(texture), window_(window)
{}

void chess::Piece::resize(int tile_width) {
    tile_width_ = tile_width;
    sprite_scale_ = tile_width_ / sprite_.getTexture().getSize().x;
    sprite_.setScale({sprite_scale_, sprite_scale_});
    update_position();
}

void chess::Piece::draw() {
    window_.draw(sprite_);
}

void chess::Piece::update() {

}

void chess::Piece::update_position() {
    sf::Vector2f indexes = coordinates_.to_index();
    sprite_.setPosition({tile_width_ * indexes.x, tile_width_ * 7 - tile_width_ * indexes.y});
}
