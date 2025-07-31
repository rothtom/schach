#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <memory>

#include "Piece.hpp"
#include "colors.hpp"
#include "player_type.hpp"
#include "rochade_types.hpp"
#include "helpers.hpp"
#include "GameStatus.hpp"
#include "piece_name.hpp"

// using move = std::pair<chess::ChessCoordinates, chess::ChessCoordinates>;
// using moves = std::pair<chess::ChessCoordinates, std::vector<chess::ChessCoordinates>>;

namespace chess {
    class King;
    class Move;
    class Board {
        public:
            Board(sf::RenderWindow& window, std::string fen_string);
            Board(sf::RenderWindow& window);
            Board(Board& board);
            

            void draw();
            void draw_tiles();
            void draw_pieces();
            void draw_possible_move_markers();

            void resize();
            void update();

            std::vector<Move> all_possible_moves();
            std::vector<Move> pieces_moves(std::unique_ptr<Piece>& piece);
            void set_possible_moves(std::vector<Move> moves);

            bool is_attacked(const ChessCoordinates& tile, color attacking_color);
            bool is_now_in_check(const Move move);
            // std::vector<ChessCoordinates> possible_moves(const std::unique_ptr<Piece>& piece);
            // void set_possible_moves();
            void load_fen(std::string fen_string);
            std::string board_to_fen();

            unsigned short non_advancing_moves;
            int move_num;
            color current_player;
            std::vector<rochade_types> rochade_rights;
            bool enpasseaint_possible;
            std::optional<ChessCoordinates> enpasseaint_possible_at;

            std::vector<std::unique_ptr<Piece>>& get_pieces();

            Board deep_copy();

            bool is_piece_at(ChessCoordinates coords);
            chess::Piece* get_piece_at(ChessCoordinates coords);
            std::vector<std::unique_ptr<Piece>>::iterator get_piece_iterator_at(ChessCoordinates coords);
            void take_piece_at(ChessCoordinates target_cords);
            void add_piece(piece_name piece_name, color piece_color, ChessCoordinates coordinates);
            King* get_king(color kings_color) const;
            bool is_in_check();
            bool is_checkmate();
            game_status status;
            // ai logic
            float evaluate();
            chess::color get_current_player() const;
            Move best_move();
            Move best_move_white();
            Move best_move_black();
            std::map<std::string, sf::Texture> textures;

        private:
            sf::RenderWindow& window_;
            int window_width_;
            int window_height_;
            float board_width_;
            float tile_width_;
            std::vector<std::unique_ptr<Piece>> pieces_;
            sf::RectangleShape white_tile_;
            sf::RectangleShape black_tile_;
            std::optional<std::reference_wrapper<Piece>> selected_piece_;

            Board operator=(Board& other_board);
            std::unordered_map<color, player_type> colors_players_;
    };
}