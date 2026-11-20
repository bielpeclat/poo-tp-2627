#ifndef POO_TP_2627_ITEM_H
#define POO_TP_2627_ITEM_H

#include <string>

class Item { // Classe -abstrata- para todos os itens que circulam pela fabrica
public:
   virtual ~Item() = default;

   virtual std::string getNome() const = 0;
   virtual char getCaracter() const = 0;
   virtual int getValor() const = 0;  // valor em creditos
};

#endif //POO_TP_2627_ITEM_H
