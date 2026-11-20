#include "Oficina.h"
#include "Settings.h"

Oficina::Oficina(const Coordenada& pos, Direcao dir) : Maquina(pos, dir) {}

int Oficina::getCusto() const { return Settings::oficina_custo; }
char Oficina::getCaracter() const { return 'O'; }
std::string Oficina::getNome() const { return "Oficina"; }

std::string Oficina::getDescricao() const {
    return "vazia; producao demora " + std::to_string(Settings::oficina_duracao) + " instantes";
}

// aceitar os ingredientes da receita - entrega final
bool Oficina::aceita(const Item*) const { return false; }
bool Oficina::recebe(Item*, int) { return false; }

void Oficina::atua(Fabrica&) {
    // quando tiver a receita, produzir o kit e tentar entrega-lo - entrega final
}
