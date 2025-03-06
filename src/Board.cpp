#include "Board.hpp"


Board::Board(sf::RenderWindow& window) : window_(window) {
    square_length_ = std::min(window_.getSize().x, window_.getSize().y) / 8;
    tile_ = sf::RectangleShape(sf::Vector2f(square_length_, square_length_));
    set_textures();
    load_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
};

void Board::set_textures() {
    sf::Vector2i piece_size(45, 45);
    std::array<char, 6> piece_letters{'k', 'q', 'b', 'n', 'r', 'p'};
    for (int i=0; i<6; i++) {
        textures_[piece_letters[i]] = sf::Texture("/home/tom/Documents/code/schach/assets/spritesheet.jpg", false, sf::IntRect(sf::Vector2i(0, 45*i), piece_size));
        textures_[toupper(piece_letters[i])] = sf::Texture("/home/tom/Documents/code/schach/assets/spritesheet.jpg", false, sf::IntRect(sf::Vector2i(45, 45*i), piece_size));
    }
}

void Board::load_fen(std::string s) {
    int row = 0;
    int collumn = 7;
    for (char c : s) {
        if (c == ' ') {break;}
        else if (c == '/') {
            row = 0;
            collumn--;
        }
        else if ((int)c <= 8) {
            row += (int)c;
        }
        else {
            ChessCoordinates coordinates{(char)row + 48, collumn};
            pieces_[coordinates] = create_piece(c, coordinates);
        }
    }
}

std::unique_ptr<Piece> Board::create_piece(char type_char, const ChessCoordinates& coordinates) {
    colors color;
    std::isupper(type_char) ? color = colors::WHITE : color = colors::BLACK;

    switch(std::tolower(type_char)) {
        case('p'):
            return std::make_unique<Pawn>(textures_[type_char], color, coordinates);
        case('b'):
            return std::make_unique<Bishop>(textures_[type_char], color, coordinates);
        case('n'):
            return std::make_unique<Knight>(textures_[type_char], color, coordinates);
        case('r'):
            return std::make_unique<Rook>(textures_[type_char], color, coordinates);
        case('q'):
            return std::make_unique<Queen>(textures_[type_char], color, coordinates);
        case('k'):
            return std::make_unique<King>(textures_[type_char], color, coordinates);
        default:
            return nullptr;
    }
}


void Board::draw() {
    window_.clear(sf::Color(0, 0, 0));
    draw_tiles_();
    window_.display();
}

void Board::draw_tiles_() {
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            tile_.setPosition(sf::Vector2f(square_length_*i, square_length_*j));
            (i + j) % 2 == 0 ? tile_.setFillColor(sf::Color(78, 120, 55)) : tile_.setFillColor(sf::Color(255, 255, 255));
            window_.draw(tile_);
        }
    }
}

