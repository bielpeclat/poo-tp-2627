#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

#include "Ecra.h"
#include "Biblioteca.h"
#include "Coordenada.h"
#include "Fabrica.h"

void mostraFabrica(const Fabrica &f) {
    Ecra e;
    f.preparaEcra(e);
    e.mostra();
}

void demoEcra() {
    Ecra e(7, 20);
    e.moldura(0, 0, 5, 20);
    e.escreve(1, 2, "Ola Marte");
    e.escreve(2, 2, 'X');
    e.posiciona(3, 2);
    e.escreve(1234);
    e.escreve(10, 10, "fora do ecra");
    e.escreve(5, 15, "ABCDEFGH");
    e.mostra();
}

void demoCoordenada() {
    const std::string casos[] = {"aa", "ce", "lt", "ma", "a1", "abc"};

    for (const std::string &txt : casos) {
        std::cout << txt << ": ";
        if (Coordenada::valida(txt, 12, 20)) {
            Coordenada c(txt);
            std::cout << "linha " << c.getLinha() << ", coluna " << c.getColuna() << "\n";
        } else {
            std::cout << "invalida\n";
        }
    }
}

void demoFabrica(int linhas, int colunas) {
    Fabrica f(linhas, colunas);
    mostraFabrica(f);
}

void demoLposicao() {
    Fabrica f(10, 10);
    mostraFabrica(f);

    std::cout << "lposicao ee\n" << f.listaPosicao("ee") << "\n";
    std::cout << "lposicao ee 1\n" << f.listaPosicao("ee", 1) << "\n";
    std::cout << "lposicao aa 1\n" << f.listaPosicao("aa", 1) << "\n";
    std::cout << "lposicao zz\n" << f.listaPosicao("zz") << "\n";
}

void demoCarrega(const std::string &nome) {
    std::cout << "carrega " << nome << "\n";

    Fabrica *f = Fabrica::carrega(nome);
    if (f == nullptr) {
        std::cout << "Ficheiro invalido ou inexistente\n";
        return;
    }

    mostraFabrica(*f);
    delete f;
}

void terminaSimulacao(Fabrica *&f) {
    delete f;
    f = nullptr;
    std::cout << "Simulacao terminada\n";
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    demoEcra();
    aguardaEnter();

    demoCoordenada();
    aguardaEnter();

    demoFabrica(10, 10);
    aguardaEnter();

    demoFabrica(4, 4);
    aguardaEnter();

    demoFabrica(26, 26);
    aguardaEnter();

    demoLposicao();
    aguardaEnter();

    demoCarrega("./mapas/mapa1.txt");
    aguardaEnter();

    demoCarrega("./mapas/mapa_erro_char.txt");
    demoCarrega("./mapas/mapa_erro_tam.txt");
    demoCarrega("./mapas/naoexiste.txt");
    aguardaEnter();

    Fabrica *atual = Fabrica::carrega("./mapas/mapa1.txt");
    if (atual == nullptr) {
        atual = new Fabrica(10, 10);
    }
    mostraFabrica(*atual);

    terminaSimulacao(atual);

    return 0;
}
