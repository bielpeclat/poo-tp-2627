#include "CmdRecupera.h"

#include <iostream>

CmdRecupera::CmdRecupera() : Comando("recupera", "recupera <nome>") {}

std::string CmdRecupera::getAjuda() const {
   return "Sintaxe: recupera <nome>\n"
          "Parametros: nome - nome da copia a recuperar\n"
          "Efeito: a fabrica passa a ser como era quando a copia foi feita; os engenheiros ficam livres; a copia nao e eliminada\n"
          "Falha: se nao existir copia com esse nome\n"
          "Exemplo: recupera antes\n";
}

bool CmdRecupera::valida(const std::vector<std::string>& args, std::string& erro) const {
   if (!verificaNumArgs(args, 1, 1, erro))
      return false;

   return true;
}

void CmdRecupera::executa(Simulador&, const std::vector<std::string>&) {
   std::cout << "recupera: disponivel na entrega final\n";
}
