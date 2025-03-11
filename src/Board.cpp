#include "Board.hpp"

#include <iostream>


Board::Board(sf::RenderWindow& window) : window_(window) {
    square_length_ = std::min(window_.getSize().x, window_.getSize().y) / 8;
    float piece_scale = square_length_ / 480;
    piece_scale_ = {piece_scale, piece_scale};
    tile_ = sf::RectangleShape(sf::Vector2f(square_length_, square_length_));
    possible_move_marker_ = sf::CircleShape(480 * 0.4 / 2);
    set_textures();
    load_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq e3 0 1");
    set_piece_positions();
};

void Board::set_textures() {
    textures_['p'] = sf::Texture("/home/tom/Documents/code/schach/assets/b-pawn.png");
    textures_['b'] = sf::Texture("/home/tom/Documents/code/schach/assets/b-bishop.png");
    textures_['n'] = sf::Texture("/home/tom/Documents/code/schach/assets/b-knight.png");
    textures_['r'] = sf::Texture("/home/tom/Documents/code/schach/assets/b-rook.png");
    textures_['q'] = sf::Texture("/home/tom/Documents/code/schach/assets/b-queen.png");
    textures_['k'] = sf::Texture("/home/tom/Documents/code/schach/assets/b-king.png");
    textures_['P'] = sf::Texture("/home/tom/Documents/code/schach/assets/w-pawn.png");
    textures_['B'] = sf::Texture("/home/tom/Documents/code/schach/assets/w-bishop.png");
    textures_['N'] = sf::Texture("/home/tom/Documents/code/schach/assets/w-knight.png");
    textures_['R'] = sf::Texture("/home/tom/Documents/code/schach/assets/w-rook.png");
    textures_['Q'] = sf::Texture("/home/tom/Documents/code/schach/assets/w-queen.png");
    textures_['K'] = sf::Texture("/home/tom/Documents/code/schach/assets/w-king.png");
    for (auto& [c, texture] : textures_) {
        texture.setSmooth(true);
    }
}


void Board::load_fen(std::string s) {
    unsigned short collumn = 'A';
    unsigned short row = 8;
    for (char c : s) {
        if (c == ' ') {break;}
        else if (c == '/') {
            collumn = 'A';
            row--;
        }
        else if (c >= '1' && c <= '8') {
            collumn = collumn + c - '0';
        }
        else {
            ChessCoordinates coordinates{row, collumn};
            pieces_[coordinates] = create_piece(c, coordinates);
            // check for possible moves once at start, then handeled after move making
            pieces_[coordinates]->possible_moves();
            collumn++;
        }
    }
}

void Board::set_piece_positions() {
    for (const auto& [coordinates, piece] : pieces_) {
        piece->set_position();
    }
}

std::shared_ptr<Piece> Board::create_piece(char type_char, const ChessCoordinates& coordinates) {
    colors color;
    std::isupper(type_char) ? color = colors::WHITE : color = colors::BLACK;
    switch(std::tolower(type_char)) {
        case('p'):
            return std::make_shared<Pawn>(pieces_, textures_[type_char], color, coordinates, square_length_, piece_scale_, possible_move_marker_, window_);
        case('b'):
            return std::make_shared<Bishop>(pieces_, textures_[type_char], color, coordinates, square_length_, piece_scale_, possible_move_marker_, window_);
        case('n'):
            return std::make_shared<Knight>(pieces_, textures_[type_char], color, coordinates, square_length_, piece_scale_, possible_move_marker_, window_);
        case('r'):
            return std::make_shared<Rook>(pieces_, textures_[type_char], color, coordinates, square_length_, piece_scale_, possible_move_marker_, window_);
        case('q'):
            return std::make_shared<Queen>(pieces_, textures_[type_char], color, coordinates, square_length_, piece_scale_, possible_move_marker_, window_);
        case('k'):
            return std::make_shared<King>(pieces_, textures_[type_char], color, coordinates, square_length_, piece_scale_, possible_move_marker_, window_);
        default:
            return nullptr;
    }
}


void Board::draw() {
    window_.clear(sf::Color(0, 0, 0));
    draw_tiles_();
    draw_pieces_();
    window_.display();
}

void Board::draw_tiles_() {
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            tile_.setPosition(sf::Vector2f(square_length_*i, square_length_*j));
            (i + j) % 2 == 1 ? tile_.setFillColor(sf::Color(78, 120, 55)) : tile_.setFillColor(sf::Color(255, 255, 255));
            window_.draw(tile_);
        }
    }
}

void Board::draw_pieces_() {
    for (const auto&  [coordinates, piece] : pieces_) {
        // std::cout << "Hi" << std::endl;
        piece->draw_piece();
    }
    if (selected_piece_ != nullptr) {
        selected_piece_->draw_possible_moves();
    }
}

void Board::check_piece_selected(sf::Vector2i& mousepos) {
    bool moved = false;
    for (auto& [coordinates, piece] : pieces_) {
        if (piece->color != next_move) {continue;}
        else {
            piece->check_clicked(mousepos, moved);
        }
    }
}

