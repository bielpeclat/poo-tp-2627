#include "Lancador.h"
#include "Settings.h"

Lancador::Lancador(const Coordenada& pos, Direcao dir) : Maquina(pos, dir) {}

int Lancador::getCusto() const { return Settings::lancador_custo; }
char Lancador::getCaracter() const { return 'L'; }
std::string Lancador::getNome() const { return "Lancador"; }

std::string Lancador::getDescricao() const {
    return "sem item; envia 1 item de " + std::to_string(Settings::lancador_recarga) + " em "
         + std::to_string(Settings::lancador_recarga) + " instantes; perda "
         + std::to_string(Settings::lancador_prob_perda) + "%";
}

// aceitar qualquer item quando nao tiver nenhum por lancar - entrega final
bool Lancador::aceita(const Item*) const { return false; }
bool Lancador::recebe(Item*, int) { return false; }

void Lancador::atua(Fabrica&) {
    // lancar o item de N em N instantes e somar os creditos - entrega final
}