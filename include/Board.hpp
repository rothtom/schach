#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <array>

#include "colors.hpp"
#include "Coordinates.hpp"
#include "helpers.hpp"
#include "Pieces.hpp"

class Board {
    public:
        Board(sf::RenderWindow& window);
        void draw();
        void set_textures();
        void load_fen(std::string s);

        

        void check_piece_clicked(sf::Vector2i& mousepos);

    private:
        sf::RenderWindow& window_;
        float square_length_;
        sf::Vector2f piece_scale_;
        sf::RectangleShape tile_;
        sf::CircleShape possible_move_marker_;

        colors next_move = WHITE;

        std::map<char, sf::Texture> textures_;
        
        std::unique_ptr<Piece> create_piece(char type_char, const ChessCoordinates& coordinates);
        std::map<ChessCoordinates, std::unique_ptr<Piece>> pieces_;

        void set_piece_positions();
        
        void draw_tiles_();
        void draw_pieces_();
      
};