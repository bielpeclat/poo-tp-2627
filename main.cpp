#include <iostream>

#include "Settings.h"
#include "Ecra.h"
#include "Biblioteca.h"

int main() {
    std::cout << "Simulador de fabrica em Marte" << std::endl;

    Ecra e1(40, 80);
    e1.limpa();
    e1.moldura(0, 0, 40, 80);
    e1.mostra();

    return 0;
}

