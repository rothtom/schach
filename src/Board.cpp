#include "Board.hpp"

#include <optional>
#include <functional>

chess::Board::Board(sf::RenderWindow& window) 
: window_(window)
{
    textures_ = load_textures();
    pieces_.reserve(32);
    white_tile_.setFillColor(sf::Color(240, 217, 181));
    black_tile_.setFillColor(sf::Color(181, 136, 99));

    load_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    resize();
}

chess::Board::Board(sf::RenderWindow& window, std::string fen_string)
: window_(window), 
window_width_(window.getSize().x), window_height_(window.getSize().y), 
board_width_(std::min(window_width_, window_height_)), tile_width_(board_width_ / 8)
{
    textures_ = load_textures();
    pieces_.reserve(32);
    white_tile_.setFillColor(sf::Color(240, 217, 181));
    black_tile_.setFillColor(sf::Color(181, 136, 99));

    load_fen(fen_string);

    resize();
}

std::vector<chess::ChessCoordinates> chess::Board::possible_moves(std::unique_ptr<Piece>& piece) {
    std::vector<ChessCoordinates> considered_tiles = piece->get_possible_moves();
}


void chess::Board::draw() {
    draw_tiles();
    draw_pieces();
}

void chess::Board::draw_tiles() {
    sf::Vector2f position;
    for (int i=0; i<8; i++) {
        for (int j=0; j<9; j++) {
            position = {tile_width_ * i, tile_width_ * j};
            if (((i + j) % 2) == 0) {
                white_tile_.setPosition(position);
                window_.draw(black_tile_);
            }
            else {
                black_tile_.setPosition(position);
                window_.draw(white_tile_);
            }
        }
    }
}

void chess::Board::draw_pieces() {
    for (std::unique_ptr<Piece>& piece : pieces_) {
        piece->draw();
    }
}

void chess::Board::resize() {
    window_width_ = window_.getSize().x;
    window_height_ = window_.getSize().y;
    board_width_ = std::min(window_width_, window_height_);
    tile_width_ = board_width_ / 8;
    black_tile_.setSize({static_cast<float>(tile_width_), static_cast<float>(tile_width_)});
    white_tile_.setSize({static_cast<float>(tile_width_), static_cast<float>(tile_width_)});
    sf::View view(sf::FloatRect({0, 0}, {static_cast<float>(window_width_), static_cast<float>(window_height_)}));
    window_.setView(view);

    for ( std::unique_ptr<Piece>& piece : pieces_) {
        piece->resize(tile_width_);
    }
}

void chess::Board::update() {
    while (const std::optional<sf::Event> event = window_.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window_.close();
        }
        else if (event->is<sf::Event::Resized>()) {
            resize();
        }
        else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            sf::Vector2i mouse_pos = mouseButtonPressed->position;
            if (selected_piece_.has_value()) {
                std::optional<ChessCoordinates> cords_to_move_to = selected_piece_->get().marker_clicked(mouse_pos);
                if (cords_to_move_to.has_value()) {
                    if (is_piece_at(pieces_, *cords_to_move_to)) {
                        pieces_.erase(get_piece_iterator_at(pieces_, *cords_to_move_to));
                    }
                    selected_piece_->get().move(*cords_to_move_to);
                    selected_piece_.reset();
                    current_player == BLACK ? current_player = WHITE : current_player = BLACK;
                    break;
                }
            }

            for (auto& piece : pieces_) {
                if (piece->is_clicked(mouse_pos) && piece->get_color() == current_player) {
                    if (piece->is_selected()) {
                        piece->disselect();
                        selected_piece_.reset();
                    }
                    else {
                        for(auto& other_pieces : pieces_) {
                            other_pieces->disselect();
                        }
                        piece->select();
                        selected_piece_ = std::reference_wrapper<Piece>(*piece);
                    }
                    break;                    
                };
            }
            
        } 
    }
    for (std::unique_ptr<Piece>& piece : pieces_) {
        piece->update();
    }
}







