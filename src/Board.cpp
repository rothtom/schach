#include "Board.hpp"

chess::Board::Board(sf::RenderWindow& window) 
: window_(window)
{
    textures_ = load_textures();
    pieces_.reserve(32);
    white_tile_.setFillColor(sf::Color(240, 217, 181));
    black_tile_.setFillColor(sf::Color(181, 136, 99));

    load_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    resize();

    /* for (chess::Piece piece : pieces_) {
        piece.update();
    } */
}

chess::Board::Board(sf::RenderWindow& window, std::string fen_string)
: window_(window), 
window_width_(window.getSize().x), window_height_(window.getSize().y), 
board_width_(std::min(window_width_, window_height_)), tile_width_(board_width_ / 8)
{
    white_tile_.setFillColor(sf::Color(240, 217, 181));
    black_tile_.setFillColor(sf::Color(181, 136, 99));

    load_fen(fen_string);
}

void chess::Board::load_fen(std::string fen_string) {
    unsigned short row = 8;
    char collumn = 'a';
    int i = 0;
    char c;
    while ((c = fen_string[i]) != ' ') {
        if (std::isdigit(c)) {
            std::cout << "Collumn: " << collumn << std::endl;
        }
        else if (c == '/') {
            row--;
            collumn = 'a';
        }
        else {
            std::cout << "Adding Piece" << std::endl;
            // black pieces -> lower case letters
            if (c == 'k') {
               pieces_.emplace_back(std::make_unique<King>(BLACK, {collumn, row}, textures_["b-king"], window_));
            }
            else if (c == 'q') {
                pieces_.emplace_back(std::make_unique<Queen>(BLACK, {collumn, row}, textures_["b-queen"], window_));
            }
            else if (c == 'r') {
                pieces_.emplace_back(std::make_unique<Rook>(BLACK, {collumn, row}, textures_["b-rook"], window_));
            }
            else if (c == 'b') {
                pieces_.emplace_back(std::make_unique<Bishop>(BLACK, {collumn, row}, textures_["b-bishop"], window_));
            }
            else if (c == 'n') {
                pieces_.emplace_back(std::make_unique<Knight>(BLACK, {collumn, row}, textures_["b-knight"], window_));
            }
            else if (c == 'p') {
                pieces_.emplace_back(std::make_unique<Paen>(BLACK, {collumn, row}, textures_["b-pawn"], window_));
            }

            else if (c == 'k') {
               pieces_.emplace_back(std::make_unique<King>(WHITE, {collumn, row}, textures_["w-king"], window_));
            }
            else if (c == 'q') {
                pieces_.emplace_back(std::make_unique<Queen>(WHITE, {collumn, row}, textures_["w-queen"], window_));
            }
            else if (c == 'r') {
                pieces_.emplace_back(std::make_unique<Rook>(WHITE, {collumn, row}, textures_["w-rook"], window_));
            }
            else if (c == 'b') {
                pieces_.emplace_back(std::make_unique<Bishop>(WHITE, {collumn, row}, textures_["w-bishop"], window_));
            }
            else if (c == 'n') {
                pieces_.emplace_back(std::make_unique<Knight>(WHITE, {collumn, row}, textures_["w-knight"], window_));
            }
            else if (c == 'p') {
                pieces_.emplace_back(std::make_unique<Pawn>(WHITE, {collumn, row}, textures_["w-pawn"], window_));
            }
            else {
                std::cout << c << std::endl;
            }
        } 
        i++;
    }

    fen_string[i] == 'w' ? next_player = WHITE : next_player = BLACK;
    i++;

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

    return;

    enpasseaint_possible = fen_string[i] != '-';
    enpasseaint_possible ? i += 2 : i++;

    std::cout << i << std::endl;

    std::string non_advancing_moves_str = "";
    while (char c = fen_string[i] != ' ') {
        non_advancing_moves_str += c;
        i++;
    }
    std::cout << "non_advancing_moves_str: " << non_advancing_moves_str << std::endl;

    non_advancing_moves = std::stoi(non_advancing_moves_str);

    std::string move_num_str = "";
    while ((c = fen_string[i]) != ' ') {
        move_num_str += c;
        i++;
    }
    move_num = std::stoi(move_num_str);
}

void chess::Board::draw() {
    draw_tiles();
    draw_pieces();
}

void chess::Board::draw_tiles() {
    sf::Vector2f position;
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            position = {static_cast<float>(tile_width_ * i), static_cast<float>(tile_width_ * j)};
            if (((i + j) % 2) == 0) {
                black_tile_.setPosition(position);
                window_.draw(black_tile_);
            }
            else {
                white_tile_.setPosition(position);
                window_.draw(white_tile_);
            }
        }
    }
}

void chess::Board::draw_pieces() {
    /* for (Piece piece : pieces_) {
        piece->draw();
    } */
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

    /* for (chess::Piece piece : pieces_) {
        piece.resize(tile_width_);
    } */
}


