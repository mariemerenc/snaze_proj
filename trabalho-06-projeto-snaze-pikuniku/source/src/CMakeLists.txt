cmake_minimum_required(VERSION 3.2)
project(SnazeGame VERSION 1.0 LANGUAGES CXX)

#=== Main App ===

include_directories("src"
                    "include")

# set the compiling flags
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "-g")
set (CMAKE_CXX_FLAGS "-fsanitize=address -g")

add_executable(snaze
               level.cpp
               player.cpp
               snake.cpp
               snaze_game.cpp
               snaze.cpp)

# Define C++11 standard
target_compile_features(snaze PUBLIC cxx_std_17)

# The end