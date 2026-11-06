#include <iostream>
#include <string>
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
      for (int j = 0; j < nColunas; j++) {

         buffer[i][j] = ' ';

      }
   }
   cursorL = 0;
   cursorC = 0;
}

void Ecra::posiciona(int l, int c) {

   // a posicao esta nos limites do ecra?
   if ((l < 0 || l >= nLinhas) ||
       (c < 0 || c >= nColunas)) {
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
   if (cursorC >= nColunas) { // fim das colunas
      cursorC = 0;
      cursorL++;
   }
}

void Ecra::escreve(const std::string &texto) {
   for (size_t i = 0; i < texto.length(); i++) { // .lenth() retorna size_t
      escreve(texto[i]);
   }
}

void Ecra::escreve(int l, int c, const std::string &texto) {
   posiciona(l, c);
   escreve(texto);
}

void Ecra::escreve(int i) {
   escreve(std::to_string(i));
}

void Ecra::escreve(int l, int c, char ch) {
   posiciona(l, c);
   escreve(ch);
}

void Ecra::moldura(int l, int c, int altura, int largura) {

   // inserir os 4 cantos
   escreve(l,c,'+');
   escreve(l, c + largura - 1, '+');
   escreve(l + altura - 1, c, '+');
   escreve(l + altura - 1, c + largura - 1, '+');

   // inserir as linhas horizontais
   for (int i = c + 1; i < c + largura - 1; i++) {
      escreve(l, i, '-');
      escreve(l+altura-1, i, '-');
   }

   // inserir as linhas verticas
   for (int i = l + 1; i < l + altura - 1; i++) {
      escreve(i, c, '|');
      escreve(i, c + largura - 1, '|');
   }
}

void Ecra::mostra() const {
   for (int i = 0; i < nLinhas; i++) {
      for (int j = 0; j < nColunas; j++) {

         std::cout << buffer[i][j];

      }
      std::cout << '\n';
   }
}

