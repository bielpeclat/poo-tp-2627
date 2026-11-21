#include "CmdLPosicao.h"
#include "Simulador.h"
#include "Fabrica.h"

#include <algorithm>   // std::max
#include <iostream>

CmdLPosicao::CmdLPosicao() : Comando("lposicao", "lposicao <lc> [n]") {}

std::string CmdLPosicao::getAjuda() const {
   return "Sintaxe: lposicao <lc> [n]\n"
          "Parametros: lc - posicao da fabrica (duas letras: linha e coluna); n (opcional) - raio, em posicoes, a volta de lc\n"
          "Efeito: mostra o terreno da posicao lc (e a quantidade de materia-prima, se for um deposito); com n, mostra todas as posicoes dentro do quadrado de raio n centrado em lc\n"
          "Falha: se a fabrica ainda nao existir, se lc nao for uma posicao valida da fabrica, se n nao for um inteiro ou se houver parametros a mais ou a menos\n"
          "Exemplo: lposicao df 2\n";
}

bool CmdLPosicao::valida(const std::vector<std::string>& args, std::string& erro) const {
   if (!verificaNumArgs(args, 1, 2, erro))
      return false;

   if (!eFormatoPosicao(args[0])) {
      erro = "posicao invalida (esperado duas letras minusculas, ex: df)";
      return false;
   }

   if (args.size() == 2 && !eInteiro(args[1])) {
      erro = "o raio tem de ser um inteiro";
      return false;
   }

   return true;
}

void CmdLPosicao::executa(Simulador& sim, const std::vector<std::string>& args) {
   const Fabrica& fabrica = sim.getFabrica();

   if (!posicaoNaFabrica(fabrica, args[0])) {
      std::cout << "Posicao fora da fabrica: " << args[0] << "\n";
      return;
   }

   int raio = 0;
   if (args.size() == 2)
      raio = std::stoi(args[1]);

   // Um raio maior que a fabrica mostra o mesmo que um raio do tamanho da fabrica;
   // sem este limite, um raio enorme (ex: 999999999) faria o ciclo da fabrica demorar uma eternidade.
   int maximo = std::max(fabrica.getLinhas(), fabrica.getColunas());
   if (raio > maximo)
      raio = maximo;

   std::cout << fabrica.listaPosicao(args[0], raio);
}
