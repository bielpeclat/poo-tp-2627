//
// Created by gabriel-costa on 11/4/26.
//

#include <string>
#include "Coordenada.h"

// assume que cords ja foi validado com valida()
Coordenada::Coordenada(const std::string& cords)
   : linha(cords[0] - 'a'), coluna(cords[1] - 'a') {}

Coordenada::Coordenada(int l, int c) : linha(l), coluna(c) {}

int Coordenada::getLinha() const {
   return linha;
}

int Coordenada::getColuna() const {
   return coluna;
}

// caminho inverso: (2,4) -> "ce"
std::string Coordenada::toString() const {
   std::string s;
   s += static_cast<char>('a' + linha);
   s += static_cast<char>('a' + coluna);
   return s;
}

bool Coordenada::valida(const std::string& c, int maxLinhas, int maxColunas) {
   if (c.size() != 2) {
      return false;
   }

   char cl = c[0]; // caracter da linha
   char cc = c[1]; // caracter da coluna

   // tem de ser letra minuscula
   if (cl < 'a' || cl > 'z') {
      return false;
   }
   if (cc < 'a' || cc > 'z') {
      return false;
   }

   // converte letra em indice: 'a' -> 0, 'b' -> 1, ...
   int l = cl - 'a';
   int col = cc - 'a';

   // tem de estar dentro da fabrica
   if (l >= maxLinhas || col >= maxColunas) {
      return false;
   }

   return true;
}