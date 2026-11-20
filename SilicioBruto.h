#ifndef POO_TP_2627_SILICIOBRUTO_H
#define POO_TP_2627_SILICIOBRUTO_H

#include "Item.h"

class SilicioBruto : public Item {
public:
   std::string getNome() const override;
   char getCaracter() const override;
   int getValor() const override;
};

#endif //POO_TP_2627_SILICIOBRUTO_H
