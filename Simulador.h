#ifndef POO_TP_2627_SIMULADOR_H
#define POO_TP_2627_SIMULADOR_H

#include <string>
#include <vector>

class Fabrica; // Apenas usado para as funções saberem da existência destas classes.
class Comando;

class Simulador {
    Fabrica* fabrica;                 // nullptr até a fábrica ser criada.
    std::vector<Comando*> comandos;   // vector que contem 1 objeto para cada comando.
    bool terminado;                   // passa a true com o fim da simulação - condição de paragem do ciclo principal.
    bool aExecutarFicheiro;           // True enquanto está a correr um executa - impede um executa dentro de outro.

    static std::vector<std::string> separaPalavras(const std::string& linha);

public:
};


#endif //POO_TP_2627_SIMULADOR_H
