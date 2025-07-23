add_library(Board Board.cpp)
add_library(Piece Piece.cpp)
add_library(King King.cpp)
add_library(Queen Queen.cpp)
add_library(Rook Rook.cpp)
add_library(Bishop Bishop.cpp)
add_library(Knight Knight.cpp)
add_library(Pawn Pawn.cpp)
add_library(helpers helpers.cpp)

add_library(ChessCoordinates ChessCoordinates.cpp)

add_executable(main main.cpp)

add_library(chess STATIC
            Board
            Piece
            King
            Queen
            Rook
            Bishop
            Knight
            Pawn
            helpers
            ChessCoordinates
)

target_link_libraries(main
                        SFML::Window
                        SFML::System
                        SFML::Audio
                        SFML::Graphics

                        chess                        
)               