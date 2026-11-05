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

    inicializaGrelhaVazia();
    geraElementosAleatorios();
}

void Fabrica::preparaEcra(Ecra &ecra, int lInicial = 0, int cInicial = 0) const {

    ecra.limpa();

    int altFabrica = tam_Linhas_f + 3; // +3 porque temos de guardar +1 para a "régua" (ABC) e +2 por causa da moldura de cada lado (esquerdo e direito).
    int largFabrica = tam_Colunas_f + 3;

    ecra.moldura(lInicial, cInicial, altFabrica, largFabrica);
    ecra.escreve(lInicial + 1, cInicial + 1, ' ');

    for (int c = 0; c < tam_Colunas_f; c++) { // régua ABC - Colunas
        ecra.escreve(lInicial + 1, cInicial + 2 + c, static_cast<char>('A' + c));
    }

    for (int l = 0; l < tam_Linhas_f; l++) { // régua ABC - Colunas
        ecra.escreve(lInicial + 2 + l, cInicial + 1, static_cast<char>('A' + l));
    }

    for (int l = 0; l < tam_Linhas_f; l++) {
        for (int c = 0; c < tam_Colunas_f; c++) {

            char simbolo = grelha[l][c];
            ecra.escreve(lInicial + 2 + l, cInicial + 2 + c, simbolo);
        }
    }
}

void Fabrica::geraElementosAleatorios() {

    // Crateras = #
    for (int i = 0; i < Settings::fabrica_num_crateras; i++) {
        int l, c;
        do {
            l = rand() % tam_Linhas_f;
            c = rand() % tam_Colunas_f;
        } while (grelha[l][c] != ' ');

        grelha[l][c] = '#';
    }

    int amplitude = Settings::deposito_quantidade_max - Settings::deposito_quantidade_min + 1;

    // 2. Gerar Depósitos de Ferro (%)
    for (int i = 0; i < Settings::fabrica_num_depositos_ferro; i++) {
        int l, c;
        do {
            l = rand() % tam_Linhas_f;
            c = rand() % tam_Colunas_f;
        } while (grelha[l][c] != ' ');

        grelha[l][c] = '%';
        int qtdFerro = Settings::deposito_quantidade_min + (rand() % amplitude);
    }

    // 3. Depósitos de Silício ($)
    for (int i = 0; i < Settings::fabrica_num_depositos_silicio; i++) {
        int l, c;
        do {
            l = rand() % tam_Linhas_f;
            c = rand() % tam_Colunas_f;
        } while (grelha[l][c] != ' ');

        grelha[l][c] = '$';
        int qtdSilicio = Settings::deposito_quantidade_min + (rand() % amplitude);
    }

    // 4. Depósitos de Gelo (~)
    for (int i = 0; i < Settings::fabrica_num_depositos_gelo; i++) {
        int l, c;
        do {
            l = rand() % tam_Linhas_f;
            c = rand() % tam_Colunas_f;
        } while (grelha[l][c] != ' ');

        grelha[l][c] = '~';
        int qtdGelo = Settings::deposito_quantidade_min + (rand() % amplitude);
    }
}

void Fabrica::inicializaGrelhaVazia() {
    for (int l = 0; l < tam_Linhas_f; l++) { // Fiz para que a função percorre-se apenas as linhas e colunas reais da fábrica criada
        for (int c = 0; c < tam_Colunas_f; c++) {
            grelha[l][c] = ' ';
        }
    }
}
