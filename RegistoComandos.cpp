//
// Created by gabriel-costa on 11/19/26.
//

#include "RegistoComandos.h"
#include "CmdFim.h"
#include "CmdAjuda.h"

std::vector<Comando*> criaTodosComandos() {
   std::vector<Comando*> local;
   local.push_back(new CmdFim());
   local.push_back(new CmdAjuda());
   return local;
}