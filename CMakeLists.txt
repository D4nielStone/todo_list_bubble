cmake_minimum_required(VERSION 3.28)
# set the name of the project
project(TodoListBubble VERSION 1.0.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set the out directory
set(OUT_DIR ${CMAKE_SOURCE_DIR}/build)

# set the source of the project
add_executable(TodoListBubble
    source/tlb.cpp
    source/main.cpp
    )

# glad library
add_library(glad STATIC
    libs/include/glad/glad.c
)

target_include_directories(glad PUBLIC
    ${CMAKE_SOURCE_DIR}/libs/include
)

# platform-specific include directories
if(WIN32)
    message(STATUS "Configuring for Windows (WIN32)")
    message(STATUS "GLFW library path: ${CMAKE_SOURCE_DIR}/libs/lib/libglfw3.a")
    
    # GLFW import target
    add_library(glfw STATIC IMPORTED)

    set_target_properties(glfw PROPERTIES
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libs/lib/libglfw3.a
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/libs/include
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/libs/include/GLFW
    )

    include_directories(
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/libs/include/GLFW
        ${CMAKE_SOURCE_DIR}/libs/include/glad
        ${CMAKE_SOURCE_DIR}/libs/include/
        ${OPENGL_INCLUDE_DIR}
    )
    
    target_include_directories(TodoListBubble PUBLIC
        ${CMAKE_SOURCE_DIR}/libs/include/GLFW
        ${CMAKE_SOURCE_DIR}/libs/include/glad
        ${CMAKE_SOURCE_DIR}/libs/include/
        ${OPENGL_INCLUDE_DIR}
    )
    
    target_link_libraries(TodoListBubble PUBLIC
        glfw
        glad
        opengl32
        gdi32
        user32
    )
else()
    message(STATUS "Configuring for Linux")
    # default includes for unix-like systems
    include_directories(
        libs/include
        include
    )
    
    target_include_directories(TodoListBubble PUBLIC
        ${CMAKE_SOURCE_DIR}/libs/include/glad
        ${CMAKE_SOURCE_DIR}/libs/include/
    )
    
    target_link_libraries(TodoListBubble PUBLIC
        glad
        glfw
    )
endif()