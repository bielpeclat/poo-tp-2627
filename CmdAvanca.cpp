#include "CmdAvanca.h"

#include <iostream>

CmdAvanca::CmdAvanca() : Comando("avanca", "avanca [n]") {}

std::string CmdAvanca::getAjuda() const {
   return "Sintaxe: avanca [n]\n"
          "Parametros: n (opcional) - numero de instantes a avancar, inteiro positivo; se nao for indicado, assume 1\n"
          "Efeito: avanca n instantes, um de cada vez; em cada instante as maquinas atuam e o ecra e apresentado\n"
          "Falha: se n nao for um inteiro positivo ou se houver mais de um parametro\n"
          "Exemplo: avanca 10\n";
}

bool CmdAvanca::valida(const std::vector<std::string>& args, std::string& erro) const {
   if (!verificaNumArgs(args, 0, 1, erro))
      return false;

   if (args.size() == 1) {
      if (!eInteiro(args[0])) {
         erro = "o numero de instantes tem de ser um inteiro";
         return false;
      }
      if (std::stoi(args[0]) < 1) {
         erro = "o numero de instantes tem de ser positivo";
         return false;
      }
   }

   return true;
}

// provisorio: sera ligado a Fabrica quando o contrato do Filipe estiver publicado
void CmdAvanca::executa(Simulador&, const std::vector<std::string>&) {
   std::cout << "avanca: ainda nao ligado a fabrica\n";
}
