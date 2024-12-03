cmake_minimum_required(VERSION 3.28)
project(chess_engine)

set(CMAKE_CXX_STANDARD 20)

add_executable(chess_engine main.cpp)


set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/dev/DEVEL/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/dev/DEVEL/SFML/include/SFML)
target_link_libraries(chess_engine sfml-window sfml-graphics sfml-audio)