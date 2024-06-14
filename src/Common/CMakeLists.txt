file(GLOB_RECURSE COMMON_SOURCES
    ${PROJECT_SOURCE_DIR}/src/Common/*.cpp
    ${PROJECT_SOURCE_DIR}/src/Common/*.h
)

# Maps Singleton Classes
include_directories(maps)

add_library(common ${COMMON_SOURCES}
        dtoValidator.h
)

# Link libraries and include directories for common
target_link_libraries(common yaml-cpp fmt::fmt -pthread)
target_include_directories(common PUBLIC ${PROJECT_SOURCE_DIR}/src/Common)
