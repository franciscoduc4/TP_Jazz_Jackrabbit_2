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
# file(GLOB_RECURSE SERVER_SOURCES
#     ${PROJECT_SOURCE_DIR}/src/Server/*.cpp
#     ${PROJECT_SOURCE_DIR}/src/Server/*.h)

# add_executable(server ${SERVER_SOURCES})

# target_link_libraries(server common yaml-cpp fmt::fmt -pthread)
# target_include_directories(server PUBLIC ${PROJECT_SOURCE_DIR}/src/Common)

# set_target_properties(server
#     PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
# )

# Cliente (si se implementa más adelante)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)

file(GLOB_RECURSE CLIENT_SOURCES
    ${PROJECT_SOURCE_DIR}/src/Client/*.cpp
    ${PROJECT_SOURCE_DIR}/src/Client/*.h
)
add_executable(client ${CLIENT_SOURCES})


target_link_libraries(client common Qt5::Widgets Qt5::Core SDL2 SDL2pp yaml-cpp fmt::fmt -pthread)
target_include_directories(client PUBLIC ${PROJECT_SOURCE_DIR}/src/Common)

# set(UI_FILES
#         ${PROJECT_SOURCE_DIR}/src/Client/charactereselection.ui
#         ${PROJECT_SOURCE_DIR}/src/Client/creategame.ui
#         ${PROJECT_SOURCE_DIR}/src/Client/gamelist.ui
#         ${PROJECT_SOURCE_DIR}/src/Client/lobby.ui
#         ${PROJECT_SOURCE_DIR}/src/Client/sceneselection.ui
#         ${PROJECT_SOURCE_DIR}/src/Client/waitingroom.ui
#         ${PROJECT_SOURCE_DIR}/src/Client/welcomes.ui
# )

# qt5_wrap_ui(UIS_HEADERS ${UI_FILES})

target_include_directories(client PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

#
# set_target_properties(client
#     PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
# )

#add_subdirectory("extlibs/libsdl2pp")

#add_executable(main.cpp SDL2PP)