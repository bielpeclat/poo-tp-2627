#include "CmdContrata.h"

#include <iostream>

CmdContrata::CmdContrata() : Comando("contrata", "contrata <nome>") {}

std::string CmdContrata::getAjuda() const {
   return "Sintaxe: contrata <nome>\n"
          "Parametros: nome - nome do engenheiro a contratar (pode ser repetido; o id e gerado automaticamente)\n"
          "Efeito: contrata um novo engenheiro com o nome indicado, que fica livre\n"
          "Falha: se nao houver creditos suficientes\n"
          "Exemplo: contrata joaquim\n";
}

bool CmdContrata::valida(const std::vector<std::string>& args, std::string& erro) const {
   if (!verificaNumArgs(args, 1, 1, erro))
      return false;

   return true;
}

void CmdContrata::executa(Simulador&, const std::vector<std::string>&) {
   std::cout << "contrata: disponivel na entrega final\n";
}
