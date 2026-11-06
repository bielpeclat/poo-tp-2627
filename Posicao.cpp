//
// Created by gabriel-costa on 11/4/26.
//

#include "Posicao.h"

Posicao::Posicao() : terreno(TipoTerreno::SOLO), quantidade(0) {}

bool Posicao::transformaEmDeposito(TipoTerreno t, int q) {
   if (t != TipoTerreno::FERRO &&
       t != TipoTerreno::SILICIO &&
       t != TipoTerreno::GELO) {
      return false;
   }

   if (q <= 0) return false;

   terreno = t;
   quantidade = q;
   return true;
}

bool Posicao::eDeposito() const {
   return (terreno == TipoTerreno::FERRO ||
           terreno == TipoTerreno::SILICIO ||
           terreno == TipoTerreno::GELO);
}

void Posicao::transformaEmCratera() {
   terreno = TipoTerreno::CRATERA;
   quantidade = 0;
}

bool Posicao::removeUnidade() {
   if (!eDeposito()) return false;

   if (quantidade <= 0) return false;

   quantidade--;

   if (quantidade == 0) terreno = TipoTerreno::SOLO;
   return true;
}

char Posicao::getCaracter() const {
   switch(terreno) {
      case TipoTerreno::SOLO:
         return ' ';

      case TipoTerreno::CRATERA:
         return '#';

      case TipoTerreno::FERRO:
         return '%';

      case TipoTerreno::SILICIO:
         return '$';

      case TipoTerreno::GELO:
         return '~';

      default:
         return '?';
   }
}

std::string Posicao::getDescricao() const {
   switch (terreno) {
      case TipoTerreno::SOLO:
         return "Solo";

      case TipoTerreno::CRATERA:
         return "Cratera";

      case TipoTerreno::FERRO:
         return "Deposito de Ferro com " + std::to_string(quantidade) + " unidades";

      case TipoTerreno::SILICIO:
         return "Deposito de Silicio com " + std::to_string(quantidade) + " unidades";

      case TipoTerreno::GELO:
         return "Deposito de Gelo com " + std::to_string(quantidade) + " unidades";

      default:
         return "?";
   }
}
