#include "Gelo.h"
#include "Settings.h"

std::string Gelo::getNome() const {
   return "Gelo";
}

char Gelo::getCaracter() const {
   return 'g';
}

int Gelo::getValor() const {
   return Settings::valor_gelo;
}
