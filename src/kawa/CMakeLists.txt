file(GLOB PHSRC ${PROJECT_SOURCE_DIR}/src/public/*.h)
file(GLOB_RECURSE HSRC ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

add_executable(kawa ${SRC} ${PHSRC} ${HSRC})
target_link_libraries(kawa PRIVATE libkengine)
