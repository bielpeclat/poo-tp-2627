#ifndef POO_TP_2627_CMDCONTRATA_H
#define POO_TP_2627_CMDCONTRATA_H

#include <string>
#include <vector>
#include "Comando.h"

class CmdContrata : public Comando {
public:
   CmdContrata();
   std::string getAjuda() const override;
   bool valida(const std::vector<std::string>& args, std::string& erro) const override;
   void executa(Simulador& sim, const std::vector<std::string>& args) override;
};

#endif //POO_TP_2627_CMDCONTRATA_H
