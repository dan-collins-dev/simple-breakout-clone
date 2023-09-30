cmake_minimum_required(VERSION 3.25.2)

project(BOClone)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2TTF_LIBRARY})

set(SOURCES ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/Game.cpp
    ${CMAKE_SOURCE_DIR}/include/Game.h 
    ${CMAKE_SOURCE_DIR}/src/Paddle.cpp
    ${CMAKE_SOURCE_DIR}/include/Paddle.h 
    ${CMAKE_SOURCE_DIR}/src/Ball.cpp
    ${CMAKE_SOURCE_DIR}/include/Ball.h)

add_executable(BOClone ${SOURCES})

target_link_libraries(BOClone ${SDL2_LIBRARIES} SDL2_mixer SDL2_image SDL2_ttf)

install(TARGETS BOClone DESTINATION bin)