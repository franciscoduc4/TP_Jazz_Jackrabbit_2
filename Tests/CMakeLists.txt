# Tests/CMakeLists.txt

add_executable(tests
    main.cpp
    # Añade aquí otros archivos de pruebas
)

target_link_libraries(tests common yaml-cpp -pthread)

set_target_properties(tests
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Tests
)
