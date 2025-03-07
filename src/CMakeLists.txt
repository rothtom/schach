add_library(Board Board.cpp)
add_library(Pieces Pieces.cpp)
add_library(helpers helpers.cpp)

add_library(Coordinates Coordinates.cpp)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE 
                    Board
                    Pieces
                    Coordinates
                    helpers
                    SFML::Window
                    SFML::Graphics
                    SFML::Audio
                    SFML::System
)