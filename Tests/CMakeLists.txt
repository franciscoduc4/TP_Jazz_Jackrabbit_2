# Specify source files
file(GLOB_RECURSE TEST_SOURCES
    ${PROJECT_SOURCE_DIR}/Tests/*.cpp
    ${PROJECT_SOURCE_DIR}/Tests/*.h
)

# Include GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

enable_testing()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Create test executable
add_executable(tests ${TEST_SOURCES})

# Link dependencies
target_link_libraries(tests common server yaml-cpp fmt::fmt -pthread gtest gtest_main)
target_include_directories(tests PUBLIC ${PROJECT_SOURCE_DIR}/Common ${PROJECT_SOURCE_DIR}/Server)

# Discover tests
include(GoogleTest)
gtest_discover_tests(tests)
