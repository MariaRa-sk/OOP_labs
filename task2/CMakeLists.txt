cmake_minimum_required(VERSION 3.16)
project(task2)

set(CMAKE_CXX_STANDARD 17)

add_executable(task2 src/main.cpp
        src/FileReader.cpp
        src/Parser.cpp
        src/GameConfig.cpp
        src/CommandHandler.cpp
        src/GameMechanics.cpp
        src/Window.cpp
        src/FileWriter.cpp
        src/Patterns.cpp
        src/Controller.cpp
)

target_include_directories(task2 PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        "C:/Users/kuzin/SFML/SFML-2.6.2/include"
)

target_link_directories(task2 PRIVATE "C:/Users/kuzin/SFML/SFML-2.6.2/lib")

target_link_libraries(task2
        sfml-graphics
        sfml-window
        sfml-system
)

enable_testing()

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

add_executable(test_mechanics
        test/GameMechanicsTest.cpp
        src/GameMechanics.cpp
        src/GameConfig.cpp
        src/FileWriter.cpp
        src/FileReader.cpp
        src/Parser.cpp
)

target_include_directories(test_mechanics PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(test_mechanics PRIVATE GTest::gtest GTest::gtest_main)
gtest_discover_tests(test_mechanics)