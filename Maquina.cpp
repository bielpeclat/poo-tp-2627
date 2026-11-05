#include "Maquina.h"
#include "Settings.h"

Maquina::Maquina(const Coordenada &pos, Direcao dir)
   : pos(pos), dir(dir), numEngenheiros(0) {}

Maquina::~Maquina() {}

const Coordenada& Maquina::getPosicao() const {
   return pos;
}

Direcao Maquina::getDirecao() const {
   return dir;
}

void Maquina::setDirecao(Direcao d) {
   dir = d;
}

int Maquina::getNumEngenheiros() const {
   return numEngenheiros;
}

void Maquina::adicionaEngenheiro() {
   numEngenheiros++;
}

void Maquina::removeEngenheiro() {
   if (numEngenheiros > 0) {
      numEngenheiros--;
   }
}

int Maquina::getValorVenda() const {
   return getCusto() * Settings::maquina_percentagem_venda / 100;
}

// por omissao a maquina nao e melhoravel
bool Maquina::melhora(int &) {
   return false;
}