void chess::Board::load_fen(std::string fen_string) {
    unsigned short row = 8;
    char collumn = 'a';
    int i = 0;
    char c;
    while ((c = fen_string[i]) != ' ') {
        if (std::isdigit(c)) {
            collumn += c - '0';
        }
        else if (c == '/') {
            row--;
            collumn = 'a';
        }
        else {
            // black pieces -> lower case letters
            if (c == 'k') {
               pieces_.emplace_back(std::make_unique<King>(BLACK, ChessCoordinates({collumn, row}), textures_["b-king"], window_, pieces_));
            }
            else if (c == 'q') {
                pieces_.emplace_back(std::make_unique<Queen>(BLACK, ChessCoordinates({collumn, row}), textures_["b-queen"], window_, pieces_));
            }
            else if (c == 'r') {
                pieces_.emplace_back(std::make_unique<Rook>(BLACK, ChessCoordinates({collumn, row}), textures_["b-rook"], window_, pieces_));
            }
            else if (c == 'b') {
                pieces_.emplace_back(std::make_unique<Bishop>(BLACK, ChessCoordinates({collumn, row}), textures_["b-bishop"], window_, pieces_));
            }
            else if (c == 'n') {
                pieces_.emplace_back(std::make_unique<Knight>(BLACK, ChessCoordinates({collumn, row}), textures_["b-knight"], window_, pieces_));
            }
            else if (c == 'p') {
                pieces_.emplace_back(std::make_unique<Pawn>(BLACK, ChessCoordinates({collumn, row}), textures_["b-pawn"], window_, pieces_));
            }

            else if (c == 'K') {
               pieces_.emplace_back(std::make_unique<King>(WHITE, ChessCoordinates({collumn, row}), textures_["w-king"], window_, pieces_));
            }
            else if (c == 'Q') {
                pieces_.emplace_back(std::make_unique<Queen>(WHITE, ChessCoordinates({collumn, row}), textures_["w-queen"], window_, pieces_));
            }
            else if (c == 'R') {
                pieces_.emplace_back(std::make_unique<Rook>(WHITE, ChessCoordinates({collumn, row}), textures_["w-rook"], window_, pieces_));
            }
            else if (c == 'B') {
                pieces_.emplace_back(std::make_unique<Bishop>(WHITE, ChessCoordinates({collumn, row}), textures_["w-bishop"], window_, pieces_));
            }
            else if (c == 'N') {
                pieces_.emplace_back(std::make_unique<Knight>(WHITE, ChessCoordinates({collumn, row}), textures_["w-knight"], window_, pieces_));
            }
            else if (c == 'P') {
                pieces_.emplace_back(std::make_unique<Pawn>(WHITE, ChessCoordinates({collumn, row}), textures_["w-pawn"], window_, pieces_));
            }
            else {}

            collumn++;
        } 
        i++;
    }

    i++;

    fen_string[i] == 'w' ? current_player = WHITE : current_player = BLACK;
    i += 2;

    while ((c = fen_string[i]) != ' ') {
        if (c == 'K') {
            rochade_rights.emplace_back(chess::K);
        }
        else if (c == 'Q') {
            rochade_rights.emplace_back(chess::Q);
        }
        else if (c == 'k') {
            rochade_rights.emplace_back(chess::k);
        }
        else if (c == 'q') {
            rochade_rights.emplace_back(chess::q);
        }
        i++;
    }

    i++;

    enpasseaint_possible = (fen_string[i] != '-');
    enpasseaint_possible ? i += 3 : i += 2;
    std::cout << "Enpasseaint possible: " << enpasseaint_possible << std::endl;

    std::string non_advancing_moves_str = "";
    while ((c = fen_string[i]) != ' ') {
        non_advancing_moves_str += c;
        i++;
    }
    i++;

    std::cout << "non_advancing_moves_str: " << non_advancing_moves_str << std::endl;
    non_advancing_moves = std::stoi(non_advancing_moves_str);

    std::string move_num_str = "";
    while ((c = fen_string[i]) != '\0') {
        move_num_str += c;
        i++;
    }
    i++;
    std::cout << "move_num_str: " << move_num_str << std::endl;
    move_num = std::stoi(move_num_str);
}

