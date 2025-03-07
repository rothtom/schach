#pragma once

#include <array>
#include <iostream>
#include <SFML/Window.hpp>

#include "Coordinates.hpp"

sf::Vector2u chess_cord_to_index(const ChessCoordinates& chess);

sf::Vector2f chess_cord_to_abs_pos(const ChessCoordinates& chess, const float& square_lenght, const sf::Vector2u& window_size);