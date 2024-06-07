# Root CMakeLists.txt

# Copy YAML files to the build directory
file(COPY ${CMAKE_SOURCE_DIR}/src/config DESTINATION ${CMAKE_BINARY_DIR})

# Existing content...
cmake_minimum_required(VERSION 3.16)

project(TP_Jazz_Jackrabbit_2
    DESCRIPTION "TP para Taller de Programación 1 1c2024 FIUBA"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

# Opciones de compilación
option(DEBUG "Compile in debug mode" OFF)
if (DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -ggdb")
endif()

option(TESTING "Build internal testing suite" OFF)
option(INSTALL "Apply install settings" OFF)
option(SERVER "Build server" ON)
option(CLIENT "Build client" ON)


# Configuraciones de instalación
if (INSTALL)
    message(STATUS "Applying install settings")
    set(CONFIG_FILE "/var/games/jazz_jackrabbit_2/configurations.yaml")
    set(BINDIR "/usr/local/bin")
    set(VARDIR "/var/games/jazz_jackrabbit_2")
else()
    set(CONFIG_FILE "${CMAKE_SOURCE_DIR}/config/configurations.yaml")
    set(BINDIR ${CMAKE_BINARY_DIR})
    set(VARDIR ${CMAKE_SOURCE_DIR})
endif()
set(LIBDIR "/usr/local/lib")

# Encontrar la biblioteca {fmt}
find_package(fmt REQUIRED)

# Incluir subdirectorios
add_subdirectory(src)
add_subdirectory(./extlibs/libsdl2pp)

if (TESTING)
    add_subdirectory(Tests)
endif()

# Install
if(SERVER AND INSTALL)
    install (FILES "${CMAKE_SOURCE_DIR}/config/configurations.yaml" DESTINATION ${VARDIR})
    install(TARGETS jazzserver RUNTIME DESTINATION ${BINDIR})
endif()

if(CLIENT AND INSTALL)
    install(TARGETS jazzclient RUNTIME DESTINATION ${BINDIR})
    install(TARGETS SDL2pp ARCHIVE DESTINATION ${LIBDIR})
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${VARDIR})
endif()
