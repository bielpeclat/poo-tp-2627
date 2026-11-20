#include "Refinaria.h"
#include "Settings.h"

Refinaria::Refinaria(const Coordenada& pos, Direcao dir) : Maquina(pos, dir) {}

int Refinaria::getCusto() const { return Settings::refinaria_custo; }
char Refinaria::getCaracter() const { return 'R'; }
std::string Refinaria::getNome() const { return "Refinaria"; }

std::string Refinaria::getDescricao() const {
    return "vazia; transformacao demora " + std::to_string(Settings::refinaria_duracao) + " instantes";
}

// aceitar 1 materia-prima quando estiver vazia - entrega final
bool Refinaria::aceita(const Item*) const { return false; }
bool Refinaria::recebe(Item*, int) { return false; }

void Refinaria::atua(Fabrica&) {
    // contar a duracao, transformar e tentar entregar o produto - entrega final
}
