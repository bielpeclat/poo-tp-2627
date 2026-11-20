//
// Created by gabriel-costa on 11/19/26.
//

#include "RegistoComandos.h"
#include "CmdFim.h"
#include "CmdAjuda.h"
#include "CmdExecuta.h"
#include "CmdLPosicao.h"
#include "CmdFabrica.h"

std::vector<Comando*> criaTodosComandos() {
   std::vector<Comando*> local;
   local.push_back(new CmdFim());
   local.push_back(new CmdAjuda());
   local.push_back(new CmdExecuta());
   local.push_back(new CmdLPosicao());
   local.push_back(new CmdFabrica());
   return local;
}