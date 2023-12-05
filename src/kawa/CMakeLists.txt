file(GLOB_RECURSE HSRC ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

include_directories(${PROJECT_SOURCE_DIR}/src/public/lang/casm) # TODO: Remove

add_executable(kawa ${SRC} ${HSRC})
target_link_libraries(kawa PRIVATE datatypes sl libcar-gen libcasm)
