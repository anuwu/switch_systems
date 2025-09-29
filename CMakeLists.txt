# Default Project stuff
cmake_minimum_required (VERSION 3.5)
project(ss)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wformat -Wno-sometimes-uninitialized -Wno-unused-const-variable")
include_directories("${CMAKE_CURRENT_LIST_DIR}/src")

# Find openSSL
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

# Find EMP-TOOL
find_package(emp-tool)
find_path(EMP-TOOL_INCLUDE_DIR emp-tool/emp-tool.h)
include_directories(${EMP-TOOL_INCLUDE_DIR})

# Set directories
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(verify)
add_subdirectory(bench)