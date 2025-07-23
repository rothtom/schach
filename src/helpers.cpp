#include <iostream>

#include "helpers.hpp"


sf::Texture chess::load_texture(std::string texture_path) {
       sf::Texture texture;
    if(!texture.loadFromFile(texture_path)) {
        std::cerr << "Couldnt load texture from location: " << texture_path << std::endl;
    }
    return texture;
}