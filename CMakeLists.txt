cmake_minimum_required(VERSION 3.27)
project(exo2)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(${Qt5Widgets_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)

add_executable(exo2 main.cpp
        mini.cpp
        mini.h)

target_link_libraries(mini Qt5::Widgets)