#include "CmdVende.h"

#include <iostream>

CmdVende::CmdVende() : Comando("vende", "vende <lc>") {}

std::string CmdVende::getAjuda() const {
   return "Sintaxe: vende <lc>\n"
          "Parametros: lc - posicao da fabrica onde esta a maquina\n"
          "Efeito: vende a maquina que se encontra na posicao indicada; os itens que ela tiver perdem-se e sao devolvidos 50% do custo\n"
          "Falha: se nao existir maquina na posicao\n"
          "Exemplo: vende ce\n";
}

bool CmdVende::valida(const std::vector<std::string>& args, std::string& erro) const {
   if (!verificaNumArgs(args, 1, 1, erro))
      return false;

   if (!eFormatoPosicao(args[0])) {
      erro = "posicao invalida (esperado duas letras minusculas, ex: ce)";
      return false;
   }

   return true;
}

// provisorio: sera ligado a Fabrica quando o contrato do Filipe estiver publicado
void CmdVende::executa(Simulador&, const std::vector<std::string>&) {
   std::cout << "vende: ainda nao ligado a fabrica\n";
}
