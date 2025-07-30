add_library(chess STATIC
            Board.cpp
            BoardMovesLogic.cpp
            BoardAILogic.cpp
            Piece.cpp
            King.cpp
            Queen.cpp
            Rook.cpp
            Bishop.cpp
            Knight.cpp
            Pawn.cpp
            helpers.cpp
            ChessCoordinates.cpp
            PossibleMoveMarker.cpp
)

add_executable(main main.cpp)

target_link_libraries(main
                        SFML::Window
                        SFML::System
                        SFML::Audio
                        SFML::Graphics

                        chess                        
)               