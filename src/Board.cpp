#include "Board.hpp"

#include <iostream>


Board::Board(sf::RenderWindow& window) : window_(window) {
    square_length_ = std::min(window_.getSize().x, window_.getSize().y) / 8;
    float piece_scale = square_length_ / 480;
    piece_scale_ = {piece_scale, piece_scale};
    tile_ = sf::RectangleShape(sf::Vector2f(square_length_, square_length_));
    set_textures();
    load_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    set_piece_positions();
};

void Board::set_textures() {
    textures_['p'] = sf::Texture("/home/tom/Documents/code/schach/assets/w-pawn.png");
    textures_['b'] = sf::Texture("/home/tom/Documents/code/schach/assets/w-bishop.png");
    textures_['n'] = sf::Texture("/home/tom/Documents/code/schach/assets/w-knight.png");
    textures_['r'] = sf::Texture("/home/tom/Documents/code/schach/assets/w-rook.png");
    textures_['q'] = sf::Texture("/home/tom/Documents/code/schach/assets/w-queen.png");
    textures_['k'] = sf::Texture("/home/tom/Documents/code/schach/assets/w-king.png");
    textures_['P'] = sf::Texture("/home/tom/Documents/code/schach/assets/b-pawn.png");
    textures_['B'] = sf::Texture("/home/tom/Documents/code/schach/assets/b-bishop.png");
    textures_['N'] = sf::Texture("/home/tom/Documents/code/schach/assets/b-knight.png");
    textures_['R'] = sf::Texture("/home/tom/Documents/code/schach/assets/b-rook.png");
    textures_['Q'] = sf::Texture("/home/tom/Documents/code/schach/assets/b-queen.png");
    textures_['K'] = sf::Texture("/home/tom/Documents/code/schach/assets/b-king.png");
    for (auto& [c, texture] : textures_) {
        texture.setSmooth(true);
    }
}


void Board::load_fen(std::string s) {
    unsigned short row = 0;
    unsigned short collumn = 7;
    for (char c : s) {
        if (c == ' ') {break;}
        else if (c == '/') {
            row = 0;
            collumn--;
        }
        else if (c >= '1' && c <= '8') {
            row += c - '0';
        }
        else {
            ChessCoordinates coordinates{static_cast<char>(row + 'A'), collumn};
            pieces_[coordinates] = create_piece(c, coordinates);
            row++;
        }
    }
}

void Board::set_piece_positions() {
    for (const auto& [coordinates, piece] : pieces_) {
        float x = (static_cast<int>(coordinates.row) - 'A') * square_length_;
        float y = coordinates.collumn * square_length_;
        piece->set_position(sf::Vector2f{x, y});
    }
}

std::unique_ptr<Piece> Board::create_piece(char type_char, const ChessCoordinates& coordinates) {
    colors color;
    std::isupper(type_char) ? color = colors::WHITE : color = colors::BLACK;
    switch(std::tolower(type_char)) {
        case('p'):
            return std::make_unique<Pawn>(textures_[type_char], color, coordinates, piece_scale_);
        case('b'):
            return std::make_unique<Bishop>(textures_[type_char], color, coordinates, piece_scale_);
        case('n'):
            return std::make_unique<Knight>(textures_[type_char], color, coordinates, piece_scale_);
        case('r'):
            return std::make_unique<Rook>(textures_[type_char], color, coordinates, piece_scale_);
        case('q'):
            return std::make_unique<Queen>(textures_[type_char], color, coordinates, piece_scale_);
        case('k'):
            return std::make_unique<King>(textures_[type_char], color, coordinates, piece_scale_);
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
        piece->draw(window_);
    }
}

bool Board::check_piece_clicked(sf::Vector2i& mousepos) {
    for (auto& [coordinates, piece] : pieces_) {
        if (piece->color == next_move) {continue;}
        else if (piece->check_clicked(mousepos)) {
            for (auto& [coordinates, piece2] : pieces_) {
                if (piece != piece2) {piece2->disselect();}
            }
            !piece->selected ? piece->select() : piece->disselect();
            return true;
        }
    }
    return false;
}

