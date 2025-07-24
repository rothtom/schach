#include <iostream>

#include "helpers.hpp"
#include "Piece.hpp"



bool chess::is_piece_at(const std::vector<std::unique_ptr<chess::Piece>>& pieces, chess::ChessCoordinates coords) {
    for (const std::unique_ptr<chess::Piece>& piece : pieces) {
        if (piece->get_coordinates() == coords) {
            return true;
        }
    }
    return false;
}

std::unique_ptr<chess::Piece>& chess::get_piece_at(std::vector<std::unique_ptr<chess::Piece>>& pieces, chess::ChessCoordinates coords) {
    for (std::unique_ptr<chess::Piece>& piece : pieces) {
        if (piece->get_coordinates() == coords) {
            return piece;
        }
    }
    throw std::runtime_error("No piece found at given coordinates");
}


sf::Texture chess::load_texture(std::string texture_path) {
       sf::Texture texture;
    if(!texture.loadFromFile(texture_path)) {
        std::cerr << "Couldnt load texture from location: " << texture_path << std::endl;
    }
    return texture;
}

std::map<std::string, sf::Texture> chess::load_textures() {
    std::map<std::string, sf::Texture> texture_map;
    std::array<std::string, 12> texture_names = {
        "w-king",
        "w-queen",
        "w-rook",
        "w-bishop",
        "w-knight",
        "w-pawn",
        "b-king",
        "b-queen",
        "b-rook",
        "b-bishop",
        "b-knight",
        "b-pawn",
    };
    for (std::string name : texture_names) {
        texture_map[name] = load_texture("../assets/" + name + ".png");
    }
    return texture_map;
}