cmake_minimum_required(VERSION 3.21)
project(Naloga0602)

set(CMAKE_CXX_STANDARD 14)

add_executable(Naloga0602 naloga0602.cpp Instrument.cpp Instrument.h Guitar.cpp Guitar.h Piano.cpp Piano.h Concert.cpp Concert.h)
