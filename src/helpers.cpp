#include <iostream>

#include "helpers.hpp"
#include "Piece.hpp"
#include "King.hpp"



bool chess::is_piece_at(const std::vector<std::unique_ptr<chess::Piece>>& pieces, chess::ChessCoordinates coords) {
    for (const std::unique_ptr<chess::Piece>& piece : pieces) {
        if (piece->get_coordinates() == coords) {
            return true;
        }
    }
    return false;
}

const std::unique_ptr<chess::Piece>& chess::get_piece_at(const std::vector<std::unique_ptr<chess::Piece>>& pieces, chess::ChessCoordinates coords) {
    for (const std::unique_ptr<chess::Piece>& piece : pieces) {
        if (piece->get_coordinates() == coords) {
            return piece;
        }
    }
    throw std::runtime_error("No piece found at given coordinates");
}

const std::unique_ptr<chess::Piece>& chess::get_king(const std::vector<std::unique_ptr<Piece>>& pieces, chess::color kings_color) {
    for (const std::unique_ptr<Piece>& piece : pieces) {
        if (auto king = dynamic_cast<chess::King*>(piece.get())) {
            if (king->get_color() == kings_color) {
                return piece;
            }
        }    
    }
    kings_color == WHITE ? throw std::runtime_error("no white king found") : throw std::runtime_error("no black king found");
}


bool chess::is_in_check(const std::vector<std::unique_ptr<chess::Piece>>& pieces, const std::unique_ptr<chess::Piece>& king) {
    for (const std::unique_ptr<Piece>& piece : pieces) {
        if (piece->get_color() == king->get_color()) {
            continue;
        }
        for (chess::ChessCoordinates coordinates : piece->get_possible_moves(2)) {
            if (coordinates == king->get_coordinates()) {
                return true;
            }
        }
    }
    return false;
}



std::vector<std::unique_ptr<chess::Piece>>::const_iterator chess::get_piece_iterator_at(const std::vector<std::unique_ptr<Piece>>& pieces, ChessCoordinates coords) {
    for (std::vector<std::unique_ptr<Piece>>::const_iterator it = pieces.begin(); it != pieces.end(); it++) {
        if (it->get()->get_coordinates() == coords) {
            return it;
        }
    }
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