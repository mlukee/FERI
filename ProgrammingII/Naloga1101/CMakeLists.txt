cmake_minimum_required(VERSION 3.21)
project(Naloga1101)

set(CMAKE_CXX_STANDARD 17)

add_executable(Naloga1101 naloga1101.cpp Address.cpp Address.h Date.cpp Date.h Student.cpp Student.h UnparseableDateException.cpp UnparseableDateException.h WrongPhoneNumberException.cpp WrongPhoneNumberException.h)
