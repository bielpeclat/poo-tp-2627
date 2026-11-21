#include <string>
#include <fstream>
#include <algorithm>   // std::max

#include "Fabrica.h"
#include "Ecra.h"
#include "Settings.h"
#include "Coordenada.h"
#include "Perfuradora.h"
#include "Transportador.h"
#include "Refinaria.h"
#include "Oficina.h"
#include "Lancador.h"
#include "Silo.h"

Fabrica::Fabrica(int l, int c, bool aleatoria) { // bool aleatoria necessária para caso a fabrica seja criada apartir de um mapa

    //ternários aninhados
    tam_Linhas_f = (l < 1) ? 1 : ((l > Settings::fabrica_max_linhas) ? Settings::fabrica_max_linhas : l);
    tam_Colunas_f = (c < 1) ? 1 : ((c > Settings::fabrica_max_colunas) ? Settings::fabrica_max_colunas : c);
    creditos = Settings::fabrica_creditos_iniciais;
    instante = 0;

    if (aleatoria) geraElementosAleatorios();
}

Fabrica::Fabrica(int l, int c) : Fabrica(l, c, true) {} // delegação

Fabrica::~Fabrica() {
    for (int l = 0; l < tam_Linhas_f; l++) {
        for (int c = 0; c < tam_Colunas_f; c++) {
            delete grelha[l][c].retiraMaquina();
        }
    }
}

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

            char simbolo = grelha[l][c].getCaracter(); // Terreno
            Maquina* m = grelha[l][c].getMaquina();
            if (m != nullptr) {
                simbolo = m->getCaracter(); // Máquina tapa o terreno
            }
            ecra.escreve(lInicial + 2 + l, cInicial + 2 + c, simbolo);
        }
    }

    int altPainel = std::max(altFabrica, alturaMinimaPainel);

    desenhaPainel(ecra, lInicial, cInicial + largFabrica + 1, altPainel);
}

void Fabrica::geraElementosAleatorios() {

    colocaAleatorio(TipoTerreno::CRATERA, Settings::fabrica_num_crateras);
    colocaAleatorio(TipoTerreno::FERRO, Settings::fabrica_num_depositos_ferro);
    colocaAleatorio(TipoTerreno::SILICIO, Settings::fabrica_num_depositos_silicio);
    colocaAleatorio(TipoTerreno::GELO, Settings::fabrica_num_depositos_gelo);
}

