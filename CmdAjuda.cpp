#include "CmdAjuda.h"
#include "Simulador.h"

#include <iostream>

CmdAjuda::CmdAjuda() : Comando("ajuda", "ajuda [comando]") {}

std::string CmdAjuda::getAjuda() const {
   return "Sintaxe: ajuda [comando]\n"
          "Parametros: comando (opcional) - nome do comando de que se quer a ajuda detalhada\n"
          "Efeito: sem parametro, lista todos os comandos com a sua sintaxe; com parametro, mostra a ajuda detalhada desse comando\n"
          "Falha: se tiver mais de um parametro ou se o comando indicado nao existir\n"
          "Exemplo: ajuda compra\n";
}

bool CmdAjuda::precisaFabrica() const {
   return false;
}

bool CmdAjuda::valida(const std::vector<std::string>& args, std::string& erro) const {
   return verificaNumArgs(args, 0, 1, erro);
}

void CmdAjuda::executa(Simulador& sim, const std::vector<std::string>& args) {
   if (args.empty()) { // nao recebemos o segundo parametro
      for (const Comando* c : sim.getComandos()) {
         std::cout << c->getSintaxe() << "\n";
      }
      return;
   }

   const Comando* c = sim.procuraComando(args[0]);
   if (c == nullptr) {
      std::cout << "Comando desconhecido: " << args[0] << "\n";
      return;
   }
   std::cout << c->getAjuda();
}
