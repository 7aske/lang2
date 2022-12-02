cmake_minimum_required(VERSION 3.23)
project(lang2)

set(CMAKE_CXX_STANDARD 20)

add_executable(lang2
        src/main.cpp
        include/Token.h
        src/lang2/Token.cpp
        include/Lexer.h
        src/lang2/Lexer.cpp
        include/Iterator.h
        include/Utility.h
        src/lang2/Utility.cpp)

include_directories(lang2 include)
