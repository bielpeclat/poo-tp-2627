#include "Simulador.h"
#include "Comando.h"
#include "Fabrica.h"
#include "Ecra.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "RegistoComandos.h" // "Cria" os 17 comandos que criámos.


Simulador::Simulador() : fabrica(nullptr), terminado(false), aExecutarFicheiro(false) { // Construtor
   comandos = criaTodosComandos();   // Um objeto de cada um dos 17 comandos.
}

Simulador::~Simulador() { // Destrói não só a fábrica mas também os comandos. Dessa forma não há desperdício de memória.
   delete fabrica;
   for (Comando* c : comandos) {
      delete c;
   }
}

// - - - Ciclo principal do Simulador - - -
void Simulador::corre() {
   std::cout << "Simulador de fabrica em Marte\n";
   std::cout << "Crie a fabrica com 'fabrica <nl> <nc>' ou 'carrega <ficheiro>'.\n";
   std::cout << "Escreva 'ajuda' para receber a lista de todos os comandos.\n";

   std::string linha;
   while (!terminado) {
      std::cout << "\n> ";
      if (!std::getline(std::cin, linha)) { // std::getline(std::cin, linha) lê a linha inteira, até ao Enter, e guarda-a em linha.
         break;                                   // Usa-se getline e não cin >> linha porque o >> pára no primeiro espaço.
      }
      processaLinha(linha);
   }
}


// função que processa a linha recebida pelo teclado (função corre) ou por um ficheiro (executaFicheiro)
void Simulador::processaLinha(const std::string& linha) {

   std::vector<std::string> palavras = separaPalavras(linha);
   if (palavras.empty()) { // linha está vazia? Termina a função
      return;
   }

   Comando* cmd = procuraComando(palavras[0]); // Primeiro procuramos o comando pela lista para sabermos o que o utilizador pretende.
   if (cmd == nullptr) {
      std::cout << "Comando desconhecido: " << palavras[0] << ". Escreva 'ajuda'.\n";
      return;
   }

   std::vector<std::string> args(palavras.begin() + 1, palavras.end()); // Argumentos, palavras aseguir ao nome do comando (+1).

   std::string erro;
   if (!cmd->valida(args, erro)) { // validação do comando
      std::cout << "Erro: " << erro << "\n";
      std::cout << "Sintaxe: " << cmd->getSintaxe() << "\n";
      return;
   }

   if (cmd->precisaFabrica() && !temFabrica()) { // Se o comando precisa de fábrica não pode correr sem ela.
      std::cout << "Primeiro tem de criar a fabrica (fabrica ou carrega).\n";
      return;
   }

   cmd->executa(*this, args); // não houve problema nas validações - executa.
}


//Ficheiro.
bool Simulador::executaFicheiro(const std::string& nomeFicheiro) {
   std::ifstream f(nomeFicheiro);
   if (!f) { // Ficheiro decidiu não abrir.
      return false;
   }

   aExecutarFicheiro = true;
   std::string linha;

   while (!terminado && std::getline(f, linha)) {   // Precaução no caso de aparecer "fim"
      if (separaPalavras(linha).empty()) {
         continue; // saltar linhas vazias
      }
      std::cout << "\n> " << linha << "\n";         // mostra o comando, como se fosse escrito
      processaLinha(linha);                         // EXATAMENTE a mesma forma de agir de como se fosse do teclado
   }
   aExecutarFicheiro = false; // Já executámos o ficheiro, fica false.
   return true; // sucesso
}


// As nossas funções de apoio que ajudam as anteriores
std::vector<std::string> Simulador::separaPalavras(const std::string& linha) {

   std::vector<std::string> palavras;
   std::istringstream iss(linha);      // trata a string como se fosse o cin, como se viesse do teclado.
   std::string palavra;

   while (iss >> palavra) {            // ">>" salta espaços, igual ao cin
      palavras.push_back(palavra); // palavras é um vetor, push_back adiciona o elemento ao fim do vetor.
   }
   return palavras;
}

Comando* Simulador::procuraComando(const std::string& nome) const {
   for (Comando* c : comandos) { // simples ciclo for que faz a comparação do nome do comando submetido com a nossa lista
      if (c->getNome() == nome) {
         return c;
      }
   }
   return nullptr; // comando não existe.
}

void Simulador::defineFabrica(Fabrica* nova) {
   delete fabrica;   // impedir que não haja memória por libertar
   fabrica = nova;   // O atributo fabrica é privado, comandos fabrica e carrega criam uma fábrica nova e têm de a dar ao Simulador.
}                    // Como o atributo é privado, não podem escrever diretamente nele.

void Simulador::mostraEcra() const { // self-explanatory
   if (fabrica == nullptr) return;
   Ecra ecra(fabrica->getAlturaEcra(), fabrica->getLarguraEcra());   // Apenas o tamanho necessário.
   fabrica->preparaEcra(ecra);
   ecra.mostra();
}