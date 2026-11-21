cmake_minimum_required(VERSION 3.20)
project(poo_tp_2627 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# O enunciado exige compilar sem qualquer warning
add_compile_options(-Wall -Wextra -pedantic)

# Todos os .cpp e .h da raiz entram automaticamente (nao e preciso mexer aqui ao criar classes novas).
# Nao e recursivo de proposito: assim ignora as pastas de build, extras/ e relatorio/.
file(GLOB FICHEIROS_FONTE CONFIGURE_DEPENDS
        ${CMAKE_SOURCE_DIR}/*.cpp
        ${CMAKE_SOURCE_DIR}/*.h)

add_executable(poo_tp_2627 ${FICHEIROS_FONTE})

# copia a pasta mapas para junto do executavel em cada compilacao
add_custom_command(TARGET poo_tp_2627 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/mapas
        $<TARGET_FILE_DIR:poo_tp_2627>/mapas)
