//
// Created by gabriel-costa on 11/20/26.
//

#ifndef POO_TP_2627_CMDEXECUTA_H
#define POO_TP_2627_CMDEXECUTA_H

#include <string>
#include <vector>
#include "Comando.h"

class CmdExecuta : public Comando {
public:
   CmdExecuta();
   std::string getAjuda() const override;
   bool valida(const std::vector<std::string>& args, std::string& erro) const override;
   void executa(Simulador& sim, const std::vector<std::string>& args) override;
   bool precisaFabrica() const override   ;
};


#endif //POO_TP_2627_CMDEXECUTA_H