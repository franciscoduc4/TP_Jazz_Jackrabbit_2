# cmake_minimum_required(VERSION 3.10)

# project(JazzJackrabbit2)

# # Set up options
# option(INSTALL "Apply install settings" OFF)
# option(SERVER "Build server" ON)
# option(CLIENT "Build client" ON)

# # Set paths
# if (INSTALL)
#     message(STATUS "Applying install settings")
#     set(CONFIG_FILE "/var/games/jazzjackrabbit2/configurations.yaml")
#     set(BINDIR "/usr/local/bin")
#     set(VARDIR "/var/games/jazzjackrabbit2")
# else()
#     set(CONFIG_FILE "${CMAKE_SOURCE_DIR}/configurations.yaml")
#     set(BINDIR ${CMAKE_BINARY_DIR})
#     set(VARDIR ${CMAKE_SOURCE_DIR})
# endif()
# set(LIBDIR "/usr/local/lib")

# # Dependencies
# find_package(Qt5Widgets CONFIG REQUIRED)
# find_package(Qt5Core CONFIG REQUIRED)
# find_package(SDL2 REQUIRED)
# find_package(yaml-cpp REQUIRED)
# find_package(fmt REQUIRED)

# # Include subdirectories
# add_subdirectory(extlibs/libsdl2pp)
# #add_subdirectory(extlibs/libsdl2pp ${CMAKE_BINARY_DIR}/extlibs/libsdl2pp_build)
# add_subdirectory(src)

# if (TESTING)
#     add_subdirectory(Tests)
# endif()

# # Install
# if(SERVER AND INSTALL)
#     install (FILES "${CMAKE_SOURCE_DIR}/configurations.yaml" DESTINATION ${VARDIR})
#     install(TARGETS jazzserver RUNTIME DESTINATION ${BINDIR})
# endif()

# if(CLIENT AND INSTALL)
#     install(TARGETS jazzclient RUNTIME DESTINATION ${BINDIR})
#     install(TARGETS SDL2pp ARCHIVE DESTINATION ${LIBDIR})
#     install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${VARDIR})
# endif()
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
# add_subdirectory(Tests)
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