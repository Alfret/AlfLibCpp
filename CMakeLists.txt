cmake_minimum_required(VERSION 3.12)
project(alflibcpp)

## ========================================================================== ##
## Options and Flags
## ========================================================================== ##

# CMake options
option(ALFLIBCPP_BUILD_SAMPLES "Build sample program" OFF)
option(ALFLIBCPP_BUILD_TESTS "Build tests" OFF)

# Language standard
set(CMAKE_CXX_STANDARD 17)

# Compiler flags flags
if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else ()
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
endif ()

## ========================================================================== ##
## Source files
## ========================================================================== ##

# Specify source files
set(SOURCE_FILES
  source/alflib/core/assert.cpp
  source/alflib/core/buffer.cpp
  source/alflib/core/console.cpp
  source/alflib/core/dialog.cpp
  source/alflib/core/string.cpp
  source/alflib/debug/debugger.cpp
  source/alflib/file/archive.cpp
  source/alflib/file/file.cpp
  source/alflib/file/file_io.cpp
  source/alflib/file/path.cpp
  source/alflib/file/result.cpp
  source/alflib/graphics/color.cpp
  source/alflib/graphics/image.cpp
  source/alflib/math/matrix4f.cpp
  source/alflib/math/simd.cpp
  source/alflib/math/vector2f.cpp
  source/alflib/math/vector3f.cpp
  source/alflib/math/vector4f.cpp
  source/alflib/memory/allocator.cpp
  source/alflib/memory/memory_reader.cpp
  source/alflib/memory/memory_writer.cpp
  source/alflib/platform/os.cpp
  source/thirdparty/alf_unicode.c
  source/thirdparty/miniz/miniz.c
  source/thirdparty/microtar/microtar.c
  )

## ========================================================================== ##
## Output
## ========================================================================== ##

# Add fmt formatting library
add_subdirectory(external/fmt)

# Library to create
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# Libraries to link with
target_link_libraries(${PROJECT_NAME} PRIVATE fmt-header-only)

## ========================================================================== ##
## Headers
## ========================================================================== ##

# Project headers
target_include_directories(${PROJECT_NAME} PUBLIC
  include
  include/thirdparty
  include/thirdparty/miniz
  include/thirdparty/microtar
  external/fmt/include
  )

## ========================================================================== ##
## Linux-specifics
## ========================================================================== ##

if (UNIX AND NOT APPLE)
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
  target_include_directories(${PROJECT_NAME} PRIVATE ${GTK3_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME} PRIVATE ${GTK3_LIBRARIES})
endif ()

## ========================================================================== ##
## Preprocessor definitions
## ========================================================================== ##

# Debug macro
if (CMAKE_BUILD_TYPE MATCHES Debug)
  target_compile_definitions(${PROJECT_NAME} PRIVATE ALFLIB_DEBUG)
endif ()

## ========================================================================== ##
## Other
## ========================================================================== ##

# Add samples subdirectory
if (ALFLIBCPP_BUILD_SAMPLES)
  add_subdirectory(samples)
endif ()

# Add tests subdirectory
if (ALFLIBCPP_BUILD_TESTS)
  add_subdirectory(tests)
endif ()