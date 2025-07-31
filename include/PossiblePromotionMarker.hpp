#pragma once

#include "PossibleMoveMarker.hpp"
#include "piece_name.hpp"
#include "colors.hpp"

namespace chess {
    class PossiblePromotionMarker : public PossibleMoveMarker {
        public:
            PossiblePromotionMarker(ChessCoordinates coordinates, color pawn_color, piece_name piece_to_promote_to, float& tile_width, sf::Texture& texture, Move& move, sf::RenderWindow& window);
            void update_position() override;
            void draw() override;
            bool is_clicked(sf::Vector2i& mouse_pos) override;
            bool is_hovered(sf::Vector2i& mouse_pos) override;
            void resize(int new_tile_width) override;
        private:
            piece_name piece_to_promote_to_;
            color pawn_color_;
            sf::Texture& texture_;
            sf::Sprite sprite_;
            float sprite_scale_;
    };
}