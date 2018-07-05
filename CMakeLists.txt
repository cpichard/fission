cmake_minimum_required (VERSION 3.1.0 FATAL_ERROR) 
project (fission CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# CMake modules are on this directory
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)

# CPPUnit is there
FIND_PACKAGE(CPPUNIT REQUIRED)

# This project is still on development, so it needs verbose mode
set(CMAKE_VERBOSE_MAKEFILE on)

add_subdirectory(src)
add_subdirectory(drafts/llvm)
if(CPPUNIT_FOUND)
  add_subdirectory(tests/cppunit)
endif(CPPUNIT_FOUND)
