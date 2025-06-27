
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set (LIB_FILES 
    "include/gx/gx.h"
    "gx.cpp"
    "glad/src/glad.c"
)

if (BUILD_SHARED_LIBS)
    message(STATUS "Building GX as a shared library")
    add_library(gx SHARED ${LIB_FILES})
else()
    message(STATUS "Building GX as a static library")
    add_library(gx STATIC ${LIB_FILES})
endif()

if(BUILD_SHARED_LIBS)
    target_compile_definitions(gx PUBLIC GX_SHARED)
else()
    target_compile_definitions(gx PUBLIC GX_STATIC)
endif()
target_compile_definitions(gx PRIVATE GX_BUILD)

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
