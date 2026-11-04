#ifndef POO_TP_2627_FABRICA_H
#define POO_TP_2627_FABRICA_H


class Fabrica {

    int tam_Linhas_f, tam_Colunas_f;           // tamanho da fábrica sem contar com a régua (ABC...) e os +2 espaços da moldura.
    int creditos;
    int instante;

    void inicializaGrelhaVazia();
    void geraElementosAleatorios(); // Para mais tarde colocar as crateras e os depósitos.

public:
    Fabrica(int l, int c); // O nosso construtor pedido no Enunciado
    explicit Fabrica(const std::string &nomeFicheiro); // Construtor mas com recurso ao mapa do tal ficheiro indicado.
                                                       // 'explicit' obriga a escrever explicitamente quando queremos criar um objeto novo, evitando que o programa crie objetos por engano.
};

#endif //POO_TP_2627_FABRICA_H
