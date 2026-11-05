#include <iostream>
#include <ctime>
#include <cstdlib>


#include "Settings.h"
#include "Ecra.h"
#include "Biblioteca.h"
#include "Posicao.h"
#include "Fabrica.h"

// Notas: Nao usar nunca o limpa nem o mostra no main. Isto sao funcoes que, embora afetem o ecra, elas sao aplicadas na fabrica.

int main() {
    std::cout << "Simulador de fabrica em Marte" << std::endl;

    srand(time(nullptr));

    Ecra e1(20, 50);
    Fabrica f1(10, 10);
    f1.preparaEcra(e1, 0, 0);
    e1.mostra();
    for (int l = 0; l < f1.getLinhas(); l++)
        for (int c = 0; c < f1.getColunas(); c++)
            if (f1.getPosicao(l, c).eDeposito())
                std::cout << f1.getPosicao(l, c).getDescricao() << std::endl;

    Ecra e2(20, 50);
    Fabrica f2(4, 4);
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

