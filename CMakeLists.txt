cmake_minimum_required(VERSION 3.0)

project(matrix_calculator)

set(CMAKE_C_FLAGS "-O3 -Wall -Werror -Wno-missing-braces")

include_directories(include src)

set(SOURCES ${PROJECT_SOURCE_DIR}/src)
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${SOURCES}/*.cpp")

add_executable(matrix_calculator ${SOURCES}/main.cpp)
target_sources(matrix_calculator PRIVATE ${PROJECT_SOURCES})