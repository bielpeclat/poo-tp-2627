#include "CmdRoda.h"

#include <iostream>

CmdRoda::CmdRoda() : Comando("roda", "roda <lc> <dir>") {}

std::string CmdRoda::getAjuda() const {
   return "Sintaxe: roda <lc> <dir>\n"
          "Parametros: lc - posicao da fabrica onde esta a maquina; dir - nova direcao de saida: c, b, e ou d (cima, baixo, esquerda, direita)\n"
          "Efeito: muda a direcao de saida da maquina que se encontra na posicao indicada\n"
          "Falha: se nao existir maquina na posicao\n"
          "Exemplo: roda ce b\n";
}

bool CmdRoda::valida(const std::vector<std::string>& args, std::string& erro) const {
   if (!verificaNumArgs(args, 2, 2, erro))
      return false;

   if (!eFormatoPosicao(args[0])) {
      erro = "posicao invalida (esperado duas letras minusculas, ex: ce)";
      return false;
   }

   if (!eDirecao(args[1])) {
      erro = "direcao invalida (esperado c, b, e ou d)";
      return false;
   }

   return true;
}

// provisorio: sera ligado a Fabrica quando o contrato do Filipe estiver publicado
void CmdRoda::executa(Simulador&, const std::vector<std::string>&) {
   std::cout << "roda: ainda nao ligado a fabrica\n";
}
