#include <string>
#include <SFML/Graphics.hpp>
#include <map>

#include "ChessCoordinates.hpp"
#include "colors.hpp"


namespace chess {
    class Piece;
    sf::Texture load_texture(std::string texture_path);
    std::map<std::string, sf::Texture> load_textures();

}