void Fabrica::colocaAleatorio(TipoTerreno tipo, int quantos) {

    int livres = 0; // contar quantos espaços livres temos

    for (int l = 0; l < tam_Linhas_f; l++) {
        for (int c = 0; c < tam_Colunas_f; c++) {
            if (grelha[l][c].getTerreno() == TipoTerreno::SOLO) {
                livres++;
            }
        }
    }
    if (quantos > livres) { // salvaguardar que existe sempre espaço para colocar tudo
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

std::string Fabrica::listaPosicao(const std::string& lc, int raio) const {

    if (!Coordenada::valida(lc, tam_Linhas_f, tam_Colunas_f)) {
        return "Posicao invalida: " + lc + "\n";
    }

    if (raio < 0) return "Raio invalido\n";

    Coordenada centro(lc); // assume que a string ja foi validada

    std::string resultado; // inicializado a ""

    for (int l = centro.getLinha() - raio; l <= centro.getLinha() + raio; l++) {
        for (int c = centro.getColuna() - raio; c <= centro.getColuna() + raio; c++) {
            if (l < 0 || l >= tam_Linhas_f || c < 0 || c >= tam_Colunas_f) {
                continue; // esta fora da grelha
            }

            // else
            Coordenada atual(l,c);
            resultado += atual.toString();
            resultado += ": ";
            resultado += grelha[l][c].getDescricao();

            Maquina* m = grelha[l][c].getMaquina();
            if (m != nullptr) {
                resultado += " | ";
                resultado += m->getNome();
                resultado += " (dir ";
                resultado += m->getLetraDirecao();
                resultado += "): ";
                resultado += m->getDescricao();
            }
            resultado += "\n";
        }
    }
    return resultado;
}

void Fabrica::desenhaPainel(Ecra &ecra, int lInicial, int cInicial, int altura) const {

    int largura = larguraPainel;
    ecra.moldura(lInicial, cInicial, altura, largura);

    int l = lInicial + 1;
    int c = cInicial + 2;

    ecra.escreve(l, c, "Instante: ");
    ecra.escreve(instante);

    ecra.escreve(l + 1, c, "Creditos: ");
    ecra.escreve(creditos);

    ecra.escreve(l + 2, c, "Maquinas: ");
    ecra.escreve(contaMaquinas());

    ecra.escreve(l + 3, c, "Engenheiros: ");
    ecra.escreve(0); // ainda nao temos engenheiros para o checkpoint1

    ecra.escreve(l + 5, c, "No ultimo instante: ");
    // Eventos do último instante
    int linhaFim = lInicial + altura - 1; // linha da moldura de baixo
    int cabem = linhaFim - (l + 6); // linhas livres para eventos
    int larguraTexto = largura - 4;
    int n = static_cast<int>(eventos.size());

    for (int i = 0; i < n && i < cabem; i++) {
        std::string texto = eventos[i];
        if (i == cabem - 1 && n > cabem) {
            texto = "... mais " + std::to_string(n - cabem + 1);   // nao cabem todos
        }
        ecra.escreve(l + 6 + i, c, texto.substr(0, larguraTexto));
    }

}

Fabrica* Fabrica::carrega(const std::string& nomeFicheiro) {

    std::ifstream f(nomeFicheiro);

    if (!f) return nullptr;

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

        if (static_cast<int>(linhas[l].size()) != nc) return nullptr; // size devolve size_t
        // tamanho errado -> (.size() != nc)

        for (int c = 0; c < nc; c++) {
            char ch = linhas[l][c];
            if (ch != '.' && ch != '#' && ch != '%' && ch != '$' && ch != '~') {
                return nullptr; // caracter invalido
            }
        }
    }

    Fabrica* fab = new Fabrica(nl, nc, false); // criar fabrica a partir do ficheiro (bool aleatorio = false)

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

int Fabrica::getAlturaEcra() const {
    return std::max(tam_Linhas_f + 3, alturaMinimaPainel);
}

int Fabrica::getLarguraEcra() const {
    return (tam_Colunas_f + 3) + 1 + larguraPainel;
}

// Funções para as máquinas
bool Fabrica::dentro(int l, int c) const {
    return l >= 0 && l < tam_Linhas_f && c >= 0 && c < tam_Colunas_f;
}

int Fabrica::contaMaquinas() const {
    int total = 0;
    for (int l = 0; l < tam_Linhas_f; l++) {
        for (int c = 0; c < tam_Colunas_f; c++) {
            if (grelha[l][c].getMaquina() != nullptr) {
                total++;
            }
        }
    }
    return total;
}

// cria a maquina do tipo indicado (p, t, r, o, s, l); nullptr se o tipo nao existir
Maquina* Fabrica::criaMaquina(char tipo, const Coordenada& pos, Direcao dir) {
    switch (tipo) {
        case 'p': return new Perfuradora(pos, dir);
        case 't': return new Transportador(pos, dir);
        case 'r': return new Refinaria(pos, dir);
        case 'o': return new Oficina(pos, dir);
        case 'l': return new Lancador(pos, dir);
        case 's': return new Silo(pos, dir);
        default:  return nullptr;
    }
}

bool Fabrica::compraMaquina(char tipo, const Coordenada& pos, Direcao dir, std::string& erro) {
    int l = pos.getLinha();
    int c = pos.getColuna();

    if (!dentro(l, c)) {
        erro = "Posicao fora da fabrica.";
        return false;
    }
    if (grelha[l][c].getTerreno() == TipoTerreno::CRATERA) {
        erro = "Nao se pode colocar uma maquina numa cratera.";
        return false;
    }
    if (grelha[l][c].getMaquina() != nullptr) {
        erro = "A posicao " + pos.toString() + " ja esta ocupada.";
        return false;
    }

    Maquina* nova = criaMaquina(tipo, pos, dir);
    if (nova == nullptr) {
        erro = "Tipo de maquina ainda nao disponivel.";
        return false;
    }
    if (nova->getCusto() > creditos) {
        erro = "Creditos insuficientes (custa " + std::to_string(nova->getCusto())
             + ", tem " + std::to_string(creditos) + ")";
        delete nova;                       // nao foi comprada: nao pode ficar perdida na memoria
        return false;
    }

    creditos -= nova->getCusto();
    grelha[l][c].colocaMaquina(nova);      // a partir daqui a Fabrica e dona da maquina
    return true;
}

bool Fabrica::vendeMaquina(const Coordenada& pos, std::string& erro) {
    int l = pos.getLinha();
    int c = pos.getColuna();

    if (!dentro(l, c) || grelha[l][c].getMaquina() == nullptr) {
        erro = "Nao existe nenhuma maquina em " + pos.toString();
        return false;
    }

    Maquina* m = grelha[l][c].retiraMaquina();
    creditos += m->getValorVenda();        // recebe 50% do custo
    delete m;                              // os itens que tinha dentro perdem-se (destrutor da maquina)
    return true;
}

bool Fabrica::rodaMaquina(const Coordenada& pos, Direcao dir, std::string& erro) {
    int l = pos.getLinha();
    int c = pos.getColuna();

    if (!dentro(l, c) || grelha[l][c].getMaquina() == nullptr) {
        erro = "Nao existe nenhuma maquina em " + pos.toString();
        return false;
    }

    grelha[l][c].getMaquina()->setDirecao(dir);
    return true;
}

Maquina* Fabrica::getMaquinaVizinha(const Coordenada& pos, Direcao dir) const {
    int l = pos.getLinha();
    int c = pos.getColuna();

    switch (dir) {
        case Direcao::CIMA:     l--; break;
        case Direcao::BAIXO:    l++; break;
        case Direcao::ESQUERDA: c--; break;
        case Direcao::DIREITA:  c++; break;
    }

    if (!dentro(l, c)) {
        return nullptr;                    // a vizinha estaria fora da fabrica
    }
    return grelha[l][c].getMaquina();
}

void Fabrica::registaEvento(const std::string& texto) {
    eventos.push_back(texto);
}

// Um instante: o tempo avanca e cada maquina atua uma vez.
// A regra "um item anda no maximo 1 posicao por instante" e garantida pelas maquinas:
// cada uma guarda o instante em que recebeu o item e so o entrega num instante posterior.
void Fabrica::avancaInstante() {
    instante++;
    eventos.clear();                       // o resumo e so do instante atual

    for (int l = 0; l < tam_Linhas_f; l++) {
        for (int c = 0; c < tam_Colunas_f; c++) {
            Maquina* m = grelha[l][c].getMaquina();
            if (m != nullptr) {
                m->atua(*this);
            }
        }
    }

    if (eventos.empty()) {
        eventos.push_back("Nada a assinalar.");
    }
}

std::string Fabrica::estado() const {
    std::string texto;
    texto += "Instante: " + std::to_string(instante) + "\n";
    texto += "Creditos: " + std::to_string(creditos) + "\n";

    texto += "Maquinas (" + std::to_string(contaMaquinas()) + "):\n";
    for (int l = 0; l < tam_Linhas_f; l++) {
        for (int c = 0; c < tam_Colunas_f; c++) {
            Maquina* m = grelha[l][c].getMaquina();
            if (m != nullptr) {
                texto += "  " + m->getPosicao().toString() + " " + m->getNome()
                       + " (dir " + m->getLetraDirecao() + "): " + m->getDescricao() + "\n";
            }
        }
    }

    texto += "Engenheiros: Nenhum\n";                      // entrega final
    texto += "Itens enviados para a Terra: Nenhum\n";      // entrega final (lancador)
    return texto;
}