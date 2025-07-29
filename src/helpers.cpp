#include <iostream>

#include "helpers.hpp"


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