cmake_minimum_required(VERSION 3.23)
project(Progetto)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(test)

include_directories(date/include/date/date.h)
set(SOURCE_FILES Transazione.cpp Transazione.h ContoCorrente.cpp ContoCorrente.h)
add_executable(main main.cpp)
add_library(core ${SOURCE_FILES})
target_link_libraries(main core)

