# CMakeList.txt : CMake project for graphicx, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (graphicx "graphicx.cpp" "graphicx.h" "triangle_example.h" "quad_example.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET graphicx PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(graphicx PRIVATE gx)

target_include_directories(graphicx PUBLIC
	"../gx/include"
)
