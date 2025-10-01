cmake_minimum_required(VERSION 4.0)
project(task0)

set(CMAKE_CXX_STANDARD 17)

add_executable(task0 src/main.cpp
        src/FileReader.cpp
        src/TextParser.cpp
        src/FileWriter.cpp
        src/Statistic.cpp
        src/main.cpp)
