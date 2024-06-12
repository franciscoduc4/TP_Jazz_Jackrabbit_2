# src/CMakeLists.txt
# Include directories
include_directories(${PROJECT_SOURCE_DIR}/src/Common)

# Dependencies
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
if(SERVER)
    file(GLOB_RECURSE SERVER_SOURCES
        ${PROJECT_SOURCE_DIR}/src/Server/*.cpp
        ${PROJECT_SOURCE_DIR}/src/Server/*.h
    )
    add_library(jazzserver_lib SHARED ${SERVER_SOURCES})
    add_executable(jazzserver ${SERVER_SOURCES})
    target_link_libraries(jazzserver common yaml-cpp fmt::fmt -pthread)
    target_include_directories(jazzserver PUBLIC ${PROJECT_SOURCE_DIR}/src/Common)
    set_target_properties(jazzserver PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

# Cliente
if(CLIENT)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)

    find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)

    file(GLOB_RECURSE CLIENT_SOURCES
        ${PROJECT_SOURCE_DIR}/src/Client/*.cpp
        ${PROJECT_SOURCE_DIR}/src/Client/*.h
    )

    set(UI_FILES
            ${PROJECT_SOURCE_DIR}/src/Client/charactereselection.ui
            ${PROJECT_SOURCE_DIR}/src/Client/creategame.ui
            ${PROJECT_SOURCE_DIR}/src/Client/gamelist.ui
            ${PROJECT_SOURCE_DIR}/src/Client/lobby.ui
            ${PROJECT_SOURCE_DIR}/src/Client/mapselection.ui
            ${PROJECT_SOURCE_DIR}/src/Client/waitingroom.ui
            ${PROJECT_SOURCE_DIR}/src/Client/welcomes.ui
    )

    qt5_wrap_ui(UIS_HEADERS ${UI_FILES})

    qt5_add_resources(RESOURCES ${PROJECT_SOURCE_DIR}/src/Client/resources.qrc)

    add_executable(jazzclient ${CLIENT_SOURCES} ${UIS_HEADERS} ${RESOURCES}
        Client/Controllers/LobbyController.h
        Client/Controllers/LobbyController.cpp
        Client/Controllers/GameController.cpp
        Client/Controllers/GameController.h
        Client/SDL/level.cpp)
    target_link_libraries(jazzclient common Qt5::Widgets Qt5::Core SDL2 SDL2pp SDL2_image yaml-cpp fmt::fmt -pthread)
    target_include_directories(jazzclient PUBLIC ${PROJECT_SOURCE_DIR}/src/Common)

    set_target_properties(jazzclient PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

# Copy YAML files to the build directory
file(COPY ${CMAKE_SOURCE_DIR}/src/config DESTINATION ${CMAKE_BINARY_DIR})

#add_executable(main.cpp)
