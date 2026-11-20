#ifndef POO_TP_2627_CMDESTADO_H
#define POO_TP_2627_CMDESTADO_H

#include <string>
#include <vector>
#include "Comando.h"

class CmdEstado : public Comando {
public:
   CmdEstado();
   std::string getAjuda() const override;
   bool valida(const std::vector<std::string>& args, std::string& erro) const override;
   void executa(Simulador& sim, const std::vector<std::string>& args) override;
};

#endif //POO_TP_2627_CMDESTADO_H
