#include "SilicioPuro.h"
#include "Settings.h"

std::string SilicioPuro::getNome() const {
   return "Silicio puro";
}

char SilicioPuro::getCaracter() const {
   return 'i';
}

int SilicioPuro::getValor() const {
   return Settings::valor_silicio_puro;
}
