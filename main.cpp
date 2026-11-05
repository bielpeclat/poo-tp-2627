#include <iostream>

#include "Settings.h"
#include "Ecra.h"
#include "Biblioteca.h"
#include "Posicao.h"
#include "Fabrica.h"

// Notas: Não usar nunca o limpa nem o mostra no main. Isto são funções que, embora afetem o ecrã, elas são aplicadas na fábrica.

int main() {
    std::cout << "Simulador de fabrica em Marte" << std::endl;

    Ecra e1(20, 50);
    Fabrica f1(10, 10);
    f1.preparaEcra(e1, 0, 0);
    e1.mostra();

    Ecra e2(20, 50);
    Fabrica f2(10, 10);
    f2.preparaEcra(e2, 0, 0);
    e2.mostra();

    /*e1.mostra();
    e1.moldura(0, 0, 15, 30);
    e1.escreve(3, 3, 'X');
    e1.mostra();*/
    //aguardaEnter();
    /*std::cout << "Vamos declarar uma posicao isolada...\n";
    Posicao p1;
    std::cout << p1.getDescricao() << std::endl;
    p1.transformaEmCratera();
    std::cout << p1.getDescricao() << std::endl;
    p1.transformaEmDeposito(TipoTerreno::SILICIO, 7);
    std::cout << p1.getDescricao() << std::endl;
    std::cout << p1.getQuantidade() << std::endl;
    aguardaEnter();*/

    return 0;
}

