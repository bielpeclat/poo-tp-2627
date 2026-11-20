#ifndef POO_TP_2627_CMDFABRICA_H
#define POO_TP_2627_CMDFABRICA_H

#include <string>
#include <vector>
#include "Comando.h"

class CmdFabrica : public Comando {
public:
   CmdFabrica();
   std::string getAjuda() const override;
   bool valida(const std::vector<std::string>& args, std::string& erro) const override;
   void executa(Simulador& sim, const std::vector<std::string>& args) override;
   bool precisaFabrica() const override;
};

#endif //POO_TP_2627_CMDFABRICA_H
