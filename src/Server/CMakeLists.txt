file(GLOB_RECURSE SERVER_SOURCES
    CommandHandlers/*.cpp
    CommandHandlers/*.h
    Game/*.cpp
    Game/*.h
    Protocol/*.cpp
    Protocol/*.h
    Threads/*.cpp
    Threads/*.h
    *.cpp
    *.h
)

add_executable(jazzserver ${SERVER_SOURCES})
target_link_libraries(jazzserver common yaml-cpp fmt::fmt -pthread)
target_include_directories(jazzserver PUBLIC ${PROJECT_SOURCE_DIR}/src/Common)
