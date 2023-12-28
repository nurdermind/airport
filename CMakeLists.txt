cmake_minimum_required(VERSION 3.27)
project(airport)

set(CMAKE_CXX_STANDARD 17)

add_executable(airport main.cpp
        AviaSale.cpp
        AviaSale.h
        Flight.cpp
        Flight.h)
