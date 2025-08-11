add_library(chess STATIC
            Board.cpp
            BoardMovesLogic.cpp
            BoardAILogic.cpp
            Move.cpp
            NormalMove.cpp
            PromotionMove.cpp
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
            PossiblePromotionMarker.cpp
)

add_executable(main main.cpp)

# target_include_directories(chess
    # PUBLIC
    # ${PROJECT_SOURCE_DIR}/include
    #${SFML_INCLUDE_DIRS} # optional: usually not needed if using SFML:: targets
# )

target_link_libraries(main
                        SFML::Window
                        SFML::System
                        SFML::Audio
                        SFML::Graphics

                        chess                        
)               