file(GLOB PHSRC ${PROJECT_SOURCE_DIR}/src/public/libgear/*.h)
file(GLOB_RECURSE HSRC ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

add_library(libgear ${SRC} ${HSRC} ${PHSRC})
target_link_libraries(libgear
        PUBLIC
            datatypes
            sl
            libgeff
        PRIVATE
            libcar-gen
            MINIZIP::minizip
)

target_include_directories(libgear PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/public/libgear>
        $<INSTALL_INTERFACE:include>
)

install(TARGETS libgear
        EXPORT ${CMAKE_PROJECT_NAME}Targets
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        INCLUDES DESTINATION include
)
