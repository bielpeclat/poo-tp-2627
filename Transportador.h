#ifndef POO_TP_2627_TRANSPORTADOR_H
#define POO_TP_2627_TRANSPORTADOR_H

#include "Maquina.h"

// Transporta 1 item de cada vez - a cada instante -> tenta entregá-lo na sua direção.
class Transportador : public Maquina {
    Item* item;            // nullptr se estiver vazio. O transportador é dono do item.
    int instanteRececao;   // instante em que recebeu o item

public:
    Transportador(const Coordenada& pos, Direcao dir);
    ~Transportador() override;

    // proibido fazer cópias
    Transportador(const Transportador&) = delete;
    Transportador& operator=(const Transportador&) = delete;

    int getCusto() const override;
    char getCaracter() const override;
    std::string getNome() const override;
    std::string getDescricao() const override;

    bool aceita(const Item* item) const override;
    bool recebe(Item* item, int instante) override;
    void atua(Fabrica& fabrica) override;
};

#endif //POO_TP_2627_TRANSPORTADOR_H