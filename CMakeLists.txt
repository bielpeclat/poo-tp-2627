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
        Posicao.cpp
        Posicao.h
        Coordenada.cpp
        Coordenada.h
        Fabrica.cpp
        Fabrica.h
        Comando.cpp
        Comando.h
        Simulador.cpp
        Simulador.h
        CmdFim.cpp
        CmdFim.h
        RegistoComandos.cpp
        RegistoComandos.h
        CmdAjuda.cpp
        CmdAjuda.h
        CmdExecuta.cpp
        CmdExecuta.h
        CmdLPosicao.cpp
        CmdLPosicao.h
        CmdFabrica.cpp
        CmdFabrica.h
        CmdCarrega.cpp
        CmdCarrega.h
        CmdRecupera.cpp
        CmdRecupera.h
        CmdGrava.cpp
        CmdGrava.h
        CmdDespede.cpp
        CmdDespede.h
        CmdAtribui.cpp
        CmdAtribui.h
        CmdContrata.cpp
        CmdContrata.h
        CmdMelhora.cpp
        CmdMelhora.h
        CmdEstado.cpp
        CmdEstado.h
        CmdAvanca.cpp
        CmdAvanca.h
        CmdRoda.cpp
        CmdRoda.h
        CmdVende.cpp
        CmdVende.h
        CmdCompra.cpp
        CmdCompra.h
        Item.h
        MinerioFerro.cpp
        MinerioFerro.h
        SilicioBruto.cpp
        SilicioBruto.h
        Gelo.cpp
        Gelo.h
        PlacaFerro.cpp
        PlacaFerro.h
        SilicioPuro.cpp
        SilicioPuro.h
        Agua.cpp
        Agua.h
        KitHabitat.cpp
        KitHabitat.h
)

# copia a pasta mapas para junto do executavel em cada compilacao
add_custom_command(TARGET poo_tp_2627 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/mapas
        $<TARGET_FILE_DIR:poo_tp_2627>/mapas)
