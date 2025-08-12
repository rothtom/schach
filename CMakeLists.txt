cmake_minimum_required(VERSION 3.31.6)
project(project_name)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")

execute_process(
    COMMAND xcrun --show-sdk-path
    OUTPUT_VARIABLE SDK_PATH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
message(STATUS "SDK path: ${SDK_PATH}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isysroot ${SDK_PATH} -Wall -Wextra")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -isysroot ${SDK_PATH}")


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)



include_directories(${PROJECT_SOURCE_DIR}/include)
# for mac
set(SFML_INCLUDE_DIRS /opt/homebrew/include/)
include_directories(SYSTEM ${SFML_INCLUDE_DIRS})
include_directories("/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/v1")



# import lical lobraries here
# find_package({name} REQUIRED? COMPONETS {components})
find_package(SFML REQUIRED COMPONENTS Window Graphics Audio System)



add_subdirectory(src)
