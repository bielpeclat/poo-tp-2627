#include <iostream>
#include <cstdlib> //esta biblioteca vai ser necessária no futuro para quando tratarmos da distribuição aleatória dos recursos - crateras e minérios - pelo mapa.

#include "Fabrica.h"
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

void Fabrica::geraElementosAleatorios() {
    // Coloca a quantidade de crateras definida em Settings::num_crateras em posições livres aleatórias
    // Coloca a quantidade de depósitos definida em Settings::num_depositos
    // Para cada depósito, sorteia o tipo (ferro, silício ou gelo) e a quantidade inicial (entre 40 e 60)
}

void Fabrica::inicializaGrelhaVazia() {

}
