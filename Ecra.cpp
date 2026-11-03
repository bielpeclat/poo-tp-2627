//
// Created by gabriel-costa on 11/3/26.
//

#include "Settings.h"
#include "Ecra.h"

Ecra::Ecra(int linhas, int colunas) {
   // tratar sobre as linhas
   if (linhas < 1 || linhas > Settings::ecra_max_linhas) {
      nLinhas = Settings::ecra_max_linhas;
   } else {
      nLinhas = linhas;
   }

   // tratar sobre as colunas
   if (colunas < 1 || colunas > Settings::ecra_max_colunas) {
      nColunas = Settings::ecra_max_colunas;
   } else {
      nColunas = colunas;
   }

   // ja definimos o tamanho
   // vamos por tudo a 0 -> limpa()
   limpa();
}

void Ecra::limpa() {
   for (int i = 0; i < nLinhas; i++) {
      for (int j = 0; i < nColunas; j++) {

         buffer[i][j] = ' ';

      }
   }
   cursorL = 0;
   cursorC = 0;
}

void Ecra::posiciona(int l, int c) {

   // a linha esta nos limites do ecra?
   if (l < 0 || l > Settings::ecra_max_linhas - 1) {
      cursorL = 0;
   } else {
      cursorL = l;
   }

   // a coluna esta nos limites do ecra?
   if (c < 1 || c > Settings::ecra_max_colunas - 1) {
      cursorC = 0;
   } else {
      cursorC = c;
   }
}

void Ecra::escreve(char ch) {

   // a linha eh valida?
   if (cursorL == 0 || cursorL == nLinhas - 1) {
      cursorL = 1;
   }

}

void Ecra::moldura(int l, int c, int altura, int largura) {

   // inserir os 4 cantos

}
