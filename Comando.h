#ifndef POO_TP_2627_COMANDO_H
#define POO_TP_2627_COMANDO_H

#include <string>
#include <vector>
#include "Maquina.h"   // enum Direcao

class Simulador;
class Fabrica;

class Comando { // Classe -abstrata- para TODOS os Comandos

    std::string nome;
    std::string sintaxe;

public:
    Comando(const std::string& nome, const std::string& sintaxe); // ex: "compra", "compra <tipo> <lc> <dir>"
    virtual ~Comando() = default;

    const std::string& getNome() const { return nome; }
    const std::string& getSintaxe() const { return sintaxe; }
    virtual std::string getAjuda() const = 0;   // - "ajuda <comando>"

    // a maioria dos comandos so funciona depois de a fabrica existir;
    // fabrica, carrega, executa, ajuda e fim fazem override para devolver false
    virtual bool precisaFabrica() const { return true; } // Maior parte dos comandos precisa da fábrica portanto
                                                         // esta função serve de verificação.

    virtual bool valida(const std::vector<std::string>& args, std::string& erro) const = 0; // Recebe os argumentos passados na sintaxe.
                                                                                            // Se tem 3 argumentos, se a máquina é válida, se as coordenadas têm 2 letras
                                                                                            // e se a letra da direção é válida.

    virtual void executa(Simulador& sim, const std::vector<std::string>& args) = 0; // valida devolveu true? então executa o comando.

protected: // Para que apenas a própria classe Comando e as suas derivadas possam usar estas funções.
    static bool verificaNumArgs(const std::vector<std::string>& args, int min, int max, std::string& erro);
    // args é o vetor com as palavras que vêm depois do nome do comando:
    // Cada comando (ex: compra, avanca, fim, etc.) aceita um número diferente de argumentos. O min e o max dizem quantos aceita.

    static bool eInteiro(const std::string& s);
    static bool eDirecao(const std::string& s);             // c, b, e, d -  se é uma das 4 direções.
    static Direcao paraDirecao(const std::string& s);       // "c|b|e|d" -> Direcao (so chamar depois de eDirecao ter dado true)
    static bool eTipoMaquina(const std::string& s);         // p, t, r, o, s, l - se é um tipo de máquina válido
    static bool eFormatoPosicao(const std::string& s);      // se são 2 letras minúsculas dentro do máximo 26x26. (Não precisa da Fábrica - Pode ser usada no valida)
    static bool posicaoNaFabrica(const Fabrica& f, const std::string& lc); // Se a posição cabe dentro da fábrica em questão. (Precisa da Fábrica - Só pode ser usada no executa)
};

#endif //POO_TP_2627_COMANDO_H
