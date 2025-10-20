cmake_minimum_required(VERSION 3.31)
project(clion_Test)

set(CMAKE_CXX_STANDARD 23)

add_executable(clion_Test src/main.cpp
        src/player.cpp
        Headers/player.hpp
        src/bullet.cpp
        Headers/bullet.hpp
        Headers/enemy.hpp
        src/enemy.cpp)

include_directories(./Headers)
find_package(SFML COMPONENTS Network Graphics Window Audio System CONFIG REQUIRED)
target_link_libraries(clion_Test PRIVATE SFML::Network SFML::Graphics SFML::Window SFML::Audio SFML::System)
