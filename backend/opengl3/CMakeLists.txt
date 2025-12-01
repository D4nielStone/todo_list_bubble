# GLAD
add_library(glad STATIC glad/glad.c)
target_include_directories(glad PUBLIC ${PROJECT_SOURCE_DIR}/backend/opengl3)
target_link_libraries(glad PUBLIC ${CMAKE_DL_LIBS})

# BGUI OpenGL backend
add_library(bgui_backend_opengl3 STATIC
    bgui_backend_opengl3.cpp
    opengl3_shader.cpp
)

target_compile_definitions(bgui_backend_opengl3 PUBLIC BGUI_USE_OPENGL)

target_link_libraries(bgui_backend_opengl3
    PUBLIC glad
)

target_include_directories(bgui_backend_opengl3
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/backend
        ${PROJECT_SOURCE_DIR}/backend/opengl3
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/core/include
)