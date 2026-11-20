#include "CmdAtribui.h"

#include <iostream>

CmdAtribui::CmdAtribui() : Comando("atribui", "atribui <id> <lc>") {}

std::string CmdAtribui::getAjuda() const {
   return "Sintaxe: atribui <id> <lc>\n"
          "Parametros: id - numero do engenheiro; lc - posicao da fabrica onde esta a maquina\n"
          "Efeito: atribui o engenheiro a maquina que se encontra na posicao indicada; se estava noutra maquina, deixa de estar e passa para a nova\n"
          "Falha: se nao existir engenheiro com esse id ou se nao existir maquina na posicao\n"
          "Exemplo: atribui 2 hr\n";
}

bool CmdAtribui::valida(const std::vector<std::string>& args, std::string& erro) const {
   if (!verificaNumArgs(args, 2, 2, erro))
      return false;

   if (!eInteiro(args[0])) {
      erro = "o id tem de ser um inteiro";
      return false;
   }

   if (!eFormatoPosicao(args[1])) {
      erro = "posicao invalida (esperado duas letras minusculas, ex: hi)";
      return false;
   }

   return true;
}

void CmdAtribui::executa(Simulador&, const std::vector<std::string>&) {
   std::cout << "atribui: disponivel na entrega final\n";
}
