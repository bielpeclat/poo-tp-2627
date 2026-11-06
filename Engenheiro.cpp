//
// Created by Filipe Fadigas on 06/11/2026.
//

#include "Engenheiro.h"

// Inicializa o contador global de engenheiros
int Engenheiro::contadorId = 1;

Engenheiro::Engenheiro(const std::string& nomeEngenheiro) :
    nome(nomeEngenheiro), maquinaAssociada(nullptr)
{
    id = contadorId++;
}

int Engenheiro::getId() const { return id; }
std::string Engenheiro::getNome() const { return nome; }
bool Engenheiro::isLivre() const { return maquinaAssociada == nullptr; }

void Engenheiro::associaMaquina(Maquina* novaMaquina) {
    maquinaAssociada = novaMaquina;
}

void Engenheiro::liberta() {
    maquinaAssociada = nullptr;
}
