#include "Transportador.h"
#include "Item.h"
#include "Fabrica.h"
#include "Settings.h"

Transportador::Transportador(const Coordenada& pos, Direcao dir)
   : Maquina(pos, dir), item(nullptr), instanteRececao(0) {}

Transportador::~Transportador() {
   delete item;   // Máquina vendida com um item - o item perde-se.
}

int Transportador::getCusto() const { return Settings::transportador_custo; }
std::string Transportador::getNome() const { return "Transportador"; }

// Com item - mostra o item (para se verem os itens a circular);
// Vazio - a seta da direção
char Transportador::getCaracter() const {
   if (item != nullptr) {
      return item->getCaracter();
   }
   switch (getDirecao()) {
      case Direcao::CIMA:     return '^';
      case Direcao::BAIXO:    return 'v';
      case Direcao::ESQUERDA: return '<';
      case Direcao::DIREITA:  return '>';
   }
   return '?';   // Nunca acontece, mas sem isto o compilador dá erro.
}

std::string Transportador::getDescricao() const {
   if (item == nullptr) {
      return "vazio";
   }
   return "leva " + item->getNome();
}

// Aceita qualquer item, desde que esteja vazio.
bool Transportador::aceita(const Item*) const {
   return item == nullptr;
}

bool Transportador::recebe(Item* novo, int instante) {
   if (item != nullptr || novo == nullptr) {
      return false;          // Se o transportador não ficou com ele: quem o tentou entregar continua dono.
   }
   item = novo;              // Agora o transportador é dono do item
   instanteRececao = instante;
   return true;
}

void Transportador::atua(Fabrica& fabrica) {
   if (item == nullptr) {
      return; // nada a entregar
   }
   if (instanteRececao >= fabrica.getInstante()) {
      return;
   }

   Maquina* vizinha = fabrica.getMaquinaVizinha(getPosicao(), getDirecao());
   if (vizinha != nullptr && vizinha->aceita(item)
       && vizinha->recebe(item, fabrica.getInstante())) {
      item = nullptr; // ja não é meu: largo o ponteiro. Sem delete.
   }
}
