#include "CmdVende.h"

#include "Simulador.h"
#include "Fabrica.h"
#include "Coordenada.h"
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

void CmdVende::executa(Simulador& sim, const std::vector<std::string>& args) {
   Fabrica& fabrica = sim.getFabrica();

   if (!posicaoNaFabrica(fabrica, args[0])) {
      std::cout << "Posicao fora da fabrica: " << args[0] << "\n";
      return;
   }

   std::string erro;
   if (!fabrica.vendeMaquina(Coordenada(args[0]), erro)) {
      std::cout << "Erro: " << erro << "\n";
      return;
   }

   sim.mostraEcra();
}
