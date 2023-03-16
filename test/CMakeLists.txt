project(Google_tests)

add_subdirectory(lib)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_Tests_run
        lang2_lib/LexerTest.cpp
        lang2_lib/ParserTest.cpp ../include/Interpreter.h ../src/lang2_lib/Interpreter.cpp lang2_lib/InterpreterTest.cpp)

target_link_libraries(Google_Tests_run lang2_lib)

target_link_libraries(Google_Tests_run gtest gtest_main)