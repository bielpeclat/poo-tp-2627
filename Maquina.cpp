#include "Maquina.h"
#include "Settings.h"

Maquina::Maquina(const Coordenada& pos, Direcao dir) : pos(pos), dir(dir) {}

int Maquina::getValorVenda() const {
    return getCusto() * Settings::maquina_percentagem_venda / 100;
}
