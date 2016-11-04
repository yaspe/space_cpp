cmake_minimum_required(VERSION 3.0)

set( project "SpaceGame")
project( ${project} )

add_definitions(-std=c++11)

find_package(SDL2 REQUIRED)

add_subdirectory(bin)
add_subdirectory(engine)
add_subdirectory(render)
add_subdirectory(controller)
add_subdirectory(resources)
