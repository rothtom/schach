cmake_minimum_required(VERSION 3.31.6)
project(project_name)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR}/include)

# import lical lobraries here
# find_package({name} REQUIRED? COMPONETS {components})

add_subdirectory(src)
