#include "Perfuradora.h"
#include "Settings.h"

Perfuradora::Perfuradora(const Coordenada& pos, Direcao dir) : Maquina(pos, dir) {}

int Perfuradora::getCusto() const { return Settings::perfuradora_custo; }
char Perfuradora::getCaracter() const { return 'P'; }
std::string Perfuradora::getNome() const { return "Perfuradora"; }

std::string Perfuradora::getDescricao() const {
    return "extrai de " + std::to_string(Settings::perfuradora_periodo) + " em "
         + std::to_string(Settings::perfuradora_periodo) + " instantes; perda "
         + std::to_string(Settings::perfuradora_prob_perda) + "%";
}

// Enunciado: perfuradora nunca aceita items vindos de outras maquinas
bool Perfuradora::aceita(const Item*) const { return false; }
bool Perfuradora::recebe(Item*, int) { return false; }

void Perfuradora::atua(Fabrica&) {
    // De N em N instantes extrair 1 unidade do deposito e tentar entrega-la - Entrega final.
}