cmake_minimum_required(VERSION 3.23)
project(Progetto)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(googletest-main)
include_directories(${gtest_SOURCE_DIR}/include)
include_directories(date/include/date/date.h)
add_executable(Progetto main.cpp Transazione.cpp Transazione.h ContoCorrente.cpp ContoCorrente.h tests.cpp)
target_link_libraries(Progetto gtest gtest_main)

