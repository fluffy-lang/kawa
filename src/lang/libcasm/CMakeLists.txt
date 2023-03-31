file(GLOB_RECURSE PHSRC ${PROJECT_SOURCE_DIR}/src/public/lang/casm/*.h)
file(GLOB_RECURSE HSRC ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

add_library(libcasm ${SRC} ${HSRC} ${PHSRC})
target_link_libraries(libcasm PRIVATE datatypes sl libcar-gen)

target_include_directories(libcasm PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/public/lang/casm/*.h>
        $<INSTALL_INTERFACE:include>
        )

install(TARGETS libcasm
        EXPORT ${CMAKE_PROJECT_NAME}Targets
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        INCLUDES DESTINATION include
        )

install(FILES ${PHSRC} DESTINATION include/libcasm)
