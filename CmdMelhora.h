#ifndef POO_TP_2627_CMDMELHORA_H
#define POO_TP_2627_CMDMELHORA_H

#include <string>
#include <vector>
#include "Comando.h"

class CmdMelhora : public Comando {
public:
   CmdMelhora();
   std::string getAjuda() const override;
   bool valida(const std::vector<std::string>& args, std::string& erro) const override;
   void executa(Simulador& sim, const std::vector<std::string>& args) override;
};

#endif //POO_TP_2627_CMDMELHORA_H
