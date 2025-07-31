#include "PossiblePromotionMarker.hpp"
#include "colors.hpp"
#include "helpers.hpp"
#include "Piece.hpp"

#include "Queen.hpp"
#include "Rook.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"

chess::PossiblePromotionMarker::PossiblePromotionMarker(chess::ChessCoordinates coordinates, color pawn_color, piece_name piece_to_promote_to,
float& tile_width, sf::Texture& texture, sf::RenderWindow& window)
: PossibleMoveMarker(coordinates, tile_width, window), piece_to_promote_to_(piece_to_promote_to), pawn_color_(pawn_color), texture_(texture), sprite_(texture_)
{
    resize(tile_width_);
}

void chess::PossiblePromotionMarker::draw() {
    window_.draw(sprite_);
}

void chess::PossiblePromotionMarker::update_position() {
    if (piece_to_promote_to_ == QUEEN) {
        sprite_.setPosition(sf::Vector2f({coordinates_.to_index().x * tile_width_, window_.getSize().y - (coordinates_.to_index().y + 1) * tile_width_}));
    }
    else if (piece_to_promote_to_ == ROOK) {
        sprite_.setPosition(sf::Vector2f({coordinates_.to_index().x * tile_width_ + (tile_width_ / 2), window_.getSize().y - (coordinates_.to_index().y + 1) * tile_width_}));
    }
    else if (piece_to_promote_to_ == BISHOP) {
        sprite_.setPosition(sf::Vector2f({coordinates_.to_index().x * tile_width_, window_.getSize().y - (coordinates_.to_index().y + 1) * tile_width_ + (tile_width_ / 2)}));
    }
    else if (piece_to_promote_to_ == KNIGHT) {
        sprite_.setPosition(sf::Vector2f({coordinates_.to_index().x * tile_width_ + (tile_width_ / 2), window_.getSize().y - (coordinates_.to_index().y + 1) * tile_width_ + (tile_width_ / 2)}));
    }
}

void chess::PossiblePromotionMarker::resize(float tile_width) {
    tile_width_ = tile_width;
    sprite_scale_ = (tile_width_ / 2) / sprite_.getTexture().getSize().x;
    sprite_.setScale({sprite_scale_, sprite_scale_});
    update_position();
}

std::optional<chess::piece_name> chess::PossiblePromotionMarker::is_clicked(sf::Vector2i& mouse_pos) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) and is_hovered(mouse_pos)) {
        return piece_to_promote_to_;
    }
}

bool chess::PossiblePromotionMarker::is_hovered(sf::Vector2i& mouse_pos) {
    if (mouse_pos.x > position_.x and mouse_pos.x < position_.x + tile_width_ and
        mouse_pos.y > position_.y and mouse_pos.y < position_.y + tile_width_) {
            return true;
    }
    return false;
}