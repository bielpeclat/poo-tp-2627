#include "CmdRoda.h"

#include "Simulador.h"
#include "Fabrica.h"
#include "Coordenada.h"
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

void CmdRoda::executa(Simulador& sim, const std::vector<std::string>& args) {
   Fabrica& fabrica = sim.getFabrica();

   if (!posicaoNaFabrica(fabrica, args[0])) {
      std::cout << "Posicao fora da fabrica: " << args[0] << "\n";
      return;
   }

   std::string erro;
   if (!fabrica.rodaMaquina(Coordenada(args[0]), paraDirecao(args[1]), erro)) {
      std::cout << "Erro: " << erro << "\n";
      return;
   }

   sim.mostraEcra();
}
