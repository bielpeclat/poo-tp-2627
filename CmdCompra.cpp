#include "CmdCompra.h"

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

// provisorio: sera ligado a Fabrica quando o contrato do Filipe estiver publicado
void CmdCompra::executa(Simulador&, const std::vector<std::string>&) {
   std::cout << "compra: ainda nao ligado a fabrica\n";
}
