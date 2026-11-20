//
// Created by gabriel-costa on 11/19/26.
//

#include "RegistoComandos.h"
#include "CmdFim.h"
#include "CmdAjuda.h"
#include "CmdExecuta.h"
#include "CmdLPosicao.h"
#include "CmdFabrica.h"
#include "CmdCarrega.h"
#include "CmdRecupera.h"
#include "CmdGrava.h"
#include "CmdDespede.h"
#include "CmdAtribui.h"
#include "CmdContrata.h"
#include "CmdMelhora.h"
#include "CmdEstado.h"
#include "CmdAvanca.h"
#include "CmdRoda.h"
#include "CmdVende.h"
#include "CmdCompra.h"

std::vector<Comando*> criaTodosComandos() {
   std::vector<Comando*> local;
   local.push_back(new CmdFim());
   local.push_back(new CmdAjuda());
   local.push_back(new CmdExecuta());
   local.push_back(new CmdLPosicao());
   local.push_back(new CmdFabrica());
   local.push_back(new CmdCarrega());
   local.push_back(new CmdRecupera());
   local.push_back(new CmdGrava());
   local.push_back(new CmdDespede());
   local.push_back(new CmdAtribui());
   local.push_back(new CmdContrata());
   local.push_back(new CmdMelhora());
   local.push_back(new CmdEstado());
   local.push_back(new CmdAvanca());
   local.push_back(new CmdRoda());
   local.push_back(new CmdVende());
   local.push_back(new CmdCompra());
   return local;
}