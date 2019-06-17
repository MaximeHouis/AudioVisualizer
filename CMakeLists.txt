cmake_minimum_required(VERSION 3.14)
project(AudioVisualizer)

set(CMAKE_CXX_STANDARD 17)

if (UNIX)
    add_compile_options(-Wall -Wextra -Weffc++)

    if (CMAKE_BUILD_TYPE MATCHES Debug)
        add_definitions(-DDEBUG=1)
    elseif (CMAKE_BUILD_TYPE MATCHES Release)
        add_definitions(-DRELEASE=1)
    endif ()
endif ()

add_library(
    audio-visualizer
    Lib/AudioVisualizer.cpp
    Lib/AudioVisualizer.hpp
)

add_executable(
    example
    Example/src/Main.cpp
    Example/src/Application.cpp
    Example/include/Application.hpp
)

target_link_libraries(example audio-visualizer sfml-audio sfml-system sfml-window sfml-graphics)
target_include_directories(example PUBLIC Lib Example/include)
