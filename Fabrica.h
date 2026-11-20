#ifndef POO_TP_2627_FABRICA_H
#define POO_TP_2627_FABRICA_H

#include <string>
#include <vector>
#include "Ecra.h"
#include "Posicao.h"
#include "Settings.h"
#include "Maquina.h"


class Fabrica {

    int tam_Linhas_f, tam_Colunas_f;  // tamanho da fabrica sem contar com a regua (ABC...) e os +2 espacos da moldura.
    int creditos;
    int instante;

   Posicao grelha[Settings::fabrica_max_linhas][Settings::fabrica_max_colunas];
   void colocaAleatorio(TipoTerreno tipo, int quantos);
   void geraElementosAleatorios(); // colocar as crateras e os depositos

   void desenhaPainel(Ecra &ecra, int lInicial, int cInicial, int altura) const;

   int quantidadeAleatoria() const;

    std::vector<std::string> eventos;   // resumo do ultimo instante (para o painel)

    // Funções de apoio
    bool dentro(int l, int c) const; // (l,c) esta dentro da fabrica?
    int contaMaquinas() const;
    static Maquina* criaMaquina(char tipo, const Coordenada& pos, Direcao dir);

   Fabrica(int l, int c, bool aleatoria);


public:
    Fabrica(int l, int c); // O nosso construtor pedido no Enunciado
    // esse construtor tem posicoes aleatorias (delegacao para outro construtor)

    ~Fabrica(); // Para apagar todas as máquinas
    Fabrica(const Fabrica&) = delete;
    Fabrica& operator=(const Fabrica&) = delete;

    static Fabrica* carrega(const std::string& nomeFicheiro);
    void preparaEcra(Ecra &ecra, int lInicial = 0, int cInicial = 0) const;

   int getLinhas() const {return tam_Linhas_f;}
   int getColunas() const {return tam_Colunas_f;}

   int getCreditos() const {return creditos;}
   int getInstante() const {return instante;}
   const Posicao& getPosicao(int l, int c) const {return grelha[l][c];}

   std::string listaPosicao(const std::string& lc, int raio = 0) const;

    bool compraMaquina(char tipo, const Coordenada& pos, Direcao dir, std::string& erro);
    bool vendeMaquina(const Coordenada& pos, std::string& erro);
    bool rodaMaquina(const Coordenada& pos, Direcao dir, std::string& erro);

    void avancaInstante();        // Instante: maquinas atuam e guarda-se o resumo
    std::string estado() const;   // texto do comando estado

    void registaEvento(const std::string& texto); // Cada máquina anuncia o que aconteceu
    Maquina* getMaquinaVizinha(const Coordenada& pos, Direcao dir) const; // Transportador precisa
    // de perguntar à fábrica que máquina está ao seu lado, na sua direção.

};

#endif //POO_TP_2627_FABRICA_H
