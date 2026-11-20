#ifndef POO_TP_2627_PLACAFERRO_H
#define POO_TP_2627_PLACAFERRO_H

#include "Item.h"

class PlacaFerro : public Item {
public:
   std::string getNome() const override;
   char getCaracter() const override;
   int getValor() const override;
};

#endif //POO_TP_2627_PLACAFERRO_H
