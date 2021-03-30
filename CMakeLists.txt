cmake_minimum_required(VERSION 3.17)
project(libant)

set(CMAKE_CXX_STANDARD 17)
set(BIN_OUTPUT_DIR ${PROJECT_SOURCE_DIR}/bin)

option(BUILD_TEST_CASES "building test cases" OFF)

# include search dir
include_directories(
   ${PROJECT_SOURCE_DIR}/../
)

file(GLOB_RECURSE LIBANT_SOURCE_FILES system/*.cpp)

add_library(ant ${LIBANT_SOURCE_FILES})

if (BUILD_TEST_CASES)
    add_subdirectory(test_cases)
endif()

set_target_properties(ant
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${BIN_OUTPUT_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${BIN_OUTPUT_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${BIN_OUTPUT_DIR}"
)