cmake_minimum_required(VERSION 3.16)
project(task0)

set(CMAKE_CXX_STANDARD 17)

# ОСНОВНОЕ ПРИЛОЖЕНИЕ - только исходные файлы
add_executable(task0
        src/main.cpp
        src/FileReader.cpp
        src/FileWriter.cpp
        src/TextParser.cpp
        src/Statistic.cpp
)

enable_testing()

# Загрузка GoogleTest - ПРАВИЛЬНЫЙ РЕГИСТР!
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

# ТЕСТОВЫЕ ИСПОЛНЯЕМЫЕ ФАЙЛЫ - отдельно
add_executable(test_parser
        test/TestTextParser.cpp
        src/TextParser.cpp  # только если нужны реализации
)

add_executable(test_statistic
        test/TestStatistic.cpp
        src/Statistic.cpp   # только если нужны реализации
)

# Директории include
target_include_directories(test_parser PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_include_directories(test_statistic PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Связывание с GTest
target_link_libraries(test_parser PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(test_statistic PRIVATE GTest::gtest GTest::gtest_main)

# Обнаружение тестов
gtest_discover_tests(test_parser)
gtest_discover_tests(test_statistic)