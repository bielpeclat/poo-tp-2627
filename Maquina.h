#ifndef POO_TP_2627_MAQUINA_H
#define POO_TP_2627_MAQUINA_H

#include <string>
#include "Coordenada.h"   // Objeto coordenada está guardado dentro da máquina.

class Item;     // Ambas usadas em ponteiros e referência.
class Fabrica;  // Declarar é o suficiente.

enum class Direcao {CIMA, BAIXO, ESQUERDA, DIREITA}; // c, b, e, d - Direção das maquinas

// Classe abstrata de todas as maquinas da fabrica - apenas guarda a posição e a direção,
// o comportamento individual de cada uma delas é feito em classes derivadas.
class Maquina {
    Coordenada pos;   // posição fixa na fabrica
    Direcao dir;      // direção de saída dos items

public:
    Maquina(const Coordenada& pos, Direcao dir);
    virtual ~Maquina() = default;   // delete de uma Maquina* chama o destrutor da derivada

    // Comum a todas as máquinas
    const Coordenada& getPosicao() const { return pos; }
    Direcao getDirecao() const { return dir; }
    void setDirecao(Direcao d) { dir = d; }   // -- Comando roda.
    int getValorVenda() const;                // -- Quantos créditos a fábrica recebe ao vender
                                              // esta máquina - settings.

    // Cada tipo de máquina define os seus.
    virtual int getCusto() const = 0; // Qnt custa comprar?
    virtual char getCaracter() const = 0; // Símbolo da máquina no ecrã
    virtual std::string getNome() const = 0; // Nome legível da máquina - ex: "Transportador"
    virtual std::string getDescricao() const = 0; // Estado interno da máquina. O que está a fazer.

    virtual bool aceita(const Item* item) const = 0; // Cada máquina tem as suas regras, verifica se é possível.
    virtual bool recebe(Item* item, int instante) = 0; // Entrega mesmo o item se tudo tiver corrido bem.
    virtual void atua(Fabrica& fabrica) = 0; // Comportamento em cada instante
};

#endif //POO_TP_2627_MAQUINA_H
