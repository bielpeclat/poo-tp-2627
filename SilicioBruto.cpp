#include "SilicioBruto.h"
#include "Settings.h"

std::string SilicioBruto::getNome() const {
   return "Silicio bruto";
}

char SilicioBruto::getCaracter() const {
   return 's';
}

int SilicioBruto::getValor() const {
   return Settings::valor_silicio_bruto;
}
