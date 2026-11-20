#ifndef POO_TP_2627_CMDATRIBUI_H
#define POO_TP_2627_CMDATRIBUI_H

#include <string>
#include <vector>
#include "Comando.h"

class CmdAtribui : public Comando {
public:
   CmdAtribui();
   std::string getAjuda() const override;
   bool valida(const std::vector<std::string>& args, std::string& erro) const override;
   void executa(Simulador& sim, const std::vector<std::string>& args) override;
};

#endif //POO_TP_2627_CMDATRIBUI_H
