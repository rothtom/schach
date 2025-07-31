#pragma once

#include "PossibleMoveMarker.hpp"
#include "piece_name.hpp"
#include "colors.hpp"

namespace chess {
    class PossiblePromotionMarker : public PossibleMoveMarker {
        public:
            PossiblePromotionMarker(ChessCoordinates coordinates, color pawn_color, piece_name piece_to_promote_to, float& tile_width, sf::Texture& texture, sf::RenderWindow& window);
            void update_position() override;
            void draw() override;
            std::optional<chess::piece_name> is_clicked(sf::Vector2i& mouse_pos);
            bool is_hovered(sf::Vector2i& mouse_pos) override;
            void resize(float new_tile_width);
        private:
            piece_name piece_to_promote_to_;
            color pawn_color_;
            sf::Texture& texture_;
            sf::Sprite sprite_;
            float sprite_scale_;
    };
}