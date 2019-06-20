link_libraries(alflibcpp)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/bin)

# Subdirectories
add_subdirectory(external/doctest)

# Add executable and libraries to link
add_executable(test
  main.cpp
  test_allocator.cpp
  test_archive.cpp
  test_array_list.cpp
  test_file.cpp
  test_image.cpp
  test_path.cpp
  test_pointer.cpp
  test_string.cpp)

target_link_libraries(test alflibcpp)
target_include_directories(test PUBLIC
  ../include
  external/doctest
  )