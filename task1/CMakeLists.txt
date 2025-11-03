cmake_minimum_required(VERSION 3.16)
project(task1)

set(CMAKE_CXX_STANDARD 17)

add_executable(task1
        src/main.cpp
        src/BitArray.cpp
)

enable_testing()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

add_executable(tests
        test/Test.cpp
        src/BitArray.cpp
)

target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(tests PRIVATE GTest::gtest GTest::gtest_main)

gtest_discover_tests(tests)


