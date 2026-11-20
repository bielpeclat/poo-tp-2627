#include "Agua.h"
#include "Settings.h"

std::string Agua::getNome() const {
   return "Agua";
}

char Agua::getCaracter() const {
   return 'a';
}

int Agua::getValor() const {
   return Settings::valor_agua;
}
