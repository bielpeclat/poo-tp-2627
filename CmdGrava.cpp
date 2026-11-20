#include "CmdGrava.h"

#include <iostream>

CmdGrava::CmdGrava() : Comando("grava", "grava <nome>") {}

std::string CmdGrava::getAjuda() const {
   return "Sintaxe: grava <nome>\n"
          "Parametros: nome - nome a associar a copia\n"
          "Efeito: guarda em memoria uma copia da fabrica e de tudo o que nela existe; a associacao engenheiros-maquinas nao e guardada; se ja existir uma copia com esse nome, e substituida\n"
          "Falha: se tiver mais ou menos de um parametro\n"
          "Exemplo: grava antes\n";
}

bool CmdGrava::valida(const std::vector<std::string>& args, std::string& erro) const {
   if (!verificaNumArgs(args, 1, 1, erro))
      return false;

   return true;
}

void CmdGrava::executa(Simulador&, const std::vector<std::string>&) {
   std::cout << "grava: disponivel na entrega final\n";
}
