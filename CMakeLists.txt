cmake_minimum_required(VERSION 3.15)

project(kawa LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)

if (NOT TARGET datatypes)
    add_subdirectory(${PROJECT_SOURCE_DIR}/extlibs/datatypes.h)
endif()

add_subdirectory(${PROJECT_SOURCE_DIR}/extlibs/DVM)
add_subdirectory(${PROJECT_SOURCE_DIR}/extlibs/Simple-Lexer)

set(MZ_COMPAT OFF)
set(MZ_BZIP2 OFF)
set(MZ_ZSTD OFF)
set(MZ_LIBCOMP OFF)
#set(MZ_FORCE_FETCH_LIBS ON)
set(MZ_WZAES OFF)

add_subdirectory(${PROJECT_SOURCE_DIR}/extlibs/minizip-ng)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)
