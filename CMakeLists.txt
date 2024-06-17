cmake_minimum_required(VERSION 3.16)

project(TP_Jazz_Jackrabbit_2
        DESCRIPTION "TP para Taller de Programación 1 1c2024 FIUBA"
        LANGUAGES CXX
)

add_subdirectory(extlibs/libsdl2pp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

option(DEBUG "Compile in debug mode" OFF)
if (DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -ggdb")
endif()

option(TESTING "Build internal testing suite" OFF)
option(INSTALL "Apply install settings" OFF)
option(SERVER "Build server" ON)
option(CLIENT "Build client" ON)

if (INSTALL)
    message(STATUS "Applying install settings")
    set(CONFIG_FILE "/var/games/jazz_jackrabbit_2/configurations.yaml")
    set(BINDIR "/usr/local/bin")
    set(VARDIR "/var/games/jazz_jackrabbit_2")
else()
    # set(CONFIG_FILE "${CMAKE_SOURCE_DIR}/config/configurations.yaml")
    set(BINDIR ${CMAKE_BINARY_DIR})
    set(VARDIR ${CMAKE_SOURCE_DIR})
endif()
set(LIBDIR "/usr/local/lib")

if (APPLE)
    list(APPEND CMAKE_PREFIX_PATH "/usr/local/Cellar/sdl2/2.30.3")
    list(APPEND CMAKE_PREFIX_PATH "/usr/local/Cellar/qt@5/5.15.13_1/lib/cmake")
endif()

find_package(fmt REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Core CONFIG REQUIRED)
find_package(SDL2 REQUIRED)
find_package(yaml-cpp REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/src/Common)

file(GLOB_RECURSE COMMON_SOURCES
        ${PROJECT_SOURCE_DIR}/src/Common/*.cpp
        ${PROJECT_SOURCE_DIR}/src/Common/*.h
)

add_library(common ${COMMON_SOURCES})
target_link_libraries(common yaml-cpp fmt::fmt -pthread)
target_include_directories(common PUBLIC ${PROJECT_SOURCE_DIR}/src/Common)

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

if(CLIENT)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)

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
            src/Client/Protocol/protocol.h)
    target_link_libraries(jazzclient common Qt5::Widgets Qt5::Core SDL2 SDL2pp SDL2_image yaml-cpp fmt::fmt -pthread)
    target_include_directories(jazzclient PUBLIC ${PROJECT_SOURCE_DIR}/src/Common)
    set_target_properties(jazzclient PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

file(COPY ${CMAKE_SOURCE_DIR}/src/config DESTINATION ${CMAKE_BINARY_DIR})

if(SERVER AND INSTALL)
    install (FILES "${CMAKE_SOURCE_DIR}/config/configurations.yaml" DESTINATION ${VARDIR})
    install(TARGETS jazzserver RUNTIME DESTINATION ${BINDIR})
endif()

if(CLIENT AND INSTALL)
    install(TARGETS jazzclient RUNTIME DESTINATION ${BINDIR})
    install(TARGETS SDL2pp ARCHIVE DESTINATION ${LIBDIR})
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${VARDIR})
endif()