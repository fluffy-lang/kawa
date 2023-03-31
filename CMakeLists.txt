cmake_minimum_required(VERSION 3.15)

project(kawa LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)

cmake_policy(SET CMP0002 OLD)


if (NOT TARGET datatypes)
    add_subdirectory(${PROJECT_SOURCE_DIR}/extlibs/datatypes.h)
endif()

add_subdirectory(${PROJECT_SOURCE_DIR}/extlibs/DVM)
add_subdirectory(${PROJECT_SOURCE_DIR}/extlibs/Simple-Lexer)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)
