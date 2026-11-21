#include "Silo.h"
#include "Item.h"
#include "Fabrica.h"
#include "Settings.h"

#include <cstdlib>   // rand

Silo::Silo(const Coordenada& pos, Direcao dir)
   : Maquina(pos, dir), primeiro(nullptr), ultimo(nullptr), quantidade(0),
     probPerda(Settings::silo_prob_perda) {}

Silo::~Silo() {
   // Item que ainda esteja no silo quando ele e vendido (ou o programa termina) perde-se.
   while (primeiro != nullptr) {
      apagaPrimeiro();
   }
}

// Retira o no do inicio da lista e apaga o item que ele guardava.
void Silo::apagaPrimeiro() {
   No* no = primeiro;
   primeiro = no->seguinte;
   if (primeiro == nullptr) {
      ultimo = nullptr;          // a lista ficou vazia
   }
   delete no->item;
   delete no;
   quantidade--;
}

// Retira o no do inicio da lista mas NAO apaga o item: ele passou a ser de outra maquina.
void Silo::largaPrimeiro() {
   No* no = primeiro;
   primeiro = no->seguinte;
   if (primeiro == nullptr) {
      ultimo = nullptr;
   }
   delete no;
   quantidade--;
}

int Silo::getCusto() const { return Settings::silo_custo; }
char Silo::getCaracter() const { return 'S'; }
std::string Silo::getNome() const { return "Silo"; }

std::string Silo::getDescricao() const {
   if (quantidade == 0) {
      return "vazio; perda " + std::to_string(probPerda) + "%";
   }
   return std::to_string(quantidade) + " item(ns), o mais antigo: " + primeiro->item->getNome()
        + "; perda " + std::to_string(probPerda) + "%";
}

// Aceita qualquer item (nao ha limite de capacidade).
bool Silo::aceita(const Item* item) const {
   return item != nullptr;
}

// Insere o item no fim da lista. Se devolver false, quem o tentou entregar continua dono do item.
bool Silo::recebe(Item* item, int instante) {
   if (item == nullptr) {
      return false;
   }

   No* novo = new No{item, instante, nullptr};
   if (ultimo == nullptr) {
      primeiro = novo;           // lista vazia: o novo no e o primeiro e o ultimo
   } else {
      ultimo->seguinte = novo;
   }
   ultimo = novo;
   quantidade++;
   return true;
}

void Silo::atua(Fabrica& fabrica) {
   if (primeiro == nullptr) {
      return;                                    // nada guardado
   }

   // 1. Probabilidade de perder o item guardado ha mais tempo
   if (rand() % 100 < probPerda) {
      fabrica.registaEvento("silo " + getPosicao().toString() + " perdeu " + primeiro->item->getNome());
      apagaPrimeiro();
      return;                                    // neste instante nao entrega nada
   }

   // 2. Tenta entregar o item mais antigo na direcao de saida
   if (primeiro->instanteRececao >= fabrica.getInstante()) {
      return;                                    // chegou neste instante: so sai no proximo
   }

   Maquina* vizinha = fabrica.getMaquinaVizinha(getPosicao(), getDirecao());
   if (vizinha != nullptr && vizinha->aceita(primeiro->item)
       && vizinha->recebe(primeiro->item, fabrica.getInstante())) {
      largaPrimeiro();                           // o item ja e da outra maquina: so se apaga o no
   }
}
