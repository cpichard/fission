find_package(LLVM)

if( NOT LLVM_FOUND )
  message(FATAL_ERROR "LLVM package can't be found. Set CMAKE_PREFIX_PATH variable to LLVM's installation prefix.")
endif()

include_directories(../../src)
include_directories( ${LLVM_INCLUDE_DIRS} )
add_definitions( ${LLVM_DEFINITIONS} )
add_executable(llvm_draft main.cpp)
target_link_libraries(llvm_draft fission)
