enable_testing()
include(FetchContent)

# Descargar y preparar GoogleTest
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

# Buscar todos los archivos fuente de los tests
file(GLOB_RECURSE TEST_SOURCES ${PROJECT_SOURCE_DIR}/Tests/*.cpp ${PROJECT_SOURCE_DIR}/Tests/*.h)

# Crear el ejecutable de tests
add_executable(tests ${TEST_SOURCES})

# Incluir directorios necesarios
target_include_directories(tests PUBLIC ${PROJECT_SOURCE_DIR}/src/Common)

# Vincular el ejecutable de tests con las bibliotecas necesarias
target_link_libraries(tests
    jazzserver_lib
    common
    yaml-cpp
    fmt::fmt
    -pthread
    gtest
    gtest_main
)

# Configurar GoogleTest
include(GoogleTest)
gtest_discover_tests(tests)
