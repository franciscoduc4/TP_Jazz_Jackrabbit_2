file(GLOB_RECURSE COMMON_SOURCES
    ${PROJECT_SOURCE_DIR}/src/Common/*.cpp
    ${PROJECT_SOURCE_DIR}/src/Common/*.h
)

add_library(common ${COMMON_SOURCES})

target_link_libraries(common yaml-cpp fmt::fmt -pthread)
target_include_directories(common PUBLIC ${PROJECT_SOURCE_DIR}/src/Common)

set_target_properties(common
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/src
)
