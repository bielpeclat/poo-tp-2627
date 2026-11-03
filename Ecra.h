//
// Created by gabriel-costa on 11/3/26.
//

#ifndef POO_TP_2627_ECRA_H
#define POO_TP_2627_ECRA_H

#include "Settings.h"
#include <string>

class Ecra {
   char buffer[Settings::ecra_max_linhas][Settings::ecra_max_colunas];
   int nLinhas, nColunas;           // tam que vamos usar
   int cursorL, cursorC;            // cursor virtual
public:
   Ecra(int linhas = Settings::ecra_max_linhas, int colunas = Settings::ecra_max_colunas);

   int getLinhas() const;
   int getColunas() const;

   void limpa(); // por todas as posicoes com '', cursor em (0,0)
   void posiciona(int l, int c);       // move o cursor
   void escreve(char ch); // escreve na posicao cursor
   void escreve(const std::string &texto); // escreve na posicao cursor
   void escreve(int l, int c, const std::string &texto); // primeiro posiciona, depois escreve
   void escreve(int l, int c, char ch);
   void moldura(int l, int c, int altura, int largura);
   void mostra() const; // envia tudo para o cout
};

#endif //POO_TP_2627_ECRA_H