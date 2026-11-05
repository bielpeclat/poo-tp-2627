#include <iostream>
#include <cstdlib> //esta biblioteca vai ser necessária no futuro para quando tratarmos da distribuição aleatória dos recursos - crateras e minérios - pelo mapa.

#include "Fabrica.h"
#include "Ecra.h"
#include "Settings.h"

Fabrica::Fabrica(int l, int c) {

    tam_Linhas_f = (l < 1) ? 1 : ((l > 26) ? 26 : l);
    tam_Colunas_f = (c < 1) ? 1 : ((c > 26) ? 26 : c);
    creditos = Settings::fabrica_creditos_iniciais; // Valor que vem da classe Settings onde temos todos os nossos valores limite.
    instante = 0;

    // 3. Reservar a matriz da grelha com terreno normal (Solo)
    inicializaGrelhaVazia();

    // 4. Colocar as crateras e depósitos aleatórios
    geraElementosAleatorios();
}

void Fabrica::preparaEcra(Ecra &ecra, int lInicial = 0, int cInicial = 0) const {
    // 1. Limpar o buffer virtual do ecrã
    ecra.limpa();

    // 2. Calcular dimensões da moldura da fábrica
    // nLinhas/nColunas da fábrica + 1 para a régua + 2 para as bordas da moldura
    int altFabrica = tam_Linhas_f + 3;
    int largFabrica = tam_Colunas_f + 3;

    // Desenha a moldura no canto superior esquerdo (linha 0, coluna 0)
    ecra.moldura(lInicial, cInicial, altFabrica, largFabrica);

    // 3. Desenhar as réguas com letras maiúsculas (A, B, C...)
    // Colunas (linha 1 do ecrã virtual)
    for (int c = 0; c < tam_Colunas_f; c++) {
        ecra.escreve(lInicial + 1, cInicial + 2 + c, static_cast<char>('A' + c));
    }
    // Linhas (coluna 1 do ecrã virtual)
    for (int l = 0; l < tam_Linhas_f; l++) {
        ecra.escreve(lInicial + 2 + l, cInicial + 1, static_cast<char>('A' + l));
    }
}

void Fabrica::geraElementosAleatorios() {
    // Coloca a quantidade de crateras definida em Settings::num_crateras em posições livres aleatórias
    // Coloca a quantidade de depósitos definida em Settings::num_depositos
    // Para cada depósito, sorteia o tipo (ferro, silício ou gelo) e a quantidade inicial (entre 40 e 60)
}

void Fabrica::inicializaGrelhaVazia() {

}
