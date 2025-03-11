#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <array>

#include "colors.hpp"
#include "Coordinates.hpp"
#include "helpers.hpp"
#include "Pieces.hpp"
#include "Tile.hpp"

class Board {
    public:
        Board(sf::RenderWindow& window);
        void draw();
        void set_textures();
        void load_fen(std::string s);
        void check_piece_selected(sf::Vector2i& mousepos);

        const std::map<ChessCoordinates, std::shared_ptr<Tile>>& pieces() const {return tiles_;}

    private:
        sf::RenderWindow& window_;
        float square_length_;
        sf::Vector2f piece_scale_;
        sf::RectangleShape tile_;
        sf::CircleShape possible_move_marker_;

        colors next_move = WHITE;
        std::shared_ptr<Piece> selected_piece_ = nullptr;

        std::map<char, sf::Texture> textures_;
        
        std::shared_ptr<Piece> create_piece(char type_char, const ChessCoordinates& coordinates);
        std::map<ChessCoordinates, std::shared_ptr<Tile>> tiles_;

        void set_piece_positions();
        
        void draw_tiles_();
        void draw_pieces_();
      
};