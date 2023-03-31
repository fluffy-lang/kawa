file(GLOB PHSRC ${PROJECT_SOURCE_DIR}/src/public/*.h)
file(GLOB_RECURSE HSRC ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

add_library(libgear ${SRC} ${PHSRC} ${HSRC})
target_link_libraries(libgear PUBLIC sl)
