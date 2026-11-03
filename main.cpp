#include <iostream>
#include "Settings.h"
#include "Ecra.h"
#include "Biblioteca.h"

int main() {
    std::cout << "Simulador de fabrica em Marte" << std::endl;

    Ecra e1(3, 4);
    e1.limpa();
    e1.mostra();
    aguardaEnter();
    e1.posiciona(0, 0);
    e1.escreve('G');
    e1.mostra();
    aguardaEnter();
    e1.posiciona(2, 3);
    e1.escreve('G');
    e1.mostra();

    return 0;
}

