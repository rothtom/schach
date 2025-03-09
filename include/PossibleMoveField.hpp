#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Coordinates.hpp"
#include "helpers.hpp"

class PossibleMoveField {
    public:
        PossibleMoveField(ChessCoordinates coordinates, float square_length, sf::RenderWindow& window, sf::CircleShape circle);
        void draw();
        bool check_clicked(sf::Vector2i& mousepos);
        ChessCoordinates chess_coordinates;
    private:
        float square_length_;
        
        sf::Vector2f pixel_coordinates_;
        sf::RenderWindow& window_;
        sf::CircleShape circle_;
};