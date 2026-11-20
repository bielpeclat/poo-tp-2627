#ifndef POO_TP_2627_KITHABITAT_H
#define POO_TP_2627_KITHABITAT_H

#include "Item.h"

class KitHabitat : public Item {
public:
   std::string getNome() const override;
   char getCaracter() const override;
   int getValor() const override;
};

#endif //POO_TP_2627_KITHABITAT_H
