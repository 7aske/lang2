cmake_minimum_required(VERSION 3.23)
project(lang2)

set(CMAKE_CXX_STANDARD 20)


add_library(lang2_lib
        include/Token.h
        src/lang2_lib/Token.cpp
        include/Lexer.h
        src/lang2_lib/Lexer.cpp
        include/Iterator.h
        include/Utility.h
        src/lang2_lib/Utility.cpp
        include/Parser.h
        src/lang2_lib/Parser.cpp include/Ast.h)

add_executable(lang2 src/lang2/main.cpp)
target_link_libraries(lang2 lang2_lib)

include_directories(lang2 include)

add_subdirectory(test)