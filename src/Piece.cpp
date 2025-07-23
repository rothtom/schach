#include "Piece.hpp"

chess::Piece::Piece(color piece_color, ChessCoordinates coordinates, sf::Texture& texture, sf::RenderWindow& window) 
: color_(piece_color), coordinates_(coordinates), texture_(texture), sprite_(texture), window_(window)
{}

void chess::Piece::resize(int tile_width) {
    tile_width_ = tile_width;
    sprite_scale_ = static_cast<float>(tile_width_) / sprite_.getTexture().getSize().x;
    sprite_.setScale({sprite_scale_, sprite_scale_});

    std::cout << "Tile width: " << tile_width_ << " Texture size: " << sprite_.getTexture().getSize().x << " Sprite scale: " << sprite_.getScale().x << std::endl;
}

void chess::Piece::draw() {
    std::cout << "Tile width: " << tile_width_ << " Texture size: " << sprite_.getTexture().getSize().x << " Sprite scale: " << sprite_.getScale().x << std::endl;
    resize(62);
    std::cout << "Tile width: " << tile_width_ << " Texture size: " << sprite_.getTexture().getSize().x << " Sprite scale: " << sprite_.getScale().x << std::endl;
    update();
    window_.draw(sprite_);
}

void chess::Piece::update() {
    sf::Vector2f indexes = coordinates_.to_index();
    sprite_.setPosition({tile_width_ * indexes.x, tile_width_ * indexes.y});
}
