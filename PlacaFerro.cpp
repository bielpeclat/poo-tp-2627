#include "PlacaFerro.h"
#include "Settings.h"

std::string PlacaFerro::getNome() const {
   return "Placa de ferro";
}

char PlacaFerro::getCaracter() const {
   return 'p';
}

int PlacaFerro::getValor() const {
   return Settings::valor_placa_ferro;
}
