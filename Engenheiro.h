#ifndef POO_TP_2627_ENGENHEIRO_H
#define POO_TP_2627_ENGENHEIRO_H

#include <string>

class Maquina;   // so e usada atraves de ponteiro, declarar basta

// Planeamento da classe Engenheiro (so o .h, a implementacao fica para a entrega final).
// Um engenheiro e contratado pelo gestor (custo e salario vem do Settings), tem um nome e um
// numero identificador atribuido automaticamente (o primeiro e o 1). Pode estar livre ou
// associado a uma maquina; quando associado, reduz a duracao das operacoes dessa maquina.
// A Fabrica guarda os engenheiros; o Engenheiro NAO e dono da maquina a que esta associado.
class Engenheiro {
    static int proximoId;       // contador partilhado por todos os engenheiros, gera o id seguinte
    int id;                     // unico, atribuido automaticamente na criacao
    std::string nome;           // definido na criacao; pode repetir-se entre engenheiros
    Maquina* maquina;           // maquina a que esta associado; nullptr se estiver livre

public:
    explicit Engenheiro(const std::string& nome);   // so o nome: o id e gerado aqui

    int getId() const;
    const std::string& getNome() const;
    bool estaLivre() const;                         // maquina == nullptr
    Maquina* getMaquina() const;                    // nullptr se estiver livre

    void associa(Maquina* nova);                    // comando atribui: passa da maquina anterior (se havia) para a nova
    void liberta();                                 // fica livre (usado pelo recupera, e ao vender a maquina)
};

#endif //POO_TP_2627_ENGENHEIRO_H
