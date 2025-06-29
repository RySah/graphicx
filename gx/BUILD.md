# Build GX yourself

This libary is built using [CMAKE](https://cmake.org/).
To aquire the libary and all of its dependencies the whole project is built. 
<br>

## Windows
1. Create CMAKE configuration
```batch
cmake -B [OUTPUT-DIR]
      -DCMAKE_CXX_COMPILER=[CPP-COMPILER]
      -DCMAKE_C_COMPILER=[C-COMPILER]
      -DCMAKE_BUILD_TYPE=[BUILD-TYPE(Release/Debug)]
      -DBUILD_SHARED_LIBS=[BUILD-SHARED-LIB(ON/OFF)]
      -S [SOURCE-DIR]
```
In our [workflow](../.github/workflows/cmake-multi-platform.yml), what typically works is:
- OUTPUT-DIR = build (This can be any name)
- CPP-COMPILER = cl (This might work with other compilers)
- C-COMPILER = cl (This might work with other compilers)
- BUILD-TYPE = Release (For fastest and most optimized version of the libary)
- BUILD-SHARED-LIB = OFF (If ON, all libaries will be built as shared libaries otherwise static libaries)
- SOURCE-DIR = . (Should the be project directory "graphicx")

2. Build
```batch
cmake --build [OUTPUT-DIR] 
      --config [BUILD-TYPE(Release/Debug)]
```
Both OUTPUT-DIR and BUILD-TYPE should be the same values used during the configuration step.

3. Find

if BUILD-SHARED-LIB is ON:
```
GX = [OUTPUT-DIR]/gx/[BUILD-TYPE]/gx.dll
GLFW = [OUTPUT-DIR]/dep/glfw-3.4/src/[BUILD-TYPE]/glfw3.dll
```
otherwise:
```
GX = [OUTPUT-DIR]/gx/[BUILD-TYPE]/gx.lib
```

## Linux/Unix
1. Make pre-CMAKE setup script executable
```bash
chmod +x [GRAPHICX-DIR]/install_dep_unix.sh
```

2. Run pre-CMake setup
```bash
[GRAPHICX-DIR]/install_dep_unix.sh
```

3. Create CMAKE configuration
```batch
cmake -B [OUTPUT-DIR]
      -DCMAKE_CXX_COMPILER=[CPP-COMPILER]
      -DCMAKE_C_COMPILER=[C-COMPILER]
      -DCMAKE_BUILD_TYPE=[BUILD-TYPE(Release/Debug)]
      -DBUILD_SHARED_LIBS=[BUILD-SHARED-LIB(ON/OFF)]
      -S [SOURCE-DIR]
```
In our [workflow](../.github/workflows/cmake-multi-platform.yml), what typically works is:
- OUTPUT-DIR = build (This can be any name)
- CPP-COMPILER = cl (This might work with other compilers)
- C-COMPILER = cl (This might work with other compilers)
- BUILD-TYPE = Release (For fastest and most optimized version of the libary)
- BUILD-SHARED-LIB = OFF (If ON, all libaries will be built as shared libaries otherwise static libaries)
- SOURCE-DIR = . (Should the be project directory "graphicx")

4. Build
```batch
cmake --build [OUTPUT-DIR] 
      --config [BUILD-TYPE(Release/Debug)]
```
Both OUTPUT-DIR and BUILD-TYPE should be the same values used during the configuration step.

5. Find

if BUILD-SHARED-LIB is ON:
```
GX = [OUTPUT-DIR]/gx/libgx.so
GLFW = [OUTPUT-DIR]/dep/glfw-3.4/src/libglfw.so
```
otherwise:
```
GX = [OUTPUT-DIR]/gx/libgx.a
```

<br>

Back to [README.md](../README.md)