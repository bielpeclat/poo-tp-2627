//
// Created by gabriel-costa on 11/4/26.
//

#ifndef POO_TP_2627_COORDENADA_H
#define POO_TP_2627_COORDENADA_H

#include <string>

class Coordenada {

   int linha, coluna; // (0-25)

public:
   static bool valida(const std::string& c, int maxLinhas, int maxColunas);

   Coordenada(const std::string& cords);
   Coordenada(int l, int c);

   int getLinha() const;
   int getColuna() const;

   std::string toString() const;
};

#endif //POO_TP_2627_COORDENADA_H
