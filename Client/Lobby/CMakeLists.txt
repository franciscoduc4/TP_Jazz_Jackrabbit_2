cmake_minimum_required(VERSION 3.5)

project(Lobby VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(fmt_DIR ~/fmt/build)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

find_package(fmt REQUIRED)

# Copiado de la repo de yaml-cpp
include(FetchContent)

FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG 0.8.0 # Can be a tag (yaml-cpp-x.x.x), a commit hash, or a branch name (master)
)
FetchContent_GetProperties(yaml-cpp)

if(NOT yaml-cpp_POPULATED)
  message(STATUS "Fetching yaml-cpp...")
  FetchContent_Populate(yaml-cpp)
  add_subdirectory(${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR})
endif()
# Fin fragmento copiado

set(PROJECT_SOURCES
        lobbyInit.cpp lobbyInit.h
        welcome.cpp welcome.h welcome.ui
        lobby.cpp lobby.h lobby.ui
        sceneselection.cpp sceneselection.h sceneselection.ui
        gamelist.cpp gamelist.h gamelist.ui
        creategame.cpp creategame.h creategame.ui
        characterselection.cpp characterselection.h characterselection.ui
        waitingroom.cpp waitingroom.h waitingroom.ui
        scenespriteswidget.cpp scenespriteswidget.h
        ../Client/QTMonitor.h ../Client/QTMonitor.cpp
        ../Client/gameStatusMonitor.h ../Client/gameStatusMonitor.cpp
        ../Client/senderThread.h ../Client/senderThread.cpp
        ../Client/receiverThread.h ../Client/receiverThread.cpp
        ../Common/protocol.h ../Common/protocol.cpp
        ../Common/socket.h ../Common/socket.cpp
        ../Common/queue.h
        ../Common/liberror.cpp ../Common/liberror.h
        ../Common/resolver.cpp ../Common/resolver.cpp
        ../Common/resolvererror.cpp ../Common/resolvererror.h

    )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Lobby
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Lobby APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Lobby SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Lobby
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Lobby PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Lobby PUBLIC yaml-cpp::yaml-cpp)
target_link_libraries(Lobby PRIVATE fmt::fmt)

set_target_properties(Lobby PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Lobby
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Lobby)
endif()
