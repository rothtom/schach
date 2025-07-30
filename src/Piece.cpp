#include "Piece.hpp"
#include "Board.hpp"

#include <optional>

chess::Piece::Piece(color piece_color, ChessCoordinates coordinates, sf::Texture& texture, sf::RenderWindow& window, Board& board) 
: color_(piece_color), coordinates_(coordinates), texture_(texture), sprite_(texture), selected_(false), window_(window)
{
    board_ = &board;
}

void chess::Piece::setTexture(sf::Texture& texture) {
    texture_ = texture;
}

void chess::Piece::setBoard(chess::Board& board) {
    board_ = &board;
}

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
}

void chess::Piece::draw_possible_move_markers() {
    for (PossibleMoveMarker marker : possible_move_markers_) {
        marker.draw();
    }
}

void chess::Piece::update() {
    
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
    possible_move_markers_.reserve(possible_moves_.capacity());
    for (ChessCoordinates coordinate : possible_moves_) {
        possible_move_markers_.emplace_back(PossibleMoveMarker(coordinate, tile_width_, window_));
    }
    update_position();
}

void chess::Piece::set_possible_moves(std::vector<chess::ChessCoordinates> possible_moves) {
    possible_moves_ = possible_moves;
}

void chess::Piece::add_possible_move(chess::ChessCoordinates possible_move) {
    possible_moves_.emplace_back(possible_move);
}

void chess::Piece::reset_possible_moves() {
    possible_moves_ = {};
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

chess::Piece::~Piece() = default;


