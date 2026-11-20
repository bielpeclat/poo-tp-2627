//
// Created by gabriel-costa on 11/20/26.
//

#include "CmdExecuta.h"
#include "Simulador.h"

#include <iostream>

CmdExecuta::CmdExecuta() : Comando("executa", "executa <nome-do-ficheiro>") {}

std::string CmdExecuta::getAjuda() const {
   return "Sintaxe: executa <nome-do-ficheiro>\n"
          "Parametros: nome-do-ficheiro - ficheiro de texto com um comando por linha\n"
          "Efeito: le e executa os comandos do ficheiro, como se fossem escritos no teclado\n"
          "Falha: se nao tiver exatamente um parametro, se o ficheiro nao existir, ou se ja estiver a decorrer um executa\n"
          "Exemplo: executa teste1.txt\n";
}

bool CmdExecuta::precisaFabrica() const {
   return false;
}

bool CmdExecuta::valida(const std::vector<std::string>& args, std::string& erro) const {
   return verificaNumArgs(args, 1, 1, erro);
}

void CmdExecuta::executa(Simulador& sim, const std::vector<std::string>& args) {
   if (sim.estaAExecutarFicheiro()) {
      std::cout << "Nao e possivel usar executa dentro de um ficheiro executado\n";
      return;
   }

   if (!sim.executaFicheiro(args[0])) {
      std::cout << "Falha ao executar o ficheiro: " << args[0] << "\n";
   }
}