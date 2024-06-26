# =====================================================
# | Trabajo Práctico Final | Taller de Programación 1 |
# |    Jazz Jackrabbit 2   |    1C2024   |   FIUBA    |
# =====================================================

# Configuración del proyecto
cmake_minimum_required(VERSION 3.16)

project(TP_Jazz_Jackrabbit_2
        DESCRIPTION "TP para Taller de Programación 1 1c2024 FIUBA"
        LANGUAGES CXX
)

# Inclusión de SDL2pp
add_subdirectory(extlibs/libsdl2pp)

# Flags de compilación
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

# Opciones de compilación
option(DEBUG "Compile in debug mode" OFF)
if (DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -ggdb")
endif()

option(TESTING "Build internal testing suite" ON)
option(INSTALL "Apply install settings" OFF)
option(SERVER "Build server" ON)
option(CLIENT "Build client" ON)
option(LEVEL_EDITOR "Build Level Editor" ON)

# ------------------------------------------------------------------------------------
# Configuración de instalación
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
# ------------------------------------------------------------------------------------

# Configuración de paquetes
set(LIBDIR "/usr/local/lib")
set(GTEST_LIBRARY "/usr/lib/libgtest.a")
set(GTEST_MAIN_LIBRARY "/usr/lib/libgtest_main.a")
set(GMOCK_LIBRARY "/usr/lib/libgmock.a")
set(GMOCK_MAIN_LIBRARY "/usr/lib/libgmock_main.a")

if (APPLE)
    list(APPEND CMAKE_PREFIX_PATH "/usr/local/Cellar/sdl2/2.30.3")
    list(APPEND CMAKE_PREFIX_PATH "/usr/local/Cellar/qt@5/5.15.13_1/lib/cmake")
endif()

find_package(fmt REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Gui CONFIG REQUIRED)
find_package(SDL2 REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# ------------------------------------------------------------------------------------
# Common files
include_directories(${PROJECT_SOURCE_DIR}/src/Common)

file(GLOB_RECURSE COMMON_SOURCES
        ${PROJECT_SOURCE_DIR}/src/Common/*.cpp
        ${PROJECT_SOURCE_DIR}/src/Common/*.h
)

add_library(common SHARED ${COMMON_SOURCES})
target_link_libraries(common yaml-cpp fmt::fmt -pthread)
target_include_directories(common PUBLIC ${PROJECT_SOURCE_DIR}/src/Common)

# ------------------------------------------------------------------------------------

# Server files
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

# ------------------------------------------------------------------------------------

# Client files
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
            ${PROJECT_SOURCE_DIR}/src/Client/statistics.ui
            ${PROJECT_SOURCE_DIR}/src/Client/waitingroom.ui
            ${PROJECT_SOURCE_DIR}/src/Client/welcomes.ui
    )

    qt5_wrap_ui(UIS_HEADERS ${UI_FILES})
    qt5_add_resources(RESOURCES ${PROJECT_SOURCE_DIR}/src/Client/resources.qrc)

    add_library(jazzclient_lib SHARED ${CLIENT_SOURCES} ${UIS_HEADERS} ${RESOURCES})
    target_link_libraries(jazzclient_lib common Qt5::Widgets Qt5::Core SDL2 SDL2pp SDL2_image SDL2_mixer yaml-cpp fmt::fmt -pthread)
    add_executable(jazzclient ${PROJECT_SOURCE_DIR}/src/Client/main.cpp)  # Replace main.cpp with the actual main file of jazzclient
    target_link_libraries(jazzclient jazzclient_lib)
    target_include_directories(jazzclient PUBLIC ${PROJECT_SOURCE_DIR}/src/Common)
    set_target_properties(jazzclient PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

# ------------------------------------------------------------------------------------

# Level Editor
if (LEVEL_EDITOR)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)

    file(GLOB_RECURSE LEVELEDITOR_SOURCES
            ${PROJECT_SOURCE_DIR}/LevelEditor/*.cpp
            ${PROJECT_SOURCE_DIR}/LevelEditor/*.h
    )

    set(UI_FILES_2
            ${PROJECT_SOURCE_DIR}/LevelEditor/leveleditor.ui
    )

    qt5_wrap_ui(UIS_HEADERS ${UI_FILES_2})
    qt5_add_resources(RESOURCES_LE ${PROJECT_SOURCE_DIR}/LevelEditor/resourcesLE.qrc)

    add_executable(leveleditor ${LEVELEDITOR_SOURCES} ${UIS_HEADERS} ${RESOURCES_LE})
    target_include_directories(leveleditor PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
    target_link_libraries(leveleditor common Qt5::Widgets Qt5::Core yaml-cpp fmt::fmt -pthread)
    target_include_directories(leveleditor PUBLIC ${PROJECT_SOURCE_DIR}/src/Common)
    set_target_properties(leveleditor PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()
# ------------------------------------------------------------------------------------
# Tests
# Tests
if(TESTING)
    enable_testing()

    file(GLOB_RECURSE TEST_SOURCES
            ${PROJECT_SOURCE_DIR}/Tests/*.cpp
    )

    add_executable(tests ${TEST_SOURCES})
    target_link_libraries(tests 
        GTest::GTest 
        GTest::Main 
        gmock 
        gmock_main 
        jazzserver_lib 
        jazzclient_lib 
        pthread
    )

    include(GoogleTest)
    gtest_discover_tests(tests)
endif()

# ------------------------------------------------------------------------------------

# Enable YAML Files
file(COPY ${CMAKE_SOURCE_DIR}/src/config DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/src/maps DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/LevelEditor/Sprites DESTINATION ${CMAKE_BINARY_DIR})
# ------------------------------------------------------------------------------------

# Server Installation
if(SERVER AND INSTALL)
    install (FILES "${CMAKE_SOURCE_DIR}/config/configurations.yaml" DESTINATION ${VARDIR})
    install(TARGETS jazzserver RUNTIME DESTINATION ${BINDIR})
endif()
# ------------------------------------------------------------------------------------

# Client Installation
if(CLIENT AND INSTALL)
    install(TARGETS jazzclient RUNTIME DESTINATION ${BINDIR})
    install(TARGETS SDL2pp ARCHIVE DESTINATION ${LIBDIR})
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${VARDIR})
endif()

# ------------------------------------------------------------------------------------

# LevelEditor Installation
if(LEVEL_EDITOR AND INSTALL)
    install(TARGETS leveleditor RUNTIME DESTINATION ${BINDIR})
endif()