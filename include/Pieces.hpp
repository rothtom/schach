#include <SFML/Graphics.hpp>
#include <vector>

#include "Coordinates.hpp"
#include "colors.hpp"
#include "types.hpp"
#include "helpers.hpp"
#include "PossibleMoveField.hpp"

class Piece {
    public:
        explicit Piece(sf::Texture& texture, colors color, types type, ChessCoordinates coordinates, float square_length, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker, sf::RenderWindow& window);
        virtual void possible_moves() = 0;
        void draw(sf::RenderWindow& window);
        void set_position();
        void check_clicked(sf::Vector2i& mousepos, bool& moved);
        void move(ChessCoordinates new_coordinates);

        bool selected = false;
        colors color;
        void select();
        void disselect();

    protected:
        sf::Sprite sprite_;
        sf::CircleShape possible_move_marker_;
        types type_;
        ChessCoordinates coordinates_;
        sf::Vector2f pixel_coordinates_;
        sf::Vector2f piece_scale_;
        float square_length_;
        sf::RenderWindow& window_;
        std::vector<PossibleMoveField> possible_moves_;
        
};

class Pawn : public Piece {
    public:
        explicit Pawn(sf::Texture& texture, colors color, ChessCoordinates coordinates, float square_length, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker, sf::RenderWindow& window);
        void possible_moves() override;
};

class Bishop : public Piece {
    public:
        explicit Bishop(sf::Texture& texture, colors color, ChessCoordinates coordinates, float square_length, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker, sf::RenderWindow& window);
        void possible_moves() override;
};

class Knight : public Piece {
    public:
        explicit Knight(sf::Texture& texture, colors color, ChessCoordinates coordinates, float square_length, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker, sf::RenderWindow& window);
        void possible_moves() override;
};

class Rook : public Piece {
    public:
        explicit Rook(sf::Texture& texture, colors color, ChessCoordinates coordinates, float square_length, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker, sf::RenderWindow& window);
        void possible_moves() override;
};

class Queen : public Piece {
    public:
        explicit Queen(sf::Texture& texture, colors color, ChessCoordinates coordinates, float square_length, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker, sf::RenderWindow& window);
        void possible_moves() override;
};

class King : public Piece {
    public:
        explicit King(sf::Texture& texture, colors color, ChessCoordinates coordinates, float square_length, sf::Vector2f piece_scale, sf::CircleShape& possible_move_marker, sf::RenderWindow& window);
        void possible_moves() override;
};