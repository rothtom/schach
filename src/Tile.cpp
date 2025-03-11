#include "Tile.hpp"


Tile::Tile(sf::RenderWindow& window, sf::RectangleShape rect) : window_(window), rect_(rect) {};


void Tile::draw() {
    window_.draw(rect_);
    piece->draw();
}