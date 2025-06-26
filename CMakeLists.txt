# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("graphicx")

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE BOOL "Generate installation target")

# if(UNIX AND NOT APPLE)
#     # Try to find dependencies
#     find_package(PkgConfig)
#     if(PKG_CONFIG_FOUND)
#         pkg_check_modules(WAYLAND QUIET wayland-client wayland-protocols xkbcommon)
#     endif()
#     
#     find_package(X11 QUIET)
#     
#     if(NOT WAYLAND_FOUND OR NOT X11_FOUND)
#         message(WARNING "\n\nMissing Linux dependencies for GLFW and OpenGL!\n"
#             "Please install required packages for your distribution:\n"
#             "  Debian/Ubuntu/Mint:\n"
#             "    sudo apt update\n"
#             "    sudo apt install -y libwayland-dev libxkbcommon-dev xorg-dev libgl1-mesa-dev\n"
#             "  Fedora/RHEL/CentOS:\n"
#             "    sudo dnf install -y wayland-devel libxkbcommon-devel libXcursor-devel libXi-devel libXinerama-devel libXrandr-devel mesa-libGL-devel"
#             "  FreeBSD:\n"
#             "    sudo pkg install -y wayland libxkbcommon evdev-proto xorgproto mesa-libs"
#             "Or run './install_deps.sh' if available.\n")
#     endif()
# endif()

# Include sub-projects.
add_subdirectory ("dep/glfw-3.4")

add_subdirectory ("gx")
add_subdirectory ("graphicx")

