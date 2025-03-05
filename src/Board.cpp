#include "Board.hpp"


Board::Board(sf::RenderWindow& window) : window_(window) {
    square_length_ = std::min(window_.getSize().x, window_.getSize().y) / 8;
    tile_ = sf::RectangleShape(sf::Vector2f(square_length_, square_length_));
};

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

