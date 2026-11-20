#include "CmdCarrega.h"
#include "Simulador.h"
#include "Fabrica.h"

#include <iostream>

CmdCarrega::CmdCarrega() : Comando("carrega", "carrega <nome-do-ficheiro>") {}

std::string CmdCarrega::getAjuda() const {
   return "Sintaxe: carrega <nome-do-ficheiro>\n"
          "Parametros: nome-do-ficheiro - ficheiro com o mapa (1a linha: linhas e colunas; depois o mapa com . solo, # cratera, % ferro, $ silicio, ~ gelo)\n"
          "Efeito: cria a fabrica a partir do mapa descrito no ficheiro\n"
          "Falha: se a fabrica ja existir, se o ficheiro nao existir, se o mapa nao respeitar o formato ou se nao tiver exatamente um parametro\n"
          "Exemplo: carrega mapas/mapa1.txt\n";
}

bool CmdCarrega::precisaFabrica() const {
   return false;
}

bool CmdCarrega::valida(const std::vector<std::string>& args, std::string& erro) const {
   return verificaNumArgs(args, 1, 1, erro);
}

void CmdCarrega::executa(Simulador& sim, const std::vector<std::string>& args) {
   if (sim.temFabrica()) {
      std::cout << "A fabrica ja foi criada\n";
      return;
   }

   Fabrica* f = Fabrica::carrega(args[0]);
   if (f == nullptr) {
      std::cout << "Ficheiro inexistente ou mapa invalido: " << args[0] << "\n";
      return;
   }

   sim.defineFabrica(f);
   sim.mostraEcra();
}
