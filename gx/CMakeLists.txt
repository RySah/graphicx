
add_library(gx STATIC 
    "include/gx/gx.h"
    "gx.cpp"
    "glad/src/glad.c"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET gx PROPERTY CXX_STANDARD 20)
endif()

if (WIN32) # OpenGL should come with graphics drivers
    target_link_libraries(gx PRIVATE
        opengl32
        glfw
    )
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(gx PRIVATE
        OpenGL::GL
        glfw
    )
endif()

target_include_directories(gx PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/glad/include"
    "../dep/glfw-3.4/include"
)
