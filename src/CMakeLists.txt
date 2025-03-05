add_library(Board Board.cpp)

target_link_libraries(Board
                    SFML::Window
                    SFML::Graphics
                    SFML::Audio
                    SFML::System
)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE 
                    Board
                    SFML::Window
                    SFML::Graphics
                    SFML::Audio
                    SFML::System
)