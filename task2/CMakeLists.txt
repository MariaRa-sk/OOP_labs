cmake_minimum_required(VERSION 3.16)
project(task2)

set(CMAKE_CXX_STANDARD 17)

add_executable(task2 src/main.cpp
        src/FileReader.cpp
        src/Parser.cpp
        src/GameConfig.cpp
        src/CommandHandler.cpp
        src/GameMechanics.cpp
        src/GameMechanics.h
        src/Window.cpp
        src/Window.h
)

include(FetchContent)
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.8
)
FetchContent_MakeAvailable(glfw)

# Ищем OpenGL (обычно входит в систему)
find_package(OpenGL REQUIRED)

target_link_libraries(task2
        OpenGL::GL
        glfw
)

if(WIN32)
    target_link_libraries(task2
            gdi32
    )
endif()

enable_testing()

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

add_executable(test_parser
        test/ParserTest.cpp
        src/Parser.cpp
        src/FileReader.cpp
        src/GameConfig.cpp
)


target_include_directories(test_parser PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(test_parser PRIVATE GTest::gtest GTest::gtest_main)

gtest_discover_tests(test_parser)