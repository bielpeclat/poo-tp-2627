#ifndef POO_TP_2627_CMDAVANCA_H
#define POO_TP_2627_CMDAVANCA_H

#include <string>
#include <vector>
#include "Comando.h"

class CmdAvanca : public Comando {
public:
   CmdAvanca();
   std::string getAjuda() const override;
   bool valida(const std::vector<std::string>& args, std::string& erro) const override;
   void executa(Simulador& sim, const std::vector<std::string>& args) override;
};

#endif //POO_TP_2627_CMDAVANCA_H
