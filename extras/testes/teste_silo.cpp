// Teste interno do Silo (NAO faz parte do projeto CLion nem do zip de entrega).
// No CP2 nao ha nenhuma maquina que produza itens, por isso inserimos os itens a mao.
//
// Como correr (a partir da pasta do projeto). O Silo usa Settings::silo_prob_perda,
// por isso o script compila 2 vezes, com a perda a 0% e a 100% (copia do Settings, o original nao e alterado):
//
//   bash extras/testes/corre_teste_silo.sh
//
// O programa devolve 0 se tudo passou.

#include <iostream>
#include <string>

#include "Fabrica.h"
#include "Silo.h"
#include "Gelo.h"
#include "Agua.h"
#include "PlacaFerro.h"
#include "Settings.h"

static int falhas = 0;

static void verifica(bool condicao, const std::string& descricao) {
   std::cout << (condicao ? "[ok]   " : "[FALHA] ") << descricao << "\n";
   if (!condicao) falhas++;
}

int main() {
   const bool semPerda = (Settings::silo_prob_perda == 0);
   const bool perdaTotal = (Settings::silo_prob_perda == 100);
   std::cout << "silo_prob_perda = " << Settings::silo_prob_perda << "\n";

   // Mapa fixo (sem crateras aleatorias): na linha c as posicoes ca..cg sao solo livre.
   // Silo em ca a enviar para a direita, 4 transportadores a seguir.
   Fabrica* ptr = Fabrica::carrega("mapas/mapa1.txt");
   if (ptr == nullptr) { std::cout << "correr a partir da pasta do projeto\n"; return 1; }
   Fabrica& fab = *ptr;
   std::string erro;
   verifica(fab.compraMaquina('s', Coordenada("ca"), Direcao::DIREITA, erro), "compra de um silo");
   for (char c = 'b'; c <= 'e'; c++) {
      std::string lc = std::string("c") + c;
      fab.compraMaquina('t', Coordenada(lc), Direcao::DIREITA, erro);
   }

   Silo* silo = dynamic_cast<Silo*>(fab.getPosicao(2, 0).getMaquina());
   verifica(silo != nullptr, "a maquina comprada com 's' e mesmo um Silo");
   if (silo == nullptr) return 1;

   verifica(silo->getCusto() == Settings::silo_custo && silo->getCaracter() == 'S', "custo e caracter do silo");
   verifica(silo->getQuantidade() == 0, "silo comeca vazio");

   // Sem limite de capacidade: 500 itens
   for (int i = 0; i < 500; i++) {
      silo->recebe(new Gelo(), 0);
   }
   verifica(silo->getQuantidade() == 500, "aceita 500 itens (sem limite de capacidade)");
   verifica(silo->aceita(nullptr) == false, "nao aceita nullptr");

   // Esvazia (o destrutor/atua libertam o que sobrar; a ordem FIFO testa-se mais abaixo)
   int instantes = 0;
   while (silo->getQuantidade() > 0 && instantes < 5000) {
      fab.avancaInstante();
      instantes++;
   }

   if (perdaTotal) {
      verifica(silo->getQuantidade() == 0, "com perda a 100% o silo perde um item por instante");
      verifica(instantes == 500, "com perda a 100% sao precisos exatamente 500 instantes para o esvaziar");
   }
   if (semPerda) {
      // Nao perde nunca; so o transportador final bloqueia, por isso o silo deve ficar com itens
      // quando a fila de transportadores enche (o silo acumula, e para isso que serve).
      verifica(silo->getQuantidade() > 0, "com perda a 0% nunca perde (acumula itens quando a fila enche)");
   }

   // Ordem: o mais antigo sai primeiro (so faz sentido sem perdas)
   if (semPerda) {
      Fabrica* ptr2 = Fabrica::carrega("mapas/mapa1.txt");
      Fabrica& f2 = *ptr2;
      f2.compraMaquina('s', Coordenada("ca"), Direcao::DIREITA, erro);
      f2.compraMaquina('t', Coordenada("cb"), Direcao::DIREITA, erro);
      Silo* s2 = dynamic_cast<Silo*>(f2.getPosicao(2, 0).getMaquina());
      s2->recebe(new Gelo(), 0);          // o mais antigo
      s2->recebe(new Agua(), 0);
      s2->recebe(new PlacaFerro(), 0);    // o mais recente
      Maquina* t = f2.getPosicao(2, 1).getMaquina();

      f2.avancaInstante();                // instante 1: o silo entrega o mais antigo
      verifica(t->getDescricao().find("Gelo") != std::string::npos, "1.o a sair e o mais antigo (Gelo)");
      verifica(s2->getQuantidade() == 2, "o silo ficou com 2 itens");

      // o item so anda 1 posicao por instante: no instante em que chegou ao transportador nao saiu de la
      f2.avancaInstante();                // instante 2: o transportador nao tem a quem entregar (bloqueado)
      verifica(s2->getQuantidade() == 2, "transportador ocupado: o silo mantem os restantes itens");
      delete ptr2;
   }

   // vende com itens dentro: nao pode haver fugas (verificar com -fsanitize=address)
   std::string e2;
   fab.vendeMaquina(Coordenada("ca"), e2);
   delete ptr;

   std::cout << (falhas == 0 ? "TUDO OK\n" : "HOUVE FALHAS\n");
   return falhas == 0 ? 0 : 1;
}
