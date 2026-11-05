#ifndef POO_TP_2627_FABRICA_H
#define POO_TP_2627_FABRICA_H

#include <string>
#include "Ecra.h"
#include "Posicao.h"
#include "Settings.h"


class Fabrica {

    int tam_Linhas_f, tam_Colunas_f;           // tamanho da fabrica sem contar com a regua (ABC...) e os +2 espacos da moldura.
    int creditos;
    int instante;

    Posicao grelha[Settings::fabrica_max_linhas][Settings::fabrica_max_colunas];

    void colocaAleatorio(TipoTerreno tipo, int quantos);
    void geraElementosAleatorios(); // colocar as crateras e os depositos

   void desenhaPainel(Ecra &ecra, int lInicial, int cInicial, int altura) const;

public:
    Fabrica(int l, int c); // O nosso construtor pedido no Enunciado
    explicit Fabrica(const std::string &nomeFicheiro); // Construtor mas com recurso ao mapa do tal ficheiro indicado.
                                                       // 'explicit' obriga a escrever explicitamente quando queremos criar um objeto novo, evitando que o programa crie objetos por engano.
    void preparaEcra(Ecra &ecra, int lInicial = 0, int cInicial = 0) const;

   int getLinhas() const;
   int getColunas() const;

   int getCreditos() const;
   int getInstante() const;
   const Posicao& getPosicao(int l, int c) const;

   std::string listaPosicao(const std::string& lc, int raio = 0) const;

};

#endif //POO_TP_2627_FABRICA_H
