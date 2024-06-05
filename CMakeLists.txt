cmake_minimum_required(VERSION 3.10)

project(JazzJackrabbit2)

# Set up options
option(INSTALL "Apply install settings" OFF)
option(SERVER "Build server" ON)
option(CLIENT "Build client" ON)

# Set paths
if (INSTALL)
    message(STATUS "Applying install settings")
    set(CONFIG_FILE "/var/games/jazzjackrabbit2/configurations.yaml")
    set(BINDIR "/usr/local/bin")
    set(VARDIR "/var/games/jazzjackrabbit2")
else()
    set(CONFIG_FILE "${CMAKE_SOURCE_DIR}/configurations.yaml")
    set(BINDIR ${CMAKE_BINARY_DIR})
    set(VARDIR ${CMAKE_SOURCE_DIR})
endif()
set(LIBDIR "/usr/local/lib")

# Dependencies
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Core CONFIG REQUIRED)
find_package(SDL2 REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(fmt REQUIRED)

# Incluir subdirectorios
add_subdirectory(src)
# add_subdirectory(Tests)
add_subdirectory(./extlibs/libsdl2pp)

add_subdirectory(src/Common)
add_subdirectory(src/Server)
add_subdirectory(src/Client)

if (TESTING)
    add_subdirectory(Tests)
endif()

# Install
if(SERVER AND INSTALL)
    install (FILES "${CMAKE_SOURCE_DIR}/configurations.yaml" DESTINATION ${VARDIR})
    install(TARGETS jazzserver RUNTIME DESTINATION ${BINDIR})
endif()

if(CLIENT AND INSTALL)
    install(TARGETS jazzclient RUNTIME DESTINATION ${BINDIR})
    install(TARGETS SDL2pp ARCHIVE DESTINATION ${LIBDIR})
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${VARDIR})
endif()
