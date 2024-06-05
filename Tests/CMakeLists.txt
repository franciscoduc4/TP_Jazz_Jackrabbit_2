enable_testing()
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE TEST_SOURCES ${PROJECT_SOURCE_DIR}/Tests/*.cpp ${PROJECT_SOURCE_DIR}/Tests/*.h)
add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests common yaml-cpp fmt::fmt -pthread gtest gtest_main)
include(GoogleTest)
gtest_discover_tests(tests)
