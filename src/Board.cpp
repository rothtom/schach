#include "Board.hpp"

#include "Pawn.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Rook.hpp"
#include "Queen.hpp"
#include "King.hpp"

#include "Move.hpp"
#include "PromotionMove.hpp"

#include <optional>
#include <functional>
#include <thread>
#include <chrono>

chess::Board::Board(sf::RenderWindow& window) 
: window_(window),
window_width_(window_.getSize().x), window_height_(window_.getSize().y), 
board_width_(std::min(window_width_, window_height_)), tile_width_(board_width_ / 8),
status(ON_GOING)
{
    textures = load_textures();
    pieces_.reserve(32);
    white_tile_.setFillColor(sf::Color(240, 217, 181));
    black_tile_.setFillColor(sf::Color(181, 136, 99));

    load_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    resize();
    all_possible_moves();

    colors_players_[WHITE] = HUMAN;
    colors_players_[BLACK] = HUMAN;
}

chess::Board::Board(sf::RenderWindow& window, std::string fen_string)
: window_(window), 
window_width_(window_.getSize().x), window_height_(window_.getSize().y), 
board_width_(std::min(window_width_, window_height_)), tile_width_(board_width_ / 8),
status(ON_GOING)

{
    textures = load_textures();
    pieces_.reserve(32);
    white_tile_.setFillColor(sf::Color(240, 217, 181));
    black_tile_.setFillColor(sf::Color(181, 136, 99));

    load_fen(fen_string);
    resize();
    all_possible_moves();

    colors_players_[WHITE] = HUMAN;
    colors_players_[BLACK] = AI;
}

chess::Board::Board(chess::Board& board)
:
non_advancing_moves(board.non_advancing_moves),
move_num(board.move_num),
current_player(board.current_player),
rochade_rights(board.rochade_rights),
enpasseaint_possible(board.enpasseaint_possible),
enpasseaint_possible_at(board.enpasseaint_possible_at),
window_(board.window_), 
window_width_(window_.getSize().x), window_height_(window_.getSize().y), 
board_width_(std::min(window_width_, window_height_)), tile_width_(board_width_ / 8),
white_tile_(board.white_tile_), black_tile_(board.black_tile_),
textures(board.textures)

{
    pieces_.reserve(board.get_pieces().size());
    for (const std::unique_ptr<Piece>& piece : board.get_pieces()) {
        pieces_.emplace_back(piece->deep_copy(*this));
    }
}

chess::Board chess::Board::deep_copy() {
    return Board(*this);
}



