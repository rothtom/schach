#pragma once

#include <SFML/Graphics.hpp>

namespace chess {
    class ChessCoordinates {
        public:
            ChessCoordinates() = default;
            ChessCoordinates(const ChessCoordinates&) = default;
            ChessCoordinates(ChessCoordinates&&) = default;
            ChessCoordinates(char coll, unsigned short row);
            sf::Vector2i to_index();
            unsigned short row;
            char coll;
            bool operator==(const ChessCoordinates& other) const;
            void operator=(const ChessCoordinates& other);
            std::string to_string();
        private:
            
    };
}
