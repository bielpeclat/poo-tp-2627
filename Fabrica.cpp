#include <string>
#include <fstream>

#include "Fabrica.h"
#include "Ecra.h"
#include "Settings.h"
#include "Coordenada.h"

Fabrica::Fabrica(int l, int c, bool aleatoria) { // bool aleatoria necessária para caso a fabrica seja criada apartir de um mapa

    //ternários aninhados
    tam_Linhas_f = (l < 1) ? 1 : ((l > Settings::fabrica_max_linhas) ? Settings::fabrica_max_linhas : l);
    tam_Colunas_f = (c < 1) ? 1 : ((c > Settings::fabrica_max_colunas) ? Settings::fabrica_max_colunas : c);
    creditos = Settings::fabrica_creditos_iniciais;
    instante = 0;

    if (aleatoria) geraElementosAleatorios();
}

Fabrica::Fabrica(int l, int c) : Fabrica(l, c, true) {} // delegação

void Fabrica::preparaEcra(Ecra &ecra, int lInicial, int cInicial) const {

    ecra.limpa();

    int altFabrica = tam_Linhas_f + 3; // +3 porque temos de guardar +1 para a "regua" (ABC) e +2 por causa da moldura de cada lado (esquerdo e direito).
    int largFabrica = tam_Colunas_f + 3;

    ecra.moldura(lInicial, cInicial, altFabrica, largFabrica);
    ecra.escreve(lInicial + 1, cInicial + 1, ' '); // Apenas pro espaço entre os 'A'.

    for (int c = 0; c < tam_Colunas_f; c++) { // regua ABC - Colunas
        ecra.escreve(lInicial + 1, cInicial + 2 + c, static_cast<char>('A' + c));
    }

    for (int l = 0; l < tam_Linhas_f; l++) { // regua ABC - Linhas
        ecra.escreve(lInicial + 2 + l, cInicial + 1, static_cast<char>('A' + l));
    }

    for (int l = 0; l < tam_Linhas_f; l++) {
        for (int c = 0; c < tam_Colunas_f; c++) {

            char simbolo = grelha[l][c].getCaracter();
            ecra.escreve(lInicial + 2 + l, cInicial + 2 + c, simbolo);
        }
    }
    int altPainel = altFabrica;
        if (altPainel < 10) {
            altPainel = 10;
        }

    desenhaPainel(ecra, lInicial, cInicial + largFabrica + 1, altPainel);
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

    for (int i = 0; i < quantos; i++) {
        int l, c;
        do {
            l = rand() % tam_Linhas_f;
            c = rand() % tam_Colunas_f;
        } while (grelha[l][c].getTerreno() != TipoTerreno::SOLO);
        if (tipo == TipoTerreno::CRATERA) {
            grelha[l][c].transformaEmCratera();
        } else {
            grelha[l][c].transformaEmDeposito(tipo, quantidadeAleatoria());
        }
    }
}


const Posicao &Fabrica::getPosicao(int l, int c) const {
    return grelha[l][c];
}

std::string Fabrica::listaPosicao(const std::string& lc, int raio) const {

    if (!Coordenada::valida(lc, tam_Linhas_f, tam_Colunas_f)) {
        return "Posicao invalida: " + lc + "\n";
    }

    if (raio < 0) {
        return "Raio invalido\n";
    }

    Coordenada centro(lc);

    std::string resultado;

    for (int l = centro.getLinha() - raio; l <= centro.getLinha() + raio; l++) {
        for (int c = centro.getColuna() - raio; c <= centro.getColuna() + raio; c++) {
            if (l < 0 || l >= tam_Linhas_f || c < 0 || c >= tam_Colunas_f) {
                continue;
            }
            Coordenada atual(l,c);
            resultado += atual.toString();
            resultado += ": ";
            resultado += grelha[l][c].getDescricao();
            resultado += "\n";
        }
    }
    return resultado;
}

void Fabrica::desenhaPainel(Ecra &ecra, int lInicial, int cInicial, int altura) const {
    int largura = 30;
    ecra.moldura(lInicial, cInicial, altura, largura);

    int l = lInicial + 1;
    int c = cInicial + 2;

    ecra.escreve(l, c, "Instante: ");
    ecra.escreve(instante);

    ecra.escreve(l + 1, c, "Creditos: ");
    ecra.escreve(creditos);

    ecra.escreve(l + 2, c, "Maquinas: ");
    ecra.escreve(0); // ainda nao temos maquinas para o checkpoint1

    ecra.escreve(l + 3, c, "Engenheiros: ");
    ecra.escreve(0); // ainda nao temos engenheiros para o checkpoint1

    ecra.escreve(l + 5, c, "No ultimo instante: ");

}

Fabrica* Fabrica::carrega(const std::string& nomeFicheiro) {

    std::ifstream f(nomeFicheiro);

    if (!f) {
        return nullptr;
    }

    int nl, nc;

    if (!(f >> nl >> nc)) return nullptr;

    if (nl < 1 || nl > Settings::fabrica_max_linhas ||
        nc < 1 || nc > Settings::fabrica_max_colunas) {
        return nullptr;
    }

    // le e valida o mapa todo antes de criar a fabrica
    std::string linhas[Settings::fabrica_max_linhas];

    for (int l = 0; l < nl; l++) {
        if (!(f >> linhas[l])) return nullptr;

        if (static_cast<int>(linhas[l].size()) != nc) return nullptr;

        for (int c = 0; c < nc; c++) {
            char ch = linhas[l][c];
            if (ch != '.' && ch != '#' && ch != '%' && ch != '$' && ch != '~') {
                return nullptr;
            }
        }
    }

    Fabrica* fab = new Fabrica(nl, nc, false);

    for (int l = 0; l < nl; l++) {
        for (int c = 0; c < nc; c++) {
            switch (linhas[l][c]) {
                case '#':
                    fab->grelha[l][c].transformaEmCratera();
                    break;
                case '%':
                    fab->grelha[l][c].transformaEmDeposito(TipoTerreno::FERRO, fab->quantidadeAleatoria());
                    break;
                case '$':
                    fab->grelha[l][c].transformaEmDeposito(TipoTerreno::SILICIO, fab->quantidadeAleatoria());
                    break;
                case '~':
                    fab->grelha[l][c].transformaEmDeposito(TipoTerreno::GELO, fab->quantidadeAleatoria());
                    break;
                default: // '.' fica solo
                    break;
            }
        }
    }

    return fab;
}

int Fabrica::quantidadeAleatoria() const {
    int amplitude = Settings::deposito_quantidade_max - Settings::deposito_quantidade_min + 1;
    return Settings::deposito_quantidade_min + (rand() % amplitude);
}
