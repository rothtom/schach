#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <map>
#include <memory>

#include "Piece.hpp"
#include "colors.hpp"
#include "rochade_types.hpp"
#include "helpers.hpp"

namespace chess {
    class Board {
        public:
            Board(sf::RenderWindow& window, std::string fen_string);
            Board(sf::RenderWindow& window);
            

            void draw();
            void draw_tiles();
            void draw_pieces();

            void resize();
            void update();
            std::map<std::unique_ptr<Piece>&, std::vector<ChessCoordinates>> all_possible_moves(color current_players_color);
            std::vector<ChessCoordinates> possible_moves(std::unique_ptr<Piece>& piece);
            void load_fen(std::string fen_string);
            std::string board_to_fen();

            unsigned short non_advancing_moves;
            int move_num;
            color current_player;
            std::vector<rochade_types> rochade_rights;
            bool enpasseaint_possible;

            const std::vector<std::unique_ptr<Piece>>& get_pieces();
        private:
            sf::RenderWindow& window_;
            int window_width_;
            int window_height_;
            float board_width_;
            float tile_width_;
            std::vector<std::unique_ptr<Piece>> pieces_;
            sf::RectangleShape white_tile_;
            sf::RectangleShape black_tile_;
            std::map<std::string, sf::Texture> textures_;
            std::optional<std::reference_wrapper<Piece>> selected_piece_;

    };
}