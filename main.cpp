#include <cstdlib>
#include <ctime>

#include "Simulador.h"

int main() {
   srand(static_cast<unsigned>(time(nullptr)));

   Simulador sim;
   sim.corre();

   return 0;   // ao sair do main, o destrutor do Simulador liberta tudo.
}