void chess::Board::draw() {
    draw_tiles();
    draw_pieces();
    draw_possible_move_markers();
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

void chess::Board::draw_possible_move_markers() {
    for (std::unique_ptr<Piece>& piece : pieces_) {
        piece->draw_possible_move_markers();
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
        else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>();
                mouseButtonPressed && colors_players_[current_player] == HUMAN) {
            
            sf::Vector2i mouse_pos = mouseButtonPressed->position;
            if (selected_piece_.has_value()) {
                std::optional<Move*> move = selected_piece_->get().marker_clicked(mouse_pos);
                if (move.has_value()) {
                    move.value()->set_board(*this);
                    move.value()->make_move();
                    selected_piece_.reset();
                    break;
                }
            }

            for (auto& piece : pieces_) {
                if (status != ON_GOING) {
                    break;
                }
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
               pieces_.emplace_back(std::make_unique<King>(BLACK, ChessCoordinates({collumn, row}), textures["b-king"], window_, *this));
            }
            else if (c == 'q') {
                pieces_.emplace_back(std::make_unique<Queen>(BLACK, ChessCoordinates({collumn, row}), textures["b-queen"], window_, *this));
            }
            else if (c == 'r') {
                pieces_.emplace_back(std::make_unique<Rook>(BLACK, ChessCoordinates({collumn, row}), textures["b-rook"], window_, *this));
            }
            else if (c == 'b') {
                pieces_.emplace_back(std::make_unique<Bishop>(BLACK, ChessCoordinates({collumn, row}), textures["b-bishop"], window_, *this));
            }
            else if (c == 'n') {
                pieces_.emplace_back(std::make_unique<Knight>(BLACK, ChessCoordinates({collumn, row}), textures["b-knight"], window_, *this));
            }
            else if (c == 'p') {
                pieces_.emplace_back(std::make_unique<Pawn>(BLACK, ChessCoordinates({collumn, row}), textures["b-pawn"], window_, *this));
            }

            else if (c == 'K') {
               pieces_.emplace_back(std::make_unique<King>(WHITE, ChessCoordinates({collumn, row}), textures["w-king"], window_, *this));
            }
            else if (c == 'Q') {
                pieces_.emplace_back(std::make_unique<Queen>(WHITE, ChessCoordinates({collumn, row}), textures["w-queen"], window_, *this));
            }
            else if (c == 'R') {
                pieces_.emplace_back(std::make_unique<Rook>(WHITE, ChessCoordinates({collumn, row}), textures["w-rook"], window_, *this));
            }
            else if (c == 'B') {
                pieces_.emplace_back(std::make_unique<Bishop>(WHITE, ChessCoordinates({collumn, row}), textures["w-bishop"], window_, *this));
            }
            else if (c == 'N') {
                pieces_.emplace_back(std::make_unique<Knight>(WHITE, ChessCoordinates({collumn, row}), textures["w-knight"], window_, *this));
            }
            else if (c == 'P') {
                pieces_.emplace_back(std::make_unique<Pawn>(WHITE, ChessCoordinates({collumn, row}), textures["w-pawn"], window_, *this));
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

std::vector<std::unique_ptr<chess::Piece>>& chess::Board::get_pieces() {
    return pieces_;
}

chess::Board chess::Board::operator=(chess::Board& other_board) {
    return other_board.deep_copy();
}

bool chess::Board::is_piece_at(chess::ChessCoordinates coords) {
    for (const std::unique_ptr<chess::Piece>& piece : pieces_) {
        if (piece->get_coordinates() == coords) {
            return true;
        }
    }
    return false;
}

chess::Piece* chess::Board::get_piece_at(chess::ChessCoordinates coords) {
    for (std::unique_ptr<chess::Piece>& piece : pieces_) {
        if (piece->get_coordinates() == coords) {
            return piece.get();
        }
    }
    throw std::runtime_error("No piece found at given coordinates");
}



std::vector<std::unique_ptr<chess::Piece>>::iterator chess::Board::get_piece_iterator_at(ChessCoordinates coords) {
    for (std::vector<std::unique_ptr<Piece>>::iterator it = pieces_.begin(); it != pieces_.end(); it++) {
        if (it->get()->get_coordinates() == coords) {
            return it;
        }
    }
    throw std::runtime_error("could find piece iterator");
}

chess::color chess::Board::get_current_player() const {
    return current_player;
}

void chess::Board::add_piece(piece_name piece_name, color piece_color, ChessCoordinates coordinates) {
    std::unique_ptr<Piece> new_piece;
    if (piece_name == QUEEN) {
        if (piece_color == WHITE) {
            new_piece = std::make_unique<Queen>(WHITE, coordinates, textures["w-queen"], window_, *this);
        }
        else {
            new_piece = std::make_unique<Queen>(BLACK, coordinates, textures["b-queen"], window_, *this);
        }
    }
    else if (piece_name == ROOK) {
        if (piece_color == WHITE) {
            new_piece = std::make_unique<Rook>(WHITE, coordinates, textures["w-rook"], window_, *this);
        }
        else {
            new_piece = std::make_unique<Rook>(BLACK, coordinates, textures["b-rook"], window_, *this);
        }
    }
    else if (piece_name == BISHOP) {
        if (piece_color == WHITE) {
            new_piece = std::make_unique<Bishop>(WHITE, coordinates, textures["w-bishop"], window_, *this);
        }
        else {
            new_piece = std::make_unique<Bishop>(BLACK, coordinates, textures["b-bishop"], window_, *this);
        }
    }
    else if (piece_name == KNIGHT) {
        if (piece_color == WHITE) {
            new_piece = std::make_unique<King>(WHITE, coordinates, textures["w-knight"], window_, *this);
        }
        else {
            new_piece = std::make_unique<Knight>(BLACK, coordinates, textures["b-knight"], window_, *this);
        }
    }
    new_piece->update_position();
    new_piece->resize(tile_width_);
    new_piece->draw();
    pieces_.emplace_back(std::move(new_piece));
}