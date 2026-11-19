#include "Comando.h"
#include "Coordenada.h"
#include "Fabrica.h"
#include "Settings.h"

Comando::Comando(const std::string& nome, const std::string& sintaxe)
   : nome(nome), sintaxe(sintaxe) {}

bool Comando::verificaNumArgs(const std::vector<std::string>& args, int min, int max, std::string& erro) {
    int n = static_cast<int>(args.size());
    if (n < min || n > max) {
        erro = "numero de parametros errado";
        return false;
    }
    return true;
}

bool Comando::eInteiro(const std::string& s) {

    if (s.empty() || s.size() > 9) // Aqui tratamos de carateres (digitos)
        return false;

    for (char ch : s) {
        if (ch < '0' || ch > '9')
            return false;
    }
    return true;
}

bool Comando::eDirecao(const std::string& s) {
    return s == "c" || s == "b" || s == "e" || s == "d";
}

bool Comando::eTipoMaquina(const std::string& s) {
    return s == "p" || s == "t" || s == "r" || s == "o" || s == "s" || s == "l";
}

// so a forma: a fabrica pode ainda nao existir, por isso usamos o maximo (26x26)
bool Comando::eFormatoPosicao(const std::string& s) { // s é a posição escrita pelo utilizador.
    return Coordenada::valida(s, Settings::fabrica_max_linhas, Settings::fabrica_max_colunas);
}

bool Comando::posicaoNaFabrica(const Fabrica& f, const std::string& lc) { // Só pode ser usado com a fábrica já criada.
    return Coordenada::valida(lc, f.getLinhas(), f.getColunas());
}
