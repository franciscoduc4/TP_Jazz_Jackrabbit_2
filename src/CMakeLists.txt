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

add_executable(server ${SERVER_SOURCES})

target_link_libraries(server common yaml-cpp fmt::fmt -pthread)
target_include_directories(server PUBLIC ${PROJECT_SOURCE_DIR}/src/Common)

set_target_properties(server
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Cliente (si se implementa más adelante)
# file(GLOB_RECURSE CLIENT_SOURCES
#     ${PROJECT_SOURCE_DIR}/src/Client/*.cpp
#     ${PROJECT_SOURCE_DIR}/src/Client/*.h
# )
# add_executable(client ${CLIENT_SOURCES})


# target_link_libraries(client common Qt5::Widgets Qt5::Core SDL2 yaml-cpp fmt::fmt -pthread)
# target_include_directories(client PUBLIC ${PROJECT_SOURCE_DIR}/src/Common)
#
# set_target_properties(client
#     PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
# )

#add_subdirectory("extlibs/libsdl2pp")

#add_executable(main.cpp SDL2PP)

# Tests 

FILE(GLOB_RECURSE TEST_SOURCES
    ${PROJECT_SOURCE_DIR}/src/Tests/*.cpp
    ${PROJECT_SOURCE_DIR}/src/Tests/*.h
)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

enable_testing()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(tests ${TEST_SOURCES})

target_link_libraries(tests common yaml-cpp fmt::fmt -pthread gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)