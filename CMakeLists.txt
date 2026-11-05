cmake_minimum_required(VERSION 3.20)
project(poo_tp_2627 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# O enunciado exige compilar sem qualquer warning
add_compile_options(-Wall -Wextra -pedantic)

add_executable(poo_tp_2627
        main.cpp
        Settings.h
        Ecra.h
        Ecra.cpp
        Biblioteca.h
        Biblioteca.cpp
        Posicao.cpp
        Posicao.h
        Coordenada.cpp
        Coordenada.h
        Fabrica.cpp
        Fabrica.h
        Maquina.cpp
        Maquina.h
)

# copia a pasta mapas para junto do executavel em cada compilacao
add_custom_command(TARGET poo_tp_2627 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/mapas
        $<TARGET_FILE_DIR:poo_tp_2627>/mapas)
