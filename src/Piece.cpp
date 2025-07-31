#include "Piece.hpp"
#include "Board.hpp"
#include "PossibleMoveMarker.hpp"
#include "PossiblePromotionMarker.hpp"
#include "PromotionMove.hpp"


#include <optional>

chess::Piece::Piece(color piece_color, ChessCoordinates coordinates, sf::Texture& texture, sf::RenderWindow& window, Board& board) 
: color_(piece_color), coordinates_(coordinates), texture_(texture), sprite_(texture), selected_(false), window_(window)
{
    board_ = &board;
}

chess::Piece::Piece(const chess::Piece& other) 
: color_(other.color_), coordinates_(other.coordinates_), texture_(other.texture_), sprite_(texture_), selected_(false), window_(other.window_)
{
    for (const auto& move : other.possible_moves_) {
        possible_moves_.emplace_back(std::make_unique<chess::Move>(*move));  // assumes Move has a copy constructor
    }
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
        marker->resize(tile_width);
    }
}

void chess::Piece::draw() {
    window_.draw(sprite_);
}

void chess::Piece::draw_possible_move_markers() {
    for (std::unique_ptr<PossibleMoveMarker>& marker : possible_move_markers_) {
        marker->draw();
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
        if (marker->is_clicked(mouse_pos)) {
            return marker->get_coordinates();
        }
    }
    return std::nullopt;
}


void chess::Piece::select() {
    selected_ = true;
    possible_move_markers_.reserve(possible_moves_.capacity());
    for (std::unique_ptr<Move>& move : possible_moves_) {
        if (dynamic_cast<PromotionMove*>(move.get())) {
            if (color_ == WHITE) {
                if (move->get_piece_name_to_promote_to() == QUEEN) {
                    possible_move_markers_.emplace_back(std::make_unique<PossiblePromotionMarker>(move->get_target_cords(), color_, QUEEN, tile_width_, board_->textures["w-queen"] , window_)); 
                }
                else if (move->get_piece_name_to_promote_to() == ROOK) {
                    possible_move_markers_.emplace_back(std::make_unique<PossiblePromotionMarker>(move->get_target_cords(), color_, ROOK, tile_width_, board_->textures["w-rook"] , window_)); 
                }
                else if (move->get_piece_name_to_promote_to() == BISHOP) {
                    possible_move_markers_.emplace_back(std::make_unique<PossiblePromotionMarker>(move->get_target_cords(), color_, BISHOP, tile_width_, board_->textures["w-bishop"] , window_)); 
                }
                else if (move->get_piece_name_to_promote_to() == KNIGHT) {
                    possible_move_markers_.emplace_back(std::make_unique<PossiblePromotionMarker>(move->get_target_cords(), color_, KNIGHT, tile_width_, board_->textures["w-knight"] , window_)); 
                }
            }
            else {
                if (move->get_piece_name_to_promote_to() == QUEEN) {
                    possible_move_markers_.emplace_back(std::make_unique<PossiblePromotionMarker>(move->get_target_cords(), color_, QUEEN, tile_width_, board_->textures["b-queen"] , window_)); 
                }
                else if (move->get_piece_name_to_promote_to() == ROOK) {
                    possible_move_markers_.emplace_back(std::make_unique<PossiblePromotionMarker>(move->get_target_cords(), color_, ROOK, tile_width_, board_->textures["b-rook"] , window_)); 
                }
                else if (move->get_piece_name_to_promote_to() == BISHOP) {
                    possible_move_markers_.emplace_back(std::make_unique<PossiblePromotionMarker>(move->get_target_cords(), color_, BISHOP, tile_width_, board_->textures["b-bishop"] , window_)); 
                }
                else if (move->get_piece_name_to_promote_to() == KNIGHT) {
                    possible_move_markers_.emplace_back(std::make_unique<PossiblePromotionMarker>(move->get_target_cords(), color_, KNIGHT, tile_width_, board_->textures["b-knight"] , window_)); 
                }
            }
            
        }
        else {
            possible_move_markers_.emplace_back(std::make_unique<PossibleMoveMarker>(move->get_target_cords(), tile_width_, window_)); 
        }
    }
    update_position();
}

void chess::Piece::add_possible_move(chess::Move possible_move) {
    possible_moves_.emplace_back(std::make_unique<Move>(possible_move));
}

void chess::Piece::reset_possible_moves() {
    possible_moves_.clear();
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


