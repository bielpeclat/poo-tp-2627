#include <iostream>
#include <cstdlib> // distribuicao aleatoria dos recursos ( crateras e minerios)

#include "Fabrica.h"
#include "Ecra.h"
#include "Settings.h"

Fabrica::Fabrica(int l, int c) {

    tam_Linhas_f = (l < 1) ? 1 : ((l > Settings::fabrica_max_linhas) ? Settings::fabrica_max_linhas : l);
    tam_Colunas_f = (c < 1) ? 1 : ((c > Settings::fabrica_max_colunas) ? Settings::fabrica_max_colunas : c);
    creditos = Settings::fabrica_creditos_iniciais; // Valor que vem da classe Settings onde temos todos os nossos valores limite.
    instante = 0;

    geraElementosAleatorios();
}

void Fabrica::preparaEcra(Ecra &ecra, int lInicial, int cInicial) const {

    ecra.limpa();

    int altFabrica = tam_Linhas_f + 3; // +3 porque temos de guardar +1 para a "régua" (ABC) e +2 por causa da moldura de cada lado (esquerdo e direito).
    int largFabrica = tam_Colunas_f + 3;

    ecra.moldura(lInicial, cInicial, altFabrica, largFabrica);
    ecra.escreve(lInicial + 1, cInicial + 1, ' ');

    for (int c = 0; c < tam_Colunas_f; c++) { // regua ABC - Colunas
        ecra.escreve(lInicial + 1, cInicial + 2 + c, static_cast<char>('A' + c));
    }

    for (int l = 0; l < tam_Linhas_f; l++) { // regua ABC - Colunas
        ecra.escreve(lInicial + 2 + l, cInicial + 1, static_cast<char>('A' + l));
    }

    for (int l = 0; l < tam_Linhas_f; l++) {
        for (int c = 0; c < tam_Colunas_f; c++) {

            char simbolo = grelha[l][c].getCaracter();
            ecra.escreve(lInicial + 2 + l, cInicial + 2 + c, simbolo);
        }
    }
}

void Fabrica::geraElementosAleatorios() {

    colocaAleatorio(TipoTerreno::CRATERA, Settings::fabrica_num_crateras);
    colocaAleatorio(TipoTerreno::FERRO, Settings::fabrica_num_depositos_ferro);
    colocaAleatorio(TipoTerreno::SILICIO, Settings::fabrica_num_depositos_silicio);
    colocaAleatorio(TipoTerreno::GELO, Settings::fabrica_num_depositos_gelo);
}

void Fabrica::colocaAleatorio(TipoTerreno tipo, int quantos) {
    int livres = 0;

    for (int l = 0; l < tam_Linhas_f; l++) {
        for (int c = 0; c < tam_Colunas_f; c++) {
            if (grelha[l][c].getTerreno() == TipoTerreno::SOLO) {
                livres++;
            }
        }
    }
    if (quantos > livres) {
        quantos = livres;
    }

    int amplitude = Settings::deposito_quantidade_max - Settings::deposito_quantidade_min + 1;
}

int Fabrica::getLinhas() const {
    return tam_Linhas_f;
}

int Fabrica::getColunas() const {
    return tam_Colunas_f;
}

int Fabrica::getCreditos() const {
    return creditos;
}

int Fabrica::getInstante() const {
    return instante;
}

const Posicao &Fabrica::getPosicao(int l, int c) const {
    return grelha[l][c];
}
