cmake_minimum_required(VERSION 3.28)
# set the name of the project
project(TodoListBubble)
# set the out directory
set(OUT_DIR ${CMAKE_SOURCE_DIR}/out)
# include the default library header
include_directories(
    /usr/include/GLFW
    include
    libs
    )
# set the source of the project
add_executable(TodoListBubble
    source/tlb.cpp
    source/main.cpp
    libs/glad/glad.c
    )
find_package(glfw3 REQUIRED)
target_link_libraries(TodoListBubble PRIVATE glfw)
