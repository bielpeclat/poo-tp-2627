#include <iostream>

#include "Settings.h"
#include "Ecra.h"
#include "Biblioteca.h"
#include "Fabrica.h"

int main() {
    std::cout << "Simulador de fabrica em Marte" << std::endl;

    /*Ecra e1(40, 80);
    e1.limpa();
    e1.moldura(0, 0, 40, 80);
    e1.mostra();*/

    // Experimento do Fadigas
    Ecra ecra(15, 35);
    Fabrica fabrica(4, 5);
    fabrica.preparaEcra(ecra, 3, 6);
    ecra.mostra();

    return 0;
}

