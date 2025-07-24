#pragma once

#include <SFML/Graphics.hpp>

namespace chess {
    class ChessCoordinates {
        public:
            ChessCoordinates();
            ChessCoordinates(char coll, unsigned short row);
            sf::Vector2i to_index();
            unsigned short row;
            char coll;
            bool operator==(const ChessCoordinates& other) const;
        private:
            
    };
}
