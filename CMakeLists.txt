cmake_minimum_required (VERSION 2.8)
project (fission)

# This project is still on development, so it needs verbose mode
set( CMAKE_VERBOSE_MAKEFILE on )

# CMake modules are on this directory
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)

add_subdirectory(src draft/llvm)
#add_subdirectory(drafts/llvm)
#add_subdirectory(tests)
#FIND_PACKAGE(CPPUNIT REQUIRED)

