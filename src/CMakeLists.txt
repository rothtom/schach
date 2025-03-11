add_library(Board Board.cpp)
add_library(Pieces Pieces.cpp)
add_library(Tile Tile.cpp)
add_library(helpers helpers.cpp)
add_library(PossibleMoveField PossibleMoveField.cpp)


add_library(Coordinates Coordinates.cpp)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE 
                    Board
                    Pieces
                    Tile
                    Coordinates
                    helpers
                    PossibleMoveField
                    SFML::Window
                    SFML::Graphics
                    SFML::Audio
                    SFML::System
)