#include <SFML/Graphics.hpp>

#include <Coordinates.hpp>
#include <colors.hpp>
#include <types.hpp>

class Piece {
    public:
        explicit Piece(sf::Texture& texture, colors color, types type, ChessCoordinates coordinates, sf::Vector2f piece_scale);
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
        
        types type_;
        ChessCoordinates coordinates_;
        
};

class Pawn : public Piece {
    public:
        explicit Pawn(sf::Texture& texture, colors color, ChessCoordinates coordinates, sf::Vector2f piece_scale);
        std::vector<ChessCoordinates> possible_moves() override;
};

class Bishop : public Piece {
    public:
        explicit Bishop(sf::Texture& texture, colors color, ChessCoordinates coordinates, sf::Vector2f piece_scale);
        std::vector<ChessCoordinates> possible_moves() override;
};

class Knight : public Piece {
    public:
        explicit Knight(sf::Texture& texture, colors color, ChessCoordinates coordinates, sf::Vector2f piece_scale);
        std::vector<ChessCoordinates> possible_moves() override;
};

class Rook : public Piece {
    public:
        explicit Rook(sf::Texture& texture, colors color, ChessCoordinates coordinates, sf::Vector2f piece_scale);
        std::vector<ChessCoordinates> possible_moves() override;
};

class Queen : public Piece {
    public:
        explicit Queen(sf::Texture& texture, colors color, ChessCoordinates coordinates, sf::Vector2f piece_scale);
        std::vector<ChessCoordinates> possible_moves() override;
};

class King : public Piece {
    public:
        explicit King(sf::Texture& texture, colors color, ChessCoordinates coordinates, sf::Vector2f piece_scale);
        std::vector<ChessCoordinates> possible_moves() override;
};