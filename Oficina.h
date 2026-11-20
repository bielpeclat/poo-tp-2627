#ifndef POO_TP_2627_OFICINA_H
#define POO_TP_2627_OFICINA_H

#include "Maquina.h"

class Oficina : public Maquina {
public:
    Oficina(const Coordenada& pos, Direcao dir);

    int getCusto() const override;
    char getCaracter() const override;
    std::string getNome() const override;
    std::string getDescricao() const override;

    bool aceita(const Item* item) const override;
    bool recebe(Item* item, int instante) override;
    void atua(Fabrica& fabrica) override;
};

#endif //POO_TP_2627_OFICINA_H
