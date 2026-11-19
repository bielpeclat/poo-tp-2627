//
// Created by gabriel-costa on 11/19/26.
//

#include "CmdFim.h"
#include "Simulador.h"

CmdFim::CmdFim() : Comando("fim", "fim") {}

std::string CmdFim::getAjuda() const {
   return "Sintaxe: fim\n"
          "Parametros: nenhum\n"
          "Efeito: encerra o programa e liberta todos os recursos (fabrica, comandos, etc.)\n"
          "Falha: se for escrito com algum parametro\n"
          "Exemplo: fim\n";
}

bool CmdFim::precisaFabrica() const {
   return false;
}

bool CmdFim::valida(const std::vector<std::string> &args, std::string &erro) const {
   return verificaNumArgs(args, 0, 0, erro);
}

void CmdFim::executa(Simulador &sim, const std::vector<std::string> &) {
   sim.termina();
}

