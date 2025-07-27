#include "Piece.hpp"
#include "Board.hpp"

#include <optional>

chess::Piece::Piece(color piece_color, ChessCoordinates coordinates, sf::Texture& texture, sf::RenderWindow& window, Board& board) 
: board_(board), color_(piece_color), coordinates_(coordinates), texture_(texture), sprite_(texture), selected_(false), window_(window)
{}

void chess::Piece::resize(int tile_width) {
    tile_width_ = tile_width;
    sprite_scale_ = tile_width_ / sprite_.getTexture().getSize().x;
    sprite_.setScale({sprite_scale_, sprite_scale_});
    update_position();

    for (auto& marker : possible_move_markers_) {
        marker.resize(tile_width);
    }
}

void chess::Piece::draw() {
    window_.draw(sprite_);
    for (PossibleMoveMarker marker : possible_move_markers_) {
        marker.draw();
    }
}

void chess::Piece::update() {
    
}

std::vector<chess::ChessCoordinates> chess::Piece::check_discovered_check(std::vector<chess::ChessCoordinates>& possible_moves, int depth) {
    if (depth >= 2) {
        return possible_moves;
    }
    const std::unique_ptr<chess::Piece>& same_color_king = chess::get_king(board_.get_pieces(), color_);
    for(std::vector<ChessCoordinates>::iterator it = possible_moves.begin(); it != possible_moves.end();) {
        chess::Board copied_board = board_.deep_copy();
        copied_board.move(*this, *it);
        if (chess::is_in_check(copied_board.get_pieces(), same_color_king)) {
            possible_moves.erase(it);
        }
    }
    return possible_moves;
}


bool chess::Piece::is_clicked(sf::Vector2i& mouse_pos) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) and is_hovered(mouse_pos)) {
        return true;
    }
    return false;
}

bool chess::Piece::is_hovered(sf::Vector2i& mouse_pos) {
    if (mouse_pos.x > position_.x and mouse_pos.x < position_.x + tile_width_ and
        mouse_pos.y > position_.y and mouse_pos.y < position_.y + tile_width_) {
            return true;
    }
    return false;
}

std::optional<chess::ChessCoordinates> chess::Piece::marker_clicked(sf::Vector2i& mouse_pos) {
    for (auto& marker : possible_move_markers_) {
        if (marker.is_clicked(mouse_pos)) {
            return marker.get_coordinates();
        }
    }
    return std::nullopt;
}


void chess::Piece::select() {
    selected_ = true;
    std::vector<ChessCoordinates> possible_fields = get_possible_moves(1);
    possible_move_markers_.reserve(possible_fields.capacity());
    for (ChessCoordinates coordinate : possible_fields) {
        possible_move_markers_.emplace_back(PossibleMoveMarker(coordinate, tile_width_, window_));
    }
    update_position();
}

void chess::Piece::disselect() {
    selected_ = false;
    possible_move_markers_.clear();
    update_position();    
}

bool chess::Piece::is_selected() const {
    return selected_;
}

void chess::Piece::update_position() {
    sf::Vector2i indexes = coordinates_.to_index();
    position_ = sf::Vector2f({tile_width_ * indexes.x, tile_width_ * 7 - tile_width_ * indexes.y});
    if (selected_) {
        position_.y -= tile_width_ * 0.15;
    }
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
    possible_move_markers_.clear();
    disselect();
    update_position();
}


