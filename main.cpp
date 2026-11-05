#include <iostream>
#include "Settings.h"
#include "Ecra.h"
#include "Biblioteca.h"
#include "Posicao.h"

int main() {
    std::cout << "Simulador de fabrica em Marte" << std::endl;

    Ecra e1(3, 3);
    e1.limpa();
    e1.moldura(0, 0, 3, 3);
    e1.escreve(3, 3, 'X');
    e1.mostra();
    aguardaEnter();
    std::cout << "Vamos declarar uma posicao isolada...\n";
    Posicao p1;
    std::cout << p1.getDescricao() << std::endl;
    p1.transformaEmCratera();
    std::cout << p1.getDescricao() << std::endl;
    p1.transformaEmDeposito(TipoTerreno::SILICIO, 7);
    std::cout << p1.getDescricao() << std::endl;
    std::cout << p1.getQuantidade() << std::endl;
    aguardaEnter();

    return 0;
}

