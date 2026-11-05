#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

#include "Settings.h"
#include "Ecra.h"
#include "Biblioteca.h"
#include "Posicao.h"
#include "Coordenada.h"
#include "Fabrica.h"

// Testes do checkpoint 1: cada cenario numa funcao, com pausa entre eles

void titulo(const std::string &texto) {
    std::cout << "\n========== " << texto << " ==========\n\n";
}

// ---------- Ecra ----------

void testaEcra() {
    titulo("ECRA: moldura, escrita e limites");

    Ecra e(7, 20);
    e.moldura(0, 0, 5, 20);
    e.escreve(1, 2, "Ola Marte");
    e.escreve(2, 2, 'X');
    e.posiciona(3, 2);
    e.escreve(1234);

    // escritas fora dos limites: devem ser ignoradas, sem erros
    e.escreve(10, 10, "fora");
    e.escreve(-1, 0, 'Z');

    // texto que passa do fim da linha continua na linha de baixo
    e.escreve(5, 15, "ABCDEFGH");

    e.mostra();
    std::cout << "Esperado: 'Ola Marte', 'X' e '1234' dentro da moldura;\n"
              << "por baixo, 'ABCDE' no fim de uma linha e 'FGH' no inicio da seguinte.\n";
}

// ---------- Posicao ----------

void testaPosicao() {
    titulo("POSICAO: terreno isolado");

    Posicao p;
    std::cout << "Nova:              " << p.getDescricao() << " ['" << p.getCaracter() << "']\n";

    p.transformaEmCratera();
    std::cout << "Cratera:           " << p.getDescricao() << " ['" << p.getCaracter() << "']\n";

    p.transformaEmDeposito(TipoTerreno::SILICIO, 2);
    std::cout << "Deposito:          " << p.getDescricao() << " ['" << p.getCaracter() << "']\n";

    p.removeUnidade();
    std::cout << "Remove 1 unidade:  " << p.getDescricao() << "\n";

    p.removeUnidade();
    std::cout << "Remove a ultima:   " << p.getDescricao() << " (esgotado passa a solo)\n";
}

// ---------- Coordenada ----------

void testaCoordenada() {
    titulo("COORDENADA: validacao numa fabrica 12x20");

    const std::string casos[] = {"aa", "lt", "ce", "ma", "au", "", "a", "abc", "a1", "CE"};

    for (const std::string &txt : casos) {
        std::cout << "\"" << txt << "\" -> ";
        if (Coordenada::valida(txt, 12, 20)) {
            Coordenada c(txt);
            std::cout << "valida (linha " << c.getLinha() << ", coluna " << c.getColuna()
                      << ", toString \"" << c.toString() << "\")\n";
        } else {
            std::cout << "invalida\n";
        }
    }
    std::cout << "\nEsperado: aa, lt e ce validas; todas as outras invalidas.\n";
}

// ---------- Fabrica ----------

void mostraFabrica(const Fabrica &f) {
    Ecra e;
    f.preparaEcra(e);
    e.mostra();
}

void listaDepositos(const Fabrica &f) {
    int total = 0;
    for (int l = 0; l < f.getLinhas(); l++) {
        for (int c = 0; c < f.getColunas(); c++) {
            if (f.getPosicao(l, c).eDeposito()) {
                Coordenada coord(l, c);
                std::cout << coord.toString() << ": " << f.getPosicao(l, c).getDescricao() << "\n";
                total++;
            }
        }
    }
    std::cout << "Total de depositos: " << total << "\n";
}

void testaFabrica(int linhas, int colunas, const std::string &descricao) {
    titulo("FABRICA " + std::to_string(linhas) + "x" + std::to_string(colunas) + ": " + descricao);

    Fabrica f(linhas, colunas);
    std::cout << "Tamanho efetivo: " << f.getLinhas() << "x" << f.getColunas() << "\n";
    mostraFabrica(f);
}

void testaFabricaNormal() {
    titulo("FABRICA 10x10: normal, com lista de depositos");

    Fabrica f(10, 10);
    mostraFabrica(f);
    listaDepositos(f);
    std::cout << "Esperado: "
              << Settings::fabrica_num_depositos_ferro + Settings::fabrica_num_depositos_silicio
                 + Settings::fabrica_num_depositos_gelo
              << " depositos, cada um entre " << Settings::deposito_quantidade_min
              << " e " << Settings::deposito_quantidade_max << " unidades.\n";
}

// ---------- lposicao ----------

void testaLposicao() {
    titulo("LPOSICAO (terreno) numa fabrica 10x10");

    Fabrica f(10, 10);
    mostraFabrica(f);

    struct Caso {
        std::string lc;
        int raio;
        std::string esperado;
    };
    const Caso casos[] = {
        {"aa", 0, "1 posicao"},
        {"ee", 1, "9 posicoes, de dd a ff"},
        {"aa", 1, "4 posicoes (canto)"},
        {"jj", 1, "4 posicoes (canto oposto)"},
        {"zz", 0, "posicao invalida"},
        {"ka", 0, "posicao invalida (linha k nao existe)"},
        {"ee", -1, "raio invalido"},
    };

    for (const Caso &caso : casos) {
        std::cout << "--- lposicao " << caso.lc << " " << caso.raio
                  << "  (esperado: " << caso.esperado << ") ---\n";
        std::cout << f.listaPosicao(caso.lc, caso.raio) << "\n";
    }
}

// ---------- main ----------

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    std::cout << "Simulador de fabrica em Marte - testes do checkpoint 1\n";

    testaEcra();
    aguardaEnter();

    testaPosicao();
    aguardaEnter();

    testaCoordenada();
    aguardaEnter();

    testaFabricaNormal();
    aguardaEnter();

    testaFabrica(4, 4, "pequena, deve encher sem bloquear");
    aguardaEnter();

    testaFabrica(26, 26, "tamanho maximo, painel completo");
    aguardaEnter();

    testaFabrica(3, 15, "retangular, mais larga que alta");
    aguardaEnter();

    testaFabrica(1, 1, "minima");
    aguardaEnter();

    testaFabrica(0, 40, "valores fora dos limites, devem ser corrigidos para 1x26");
    aguardaEnter();

    testaLposicao();

    return 0;
}
