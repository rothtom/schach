#include <string>
#include <SFML/Graphics.hpp>
#include <map>

namespace chess {
    sf::Texture load_texture(std::string texture_path);
    std::map<std::string, sf::Texture> load_textures();
}

