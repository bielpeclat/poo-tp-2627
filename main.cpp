#include <iostream>
#include "Settings.h"
#include "Ecra.h"
#include "Biblioteca.h"

int main() {
    std::cout << "Simulador de fabrica em Marte" << std::endl;

    Ecra e1(15, 15);
    e1.limpa();
    e1.moldura(1, 1, 5, 5);
    e1.mostra();

    return 0;
}

