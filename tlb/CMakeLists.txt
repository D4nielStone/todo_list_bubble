cmake_minimum_required(VERSION 3.28)
# set the name of the project
project(TLB VERSION 1.0.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set the source of the project
add_executable(TLB
    source/tlb.cpp
    source/main.cpp
    )

include_directories(
    ${CMAKE_SOURCE_DIR}/bgui/include
    ${CMAKE_SOURCE_DIR}/libs/include
    ${CMAKE_SOURCE_DIR}/tlb/include
    )

target_include_directories(glad PUBLIC
    ${CMAKE_SOURCE_DIR}/libs/include
    ${CMAKE_SOURCE_DIR}/libs/include/glad
)

# platform-specific include directories
if(WIN32)
    message(STATUS "Configuring for Windows (WIN32)")
    set(GLFW_LIB "${CMAKE_SOURCE_DIR}/libs/lib/libglfw3.a")

    if(NOT EXISTS ${GLFW_LIB})
        message(FATAL_ERROR "GLFW static/import library not found: ${GLFW_LIB}")
    endif()

    target_include_directories(TLB PRIVATE
        ${CMAKE_SOURCE_DIR}/bgui/include
        ${CMAKE_SOURCE_DIR}/libs/include
        ${CMAKE_SOURCE_DIR}/libs/include/GLFW
        ${CMAKE_SOURCE_DIR}/libs/include/glad
    )
    # target_link_options(TLB PRIVATE "-mwindows")
    # Link by full path and add required system libs
    target_link_libraries(TLB PRIVATE
        ${GLFW_LIB}
        glad
        bgui
        opengl32
        gdi32
        user32
        kernel32
        ws2_32
        winmm
    )
else()
    message(STATUS "Configuring for Linux")
    
    target_include_directories(TLB PUBLIC
        ${CMAKE_SOURCE_DIR}/libs/include/glad
        ${CMAKE_SOURCE_DIR}/bgui/include
        ${CMAKE_SOURCE_DIR}/libs/include/
    )
    
    target_link_libraries(TLB PUBLIC
        glad
        glfw
        bgui
    )
endif()