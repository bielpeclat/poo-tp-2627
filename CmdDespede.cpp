#include "CmdDespede.h"

#include <iostream>

CmdDespede::CmdDespede() : Comando("despede", "despede <id>") {}

std::string CmdDespede::getAjuda() const {
   return "Sintaxe: despede <id>\n"
          "Parametros: id - numero do engenheiro\n"
          "Efeito: envia o engenheiro para a Terra; deixa de fazer parte da fabrica e de receber salario\n"
          "Falha: se nao existir engenheiro com esse id\n"
          "Exemplo: despede 2\n";
}

bool CmdDespede::valida(const std::vector<std::string>& args, std::string& erro) const {
   if (!verificaNumArgs(args, 1, 1, erro))
      return false;

   if (!eInteiro(args[0])) {
      erro = "o id tem de ser um inteiro";
      return false;
   }

   return true;
}

void CmdDespede::executa(Simulador&, const std::vector<std::string>&) {
   std::cout << "despede: disponivel na entrega final\n";
}
