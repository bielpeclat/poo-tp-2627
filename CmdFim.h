//
// Created by gabriel-costa on 11/19/26.
//

#ifndef POO_TP_2627_CMDFIM_H
#define POO_TP_2627_CMDFIM_H

#include <string>
#include "Comando.h"

class CmdFim : public Comando {
public:
   CmdFim();
   std::string getAjuda() const override;
   bool valida(const std::vector<std::string>& args, std::string& erro) const override;
   void executa(Simulador& sim, const std::vector<std::string>& args) override;
   bool precisaFabrica() const override;
};


#endif //POO_TP_2627_CMDFIM_H