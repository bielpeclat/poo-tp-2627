#ifndef POO_TP_2627_MAQUINA_H
#define POO_TP_2627_MAQUINA_H

#include <string>
#include "Coordenada.h"

class Item;
class Fabrica;

enum class Direcao {CIMA, BAIXO, ESQUERDA, DIREITA};

// Classe base abstrata de todas as maquinas da fabrica.
// Guarda o que e comum (posicao, direcao, engenheiros);
// o comportamento de cada tipo fica nas classes derivadas.
class Maquina {
   Coordenada pos;        // posicao fixa na fabrica
   Direcao dir;           // direcao de saida dos itens
   int numEngenheiros;    // engenheiros associados

public:
   Maquina(const Coordenada &pos, Direcao dir);
   virtual ~Maquina();

   // ----- comum a todas as maquinas -----
   const Coordenada& getPosicao() const;
   Direcao getDirecao() const;
   void setDirecao(Direcao d);                 // comando roda

   int getNumEngenheiros() const;
   void adicionaEngenheiro();
   void removeEngenheiro();

   int getValorVenda() const;                  // percentagem do custo (Settings)

   // ----- cada tipo define o seu -----
   virtual int getCusto() const = 0;
   virtual char getCaracter() const = 0;
   virtual std::string getNome() const = 0;

   virtual bool aceita(const Item *item) const = 0;   // pode receber este item agora?
   virtual bool recebe(Item *item) = 0;               // fica com o item (passa a ser dona dele)
   virtual void atua(Fabrica &fabrica) = 0;           // comportamento em cada instante

   virtual std::string getDescricao() const = 0;      // conteudo e estado, para o lposicao
   virtual Maquina* duplica() const = 0;              // copia polimorfica, para o grava

   // ----- melhoravel so em alguns tipos -----
   virtual bool melhora(int &creditos);        // por omissao nao faz nada
};

#endif //POO_TP_2627_MAQUINA_H
