#include "CmdEstado.h"

#include "Simulador.h"
#include "Fabrica.h"
#include <iostream>

CmdEstado::CmdEstado() : Comando("estado", "estado") {}

std::string CmdEstado::getAjuda() const {
   return "Sintaxe: estado\n"
          "Parametros: nenhum\n"
          "Efeito: apresenta o instante atual, os creditos, as maquinas, os engenheiros e o total de itens enviados para a Terra, de cada tipo\n"
          "Falha: se for escrito com algum parametro\n"
          "Exemplo: estado\n";
}

bool CmdEstado::valida(const std::vector<std::string>& args, std::string& erro) const {
   if (!verificaNumArgs(args, 0, 0, erro))
      return false;

   return true;
}

void CmdEstado::executa(Simulador& sim, const std::vector<std::string>&) {
   std::cout << sim.getFabrica().estado();
}
