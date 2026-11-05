#ifndef POO_TP_2627_POSICAO_H
#define POO_TP_2627_POSICAO_H

#include <string>

enum class TipoTerreno {SOLO, CRATERA, FERRO, SILICIO, GELO};

class Posicao {
private:
   TipoTerreno terreno;
   int quantidade;
public:
   Posicao();

   TipoTerreno getTerreno() const;
   int getQuantidade() const;

   bool transformaEmDeposito(TipoTerreno t, int q);
   void transformaEmCratera();
   bool eDeposito() const;
   bool removeUnidade();
   char getCaracter() const;
   std::string getDescricao() const;

};

#endif //POO_TP_2627_POSICAO_H