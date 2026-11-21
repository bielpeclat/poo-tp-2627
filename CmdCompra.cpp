#include "CmdCompra.h"

#include "Simulador.h"
#include "Fabrica.h"
#include "Coordenada.h"
#include <iostream>

CmdCompra::CmdCompra() : Comando("compra", "compra <tipo> <lc> <dir>") {}

std::string CmdCompra::getAjuda() const {
   return "Sintaxe: compra <tipo> <lc> <dir>\n"
          "Parametros: tipo - p (perfuradora), t (transportador), r (refinaria), o (oficina), s (silo) ou l (lancador); lc - posicao da fabrica; dir - direcao de saida: c, b, e ou d (cima, baixo, esquerda, direita)\n"
          "Efeito: compra uma maquina do tipo indicado e coloca-a na posicao lc com a direcao de saida dir\n"
          "Falha: se a posicao estiver ocupada, se for uma cratera ou se nao houver creditos suficientes\n"
          "Exemplo: compra t ce d\n";
}

bool CmdCompra::valida(const std::vector<std::string>& args, std::string& erro) const {
   if (!verificaNumArgs(args, 3, 3, erro))
      return false;

   if (!eTipoMaquina(args[0])) {
      erro = "tipo invalido (esperado p, t, r, o, s ou l)";
      return false;
   }

   if (!eFormatoPosicao(args[1])) {
      erro = "posicao invalida (esperado duas letras minusculas, ex: ce)";
      return false;
   }

   if (!eDirecao(args[2])) {
      erro = "direcao invalida (esperado c, b, e ou d)";
      return false;
   }

   return true;
}

void CmdCompra::executa(Simulador& sim, const std::vector<std::string>& args) {
   Fabrica& fabrica = sim.getFabrica();

   if (!posicaoNaFabrica(fabrica, args[1])) {   // so agora sabemos o tamanho real da fabrica
      std::cout << "Posicao fora da fabrica: " << args[1] << "\n";
      return;
   }

   std::string erro;
   if (!fabrica.compraMaquina(args[0][0], Coordenada(args[1]), paraDirecao(args[2]), erro)) {
      std::cout << "Erro: " << erro << "\n";
      return;
   }

   sim.mostraEcra();
}
