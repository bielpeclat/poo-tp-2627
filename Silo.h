#ifndef POO_TP_2627_SILO_H
#define POO_TP_2627_SILO_H

#include "Maquina.h"

// Silo: guarda itens de qualquer tipo, sem limite de capacidade.
// O armazenamento e uma lista ligada feita a mao (o enunciado proibe colecoes da STL
// e so se pode usar a memoria que os itens realmente ocupam).
// A lista funciona como uma fila: os itens entram no fim e o mais antigo esta no inicio.
class Silo : public Maquina {

    // Um no da lista: guarda um item e o instante em que ele chegou ao silo.
    struct No {
        Item* item;           // o silo e dono do item enquanto ele estiver na lista
        int instanteRececao;  // para o item nao andar 2 posicoes no mesmo instante
        No* seguinte;         // nullptr no ultimo no
    };

    No* primeiro;       // item mais antigo (e o primeiro a sair); nullptr se o silo estiver vazio
    No* ultimo;         // item mais recente (e onde se insere); evita percorrer a lista para inserir
    int quantidade;     // quantos itens estao guardados
    int probPerda;      // % de perder o item mais antigo em cada instante (comeca em Settings::silo_prob_perda)

    void apagaPrimeiro();   // remove o no do inicio E apaga o item (o item perdeu-se)
    void largaPrimeiro();   // remove o no do inicio SEM apagar o item (ja foi entregue a outra maquina)

public:
    Silo(const Coordenada& pos, Direcao dir);
    ~Silo() override;       // liberta todos os nos e todos os itens que ainda la estejam

    // Uma lista ligada com ponteiros nao pode ser copiada por omissao (dois silos a apagar os mesmos nos)
    Silo(const Silo&) = delete;
    Silo& operator=(const Silo&) = delete;

    int getQuantidade() const { return quantidade; }

    int getCusto() const override;
    char getCaracter() const override;
    std::string getNome() const override;
    std::string getDescricao() const override;

    bool aceita(const Item* item) const override;
    bool recebe(Item* item, int instante) override;
    void atua(Fabrica& fabrica) override;
};

#endif //POO_TP_2627_SILO_H
