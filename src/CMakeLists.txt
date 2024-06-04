# src/CMakeLists.txt

# Incluir directorios de encabezados
include_directories(${PROJECT_SOURCE_DIR}/src/Common)

# Dependencias
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Core CONFIG REQUIRED)
find_package(SDL2 REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(fmt REQUIRED)

# Crear biblioteca comun
add_subdirectory("Common")

target_link_libraries(common yaml-cpp fmt::fmt -pthread)
target_include_directories(common PUBLIC ${PROJECT_SOURCE_DIR}/src/Common)

# Servidor
file(GLOB_RECURSE SERVER_SOURCES
    ${PROJECT_SOURCE_DIR}/src/Server/*.cpp
    ${PROJECT_SOURCE_DIR}/src/Server/*.h)

add_library(server ${SERVER_SOURCES})

target_link_libraries(server common yaml-cpp fmt::fmt -pthread)
target_include_directories(server PUBLIC ${PROJECT_SOURCE_DIR}/src/Common)

set_target_properties(server
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
