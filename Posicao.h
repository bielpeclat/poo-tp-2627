#ifndef POO_TP_2627_POSICAO_H
#define POO_TP_2627_POSICAO_H

#include <string>

class Maquina;
enum class TipoTerreno {SOLO, CRATERA, FERRO, SILICIO, GELO};

class Posicao {
private:
   TipoTerreno terreno;
   int quantidade;
   Maquina* maquina;
public:
   Posicao(); // esta vazia porque o construtor poem solo/ n = 0

   TipoTerreno getTerreno() const {return terreno; }
   int getQuantidade() const { return quantidade; }

   bool transformaEmDeposito(TipoTerreno t, int q);
   void transformaEmCratera();
   bool eDeposito() const;
   bool removeUnidade(); // tira 1 do deposito da posicao atual
   char getCaracter() const; // (solo/ cratera/ deposito)
   std::string getDescricao() const; // (tipo + quantidade)

   //Máquina colocada nesta posição
   Maquina* getMaquina() const { return maquina; }
   void colocaMaquina(Maquina* m) { maquina = m; }
   Maquina* retiraMaquina() { Maquina* m = maquina; maquina = nullptr; return m; } // devolve-a para a Fabrica depois apagar

};

#endif //POO_TP_2627_POSICAO_H