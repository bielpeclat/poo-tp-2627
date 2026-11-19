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
    Simulador();
    ~Simulador();

    //proibição que objetos da classe Simulador sejam copiados.
    Simulador(const Simulador&) = delete;
    Simulador& operator=(const Simulador&) = delete;

    void corre(); // Ciclo principal do Simulador, vai ler do teclado
    void processaLinha(const std::string& linha);        //1. separa em palavras         → {"compra", "t", "ce", "d"}
                                                         // 2. procura o comando          → "compra" → CmdCompra
                                                         // 3. pede-lhe para validar      → cmd->valida({"t","ce","d"}, erro)
                                                         // 4. verifica se precisa da fabrica e se ela existe
                                                         // 5. manda executar             → cmd->executa(*this, {"t","ce","d"})
    bool executaFicheiro(const std::string& nomeFicheiro); // lê um ficheiro inteiro de comandos.

    // Propriedade dos Comandos
    bool temFabrica() const { return fabrica != nullptr; }
    Fabrica& getFabrica() { return *fabrica; }           // Chamada depois do temFabrica()
    void defineFabrica(Fabrica* nova);                   // defineFabrica() guarda o ponteiro, é o Simulador fica encarregue do delete no fim, e não o comando que fez o new.
    void mostraEcra() const;

    void termina() { terminado = true; }
    bool estaAExecutarFicheiro() const { return aExecutarFicheiro; }

    Comando* procuraComando(const std::string& nome) const; // Encontra um comando apartir do seu nome.
                                                            // Percorre o vetor e devolve o comando cujo nome coincide, ou nullptr se não houver nenhum.
    const std::vector<Comando*>& getComandos() const { return comandos; } // É usada pelo ajuda sem parâmetro, que tem de mostrar a sintaxe de todos os comandos.
};

#endif //POO_TP_2627_SIMULADOR_H
