#include <SFML/Graphics.hpp>

#include "Coordinates.hpp"
#include "colors.hpp"
#include "types.hpp"
#include "helpers.hpp"

class Piece {
    public:
        explicit Piece(sf::Texture& texture, colors color, types type, ChessCoordinates coordinates, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker);
        void draw(float& tile_size, sf::Sprite& sprite);
        virtual std::vector<ChessCoordinates> possible_moves() = 0;
        virtual ~Piece() = default;
        void draw(sf::RenderWindow& window);
        void set_position(sf::Vector2f coordinates);
        bool check_clicked(sf::Vector2i& mousepos);

        bool selected = false;
        colors color;
        void select();
        void disselect();

    protected:
        sf::Sprite sprite_;
        sf::CircleShape possible_move_marker_;
        types type_;
        ChessCoordinates coordinates_;
        sf::Vector2f piece_scale_;
        
};

class Pawn : public Piece {
    public:
        explicit Pawn(sf::Texture& texture, colors color, ChessCoordinates coordinates, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker);
        std::vector<ChessCoordinates> possible_moves() override;
};

class Bishop : public Piece {
    public:
        explicit Bishop(sf::Texture& texture, colors color, ChessCoordinates coordinates, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker);
        std::vector<ChessCoordinates> possible_moves() override;
};

class Knight : public Piece {
    public:
        explicit Knight(sf::Texture& texture, colors color, ChessCoordinates coordinates, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker);
        std::vector<ChessCoordinates> possible_moves() override;
};

class Rook : public Piece {
    public:
        explicit Rook(sf::Texture& texture, colors color, ChessCoordinates coordinates, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker);
        std::vector<ChessCoordinates> possible_moves() override;
};

class Queen : public Piece {
    public:
        explicit Queen(sf::Texture& texture, colors color, ChessCoordinates coordinates, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker);
        std::vector<ChessCoordinates> possible_moves() override;
};

class King : public Piece {
    public:
        explicit King(sf::Texture& texture, colors color, ChessCoordinates coordinates, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker);
        std::vector<ChessCoordinates> possible_moves() override;
};