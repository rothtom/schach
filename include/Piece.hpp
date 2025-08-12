#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "colors.hpp"
#include "ChessCoordinates.hpp"
#include "helpers.hpp"

namespace chess {
    class Board;
    class PossibleMoveMarker;
    class PossiblePromotionMarker;
    class Move;
    class Piece {
        public:
            Piece() = delete;
            virtual ~Piece();
            Piece(const Piece& other);
            Piece(chess::color piece_color, chess::ChessCoordinates coordinates, sf::Texture& texture, sf::RenderWindow& window, Board& board);
            void setTexture(sf::Texture& texture);
            void setBoard(Board& board);
            void draw();
            void draw_possible_move_markers();
            void update();
            void select();
            void disselect();
            bool is_selected() const;
            void resize(int tile_width);
            void update_position();
            bool is_hovered(sf::Vector2i& mouse_pos);
            bool is_clicked(sf::Vector2i& mouse_pos);

            std::optional<Move*> marker_clicked(sf::Vector2i& mouse_pos);
            virtual void move(ChessCoordinates new_coordinates);

            void add_possible_move(std::unique_ptr<Move> possible_move);
            void reset_possible_moves();
            const ChessCoordinates& get_coordinates() const;
            const color& get_color() const;
            virtual std::unique_ptr<Piece> deep_copy(Board& board) = 0;
            virtual std::vector<std::unique_ptr<Move>> get_possible_moves() = 0;
        protected:
            Board* board_;
            chess::color color_;
            ChessCoordinates coordinates_;
            sf::Vector2f position_;
            sf::Texture& texture_;
            sf::Sprite sprite_;
            float sprite_scale_;
            float tile_width_;
            bool selected_;
            sf::RenderWindow& window_;
            std::vector<std::unique_ptr<Move>> possible_moves_;
            std::vector<std::unique_ptr<PossibleMoveMarker>> possible_move_markers_;
    };
} // chess
