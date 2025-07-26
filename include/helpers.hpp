#include <string>
#include <SFML/Graphics.hpp>
#include <map>

#include "ChessCoordinates.hpp"
#include "colors.hpp"


namespace chess {
    class Piece;
    sf::Texture load_texture(std::string texture_path);
    std::map<std::string, sf::Texture> load_textures();
    bool is_piece_at(const std::vector<std::unique_ptr<Piece>>& pieces, ChessCoordinates coords);
    std::unique_ptr<Piece>& get_piece_at(std::vector<std::unique_ptr<Piece>>& pieces, ChessCoordinates coords);
    std::vector<std::unique_ptr<Piece>>::const_iterator get_piece_iterator_at(std::vector<std::unique_ptr<Piece>>& pieces, ChessCoordinates coords);
    std::unique_ptr<Piece>& get_king(std::vector<std::unique_ptr<Piece>>& pieces, color kings_color);
    bool is_in_check(std::vector<std::unique_ptr<Piece>>& pieces, std::unique_ptr<Piece>& king);
}

