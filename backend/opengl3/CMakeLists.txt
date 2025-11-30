add_library(bgui_backend_opengl3 STATIC bgui_backend_opengl3.cpp opengl3_shader.cpp glad/glad.c)

target_compile_definitions(bgui_backend_opengl3 PUBLIC BGUI_USE_OPENGL)
find_package(GLEW REQUIRED)
target_link_libraries(bgui_backend_opengl3 PUBLIC 
glad)
target_include_directories(bgui_backend_opengl3
    PUBLIC ${PROJECT_SOURCE_DIR}/backend
    ${PROJECT_SOURCE_DIR}/backend/opengl3
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/core/include
)