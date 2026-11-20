#include "CmdMelhora.h"

#include <iostream>

CmdMelhora::CmdMelhora() : Comando("melhora", "melhora <lc>") {}

std::string CmdMelhora::getAjuda() const {
   return "Sintaxe: melhora <lc>\n"
          "Parametros: lc - posicao da fabrica onde esta a maquina a melhorar (duas letras: linha e coluna)\n"
          "Efeito: melhora a maquina que se encontra na posicao indicada, de acordo com a sua natureza e mediante o pagamento do custo da melhoria\n"
          "Falha: se nao existir maquina na posicao, se a maquina nao puder ser melhorada (ou ja tiver o maximo de melhorias) ou se nao houver creditos suficientes\n"
          "Exemplo: melhora hi\n";
}

bool CmdMelhora::valida(const std::vector<std::string>& args, std::string& erro) const {
   if (!verificaNumArgs(args, 1, 1, erro))
      return false;

   if (!eFormatoPosicao(args[0])) {
      erro = "posicao invalida (esperado duas letras minusculas, ex: hi)";
      return false;
   }

   return true;
}

void CmdMelhora::executa(Simulador&, const std::vector<std::string>&) {
   std::cout << "melhora: disponivel na entrega final\n";
}
