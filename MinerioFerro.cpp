#include "MinerioFerro.h"
#include "Settings.h"

std::string MinerioFerro::getNome() const {
   return "Minerio de ferro";
}

char MinerioFerro::getCaracter() const {
   return 'f';
}

int MinerioFerro::getValor() const {
   return Settings::valor_minerio_ferro;
}
