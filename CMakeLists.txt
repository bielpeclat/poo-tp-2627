cmake_minimum_required(VERSION 3.20)
project(poo_tp_2627 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# O enunciado exige compilar sem qualquer warning
add_compile_options(-Wall -Wextra -pedantic)

add_executable(poo_tp_2627
        main.cpp
        Settings.h
        Settings.cpp
)
