#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <map>

#include "Piece.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include "Rook.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"
#include "Pawn.hpp"
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
            void load_fen(std::string fen_string);
            std::string board_to_fen();

            unsigned short non_advancing_moves;
            int move_num;
            color next_player;
            std::vector<rochade_types> rochade_rights;
            bool enpasseaint_possible;
        private:
            sf::RenderWindow& window_;
            int window_width_;
            int window_height_;
            int board_width_;
            int tile_width_;
            std::vector<Piece> pieces_;
            sf::RectangleShape white_tile_;
            sf::RectangleShape black_tile_;
            std::map<std::string, sf::Texture> textures_;
    };
}