#include "CmdFabrica.h"
#include "Simulador.h"
#include "Fabrica.h"
#include "Settings.h"

#include <iostream>

CmdFabrica::CmdFabrica() : Comando("fabrica", "fabrica <nl> <nc>") {}

std::string CmdFabrica::getAjuda() const {
   return "Sintaxe: fabrica <nl> <nc>\n"
          "Parametros: nl - numero de linhas (1 a 26); nc - numero de colunas (1 a 26)\n"
          "Efeito: cria a fabrica com o tamanho indicado, com crateras e depositos em posicoes aleatorias\n"
          "Falha: se a fabrica ja existir, se os parametros nao forem inteiros entre 1 e 26 ou se houver parametros a mais ou a menos\n"
          "Exemplo: fabrica 12 20\n";
}

bool CmdFabrica::precisaFabrica() const {
   return false;
}

bool CmdFabrica::valida(const std::vector<std::string>& args, std::string& erro) const {
   if (!verificaNumArgs(args, 2, 2, erro))
      return false;

   if (!eInteiro(args[0]) || !eInteiro(args[1])) {
      erro = "o numero de linhas e de colunas tem de ser inteiro";
      return false;
   }

   int nl = std::stoi(args[0]);
   int nc = std::stoi(args[1]);

   if (nl < 1 || nl > Settings::fabrica_max_linhas) {
      erro = "o numero de linhas tem de estar entre 1 e " + std::to_string(Settings::fabrica_max_linhas);
      return false;
   }

   if (nc < 1 || nc > Settings::fabrica_max_colunas) {
      erro = "o numero de colunas tem de estar entre 1 e " + std::to_string(Settings::fabrica_max_colunas);
      return false;
   }

   return true;
}

void CmdFabrica::executa(Simulador& sim, const std::vector<std::string>& args) {
   if (sim.temFabrica()) {
      std::cout << "A fabrica ja foi criada\n";
      return;
   }

   int nl = std::stoi(args[0]);
   int nc = std::stoi(args[1]);

   sim.defineFabrica(new Fabrica(nl, nc));
   sim.mostraEcra();
}
