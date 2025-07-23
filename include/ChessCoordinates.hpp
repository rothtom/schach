#pragma once

#include <SFML/Graphics.hpp>

namespace chess {
    class ChessCoordinates {
        public:
            ChessCoordinates(char coll, unsigned short row);
            sf::Vector2f to_index();
        private:
            unsigned short row;
            char coll;
            
    };
}
