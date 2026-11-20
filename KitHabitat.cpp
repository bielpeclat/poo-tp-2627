#include "KitHabitat.h"
#include "Settings.h"

std::string KitHabitat::getNome() const {
   return "Kit de habitat";
}

char KitHabitat::getCaracter() const {
   return 'k';
}

int KitHabitat::getValor() const {
   return Settings::valor_kit_habitat;
}
