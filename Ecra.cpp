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
   cursorL = 0; // O nosso rato para escrever.
   cursorC = 0;
}

void Ecra::posiciona(int l, int c) {

   // verificação - a posicao esta nos limites do ecra?
   if ((l < 0 || l >= nLinhas) ||
       (c < 0 || c >= nColunas)) {
      cursorL = -1;  // acaba por não escrever nada por causa da função escreve que retorna nada;
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
   cursorC++; // em caso da função ser chamada denovo.
   if (cursorC >= nColunas) { // fim das colunas -  Passa pra posição 0 da próxima linha
      cursorC = 0;
      cursorL++;
   }
}

void Ecra::escreve(const std::string &texto) { // Talvez futuramente.
   for (size_t i = 0; i < texto.length(); i++) { // .lenth() retorna size_t
      escreve(texto[i]);
   }
}

void Ecra::escreve(int l, int c, const std::string &texto) { // Talvez futuramente.
   posiciona(l, c);
   escreve(texto);
}

void Ecra::escreve(int i) { // Assume a posição onde o cursor já se encontra.
   escreve(std::to_string(i));
}

void Ecra::escreve(int l, int c, char ch) {
   posiciona(l, c);
   escreve(ch);
}

void Ecra::moldura(int l, int c, int altura, int largura) {

   // inserir os 4 cantos
   escreve(l,c,'+'); // canto superior esquerdo
   escreve(l, c + largura - 1, '+'); // canto superior direito
   escreve(l + altura - 1, c, '+'); // canto inferior esquerdo
   escreve(l + altura - 1, c + largura - 1, '+'); // canto inferior direito

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

