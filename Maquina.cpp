#include "Maquina.h"
#include "Settings.h"

Maquina::Maquina(const Coordenada& pos, Direcao dir) : pos(pos), dir(dir) {}

int Maquina::getValorVenda() const {
    return getCusto() * Settings::maquina_percentagem_venda / 100;
}

char Maquina::getLetraDirecao() const {
    switch (dir) {
        case Direcao::CIMA:     return 'c';
        case Direcao::BAIXO:    return 'b';
        case Direcao::ESQUERDA: return 'e';
        case Direcao::DIREITA:  return 'd';
    }
    return '?';
}
