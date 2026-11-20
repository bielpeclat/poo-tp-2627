#ifndef POO_TP_2627_CMDAJUDA_H
#define POO_TP_2627_CMDAJUDA_H

#include <string>
#include <vector>
#include "Comando.h"

class CmdAjuda : public Comando {
public:
   CmdAjuda();
   std::string getAjuda() const override;
   bool valida(const std::vector<std::string>& args, std::string& erro) const override;
   void executa(Simulador& sim, const std::vector<std::string>& args) override;
   bool precisaFabrica() const override;
};

#endif //POO_TP_2627_CMDAJUDA_H
