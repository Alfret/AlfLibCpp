cmake_minimum_required(VERSION 3.10)
project(alflibcpp)

## ========================================================================== ##
## Options and Flags
## ========================================================================== ##

# Specify options
option(ALFLIBCPP_BUILD_SAMPLES "Build sample program" OFF)
option(ALFLIBCPP_BUILD_TESTS "Build tests" ON) 

# Specify flags
set(CMAKE_CXX_STANDARD 14)
if (WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else ()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
endif ()

## ========================================================================== ##
## Source files
## ========================================================================== ##

# Specify source files
set(SOURCE_FILES 
	source/alflib/allocator.cpp
	source/alflib/assert.cpp
	source/alflib/string.cpp
	source/alflib/file/file.cpp
	source/alflib/file/file_io.cpp
	source/alflib/file/path.cpp
	source/alflib/platform/os.cpp
	source/thirdparty/alf_unicode.c
	)

# Windows files
#set(SOURCE_FILES ${SOURCE_FILES}
#  source/alflib/platform/windows.cpp  
#  )

## ========================================================================== ##
## Output
## ========================================================================== ##

# fmt formatting library
add_subdirectory(external/fmt)

# Specify library to create
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# Libraries to link with
target_link_libraries(${PROJECT_NAME})

## ========================================================================== ##
## Headers
## ========================================================================== ##

# Project headers
target_include_directories(${PROJECT_NAME} PUBLIC
  include
  include/thirdparty
  external/fmt/include
  )

## ========================================================================== ##
## Preprocessor definitions
## ========================================================================== ##

# Debug macro
if (CMAKE_BUILD_TYPE MATCHES Debug)
target_compile_definitions(${PROJECT_NAME} PRIVATE ALFLIBCPP_DEBUG)
endif ()

## ========================================================================== ##
## Other
## ========================================================================== ##

# Add samples subdirectory if samples are to be built
if (ALFLIBCPP_BUILD_SAMPLES)
  add_subdirectory(samples)
endif()

# Add tests subdirectory if tests are to be built
if (ALFLIBCPP_BUILD_TESTS)
  add_subdirectory(tests)
endif ()