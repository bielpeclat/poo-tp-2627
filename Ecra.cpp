//
// Created by gabriel-costa on 11/3/26.
//

#include <iostream>
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

int Ecra::getLinhas() const {
   return nLinhas;
}

int Ecra::getColunas() const {
   return nColunas;
}

void Ecra::limpa() {
   for (int i = 0; i < nLinhas; i++) {
      for (int j = 0; j < nColunas; j++) {

         buffer[i][j] = '*'; // mudar futuramente

      }
   }
   cursorL = 0;
   cursorC = 0;
}

void Ecra::posiciona(int l, int c) {

   // a posicao esta nos limites do ecra?
   if ((l < 0 || l > nLinhas - 1) ||
       (c < 0 || c > nColunas - 1)) {
      cursorL = -1;
      cursorC = -1;
   } else {
      cursorL = l;
      cursorC = c;
   }

}

void Ecra::escreve(char ch) {

   //  o cursor esta dentro do ecra?
   if (cursorL < 0 || cursorL >= nLinhas ||
       cursorC < 0 || cursorC >= nColunas) {
      return;
   }

   // a linha eh valida!
   buffer[cursorL][cursorC] = ch;
   cursorC++;
   if (cursorC == nColunas - 1) { // fim das colunas
      cursorL++;
      if (cursorL == nLinhas - 1) { // fim das linhas
         return;
      }

      cursorC = 0;
   }
}

void Ecra::moldura(int l, int c, int altura, int largura) {

   // inserir os 4 cantos

}

void Ecra::mostra() const {
   for (int i = 0; i < nLinhas; i++) {
      for (int j = 0; j < nColunas; j++) {

         std::cout << buffer[i][j];

      }
      std::cout << '\n';
   }
}

