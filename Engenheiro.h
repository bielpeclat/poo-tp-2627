//
// Created by Filipe Fadigas on 06/11/2026.
//

#ifndef POO_TP_2627_ENGENHEIRO_H
#define POO_TP_2627_ENGENHEIRO_H

#include <sstream>

// ATENÇÃO! EU ACHO QUE FAZER A CLASS ENGENHEIRO É DEMAIS PRO CHECKPOINT 1!
// NÃO ADICIONEI NADA AO MAIN NEM AO DESENHA PAINEL PORQUE ISTO NÃO É PARA O CHECKPOINT 1!

class Maquina; // Fiz class Maquina aqui só porque alguns métodos pedidos para a classe Engenheiro
               // precisam dessa class. Mais tarde obviamente deverá ter a sua própria classe e depois
               // liga-se.

class Engenheiro {

    static int contadorId; // Variável partilhada por todos os engenheiros para gerar o ID
    int id;
    std::string nome;
    Maquina* maquinaAssociada;

public:

    Engenheiro(const std::string& nomeEngenheiro); // apenas nome porque, como o enunciado diz, ID é atribuído automaticamente

    int getId() const; // getCenas, dispensa introduções
    std::string getNome() const;
    bool isLivre() const;


    void associaMaquina(Maquina* novaMaquina); // nome dos métodos é muito straight-forward.
    void liberta();
};


#endif //POO_TP_2627_ENGENHEIRO_H
