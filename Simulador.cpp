#include "Simulador.h"
#include "Comando.h"
#include "Fabrica.h"
#include "Ecra.h"

#include <iostream>
#include <fstream>
#include <sstream>

// includes dos comandos (vamos acrescentando a medida que os criamos)
#include "CmdAjuda.h"
#include "CmdFim.h"


// ======================= construtor e destrutor =======================

Simulador::Simulador() : fabrica(nullptr), terminado(false), aExecutarFicheiro(false) {
   // um objeto de cada comando (vamos acrescentando a medida que os criamos)
   comandos.push_back(new CmdAjuda());
   comandos.push_back(new CmdFim());
}

Simulador::~Simulador() {
   delete fabrica;                 // delete de nullptr nao faz nada, e seguro
   for (Comando* c : comandos) {
      delete c;                    // o destrutor virtual do Comando chama o da derivada
   }
}

// ======================= ciclo principal (teclado) =======================

void Simulador::corre() {
   std::cout << "Simulador de fabrica em Marte\n";
   std::cout << "Crie a fabrica com 'fabrica <nl> <nc>' ou 'carrega <ficheiro>'.\n";
   std::cout << "Escreva 'ajuda' para ver todos os comandos.\n";

   std::string linha;
   while (!terminado) {
      std::cout << "\n> ";
      if (!std::getline(std::cin, linha)) {   // fim do input (ex: ctrl+z / ctrl+d)
         break;
      }
      processaLinha(linha);
   }
}

// ======================= processar uma linha =======================
// usado tanto pelo teclado (corre) como pelo ficheiro (executaFicheiro)

void Simulador::processaLinha(const std::string& linha) {
   std::vector<std::string> palavras = separaPalavras(linha);
   if (palavras.empty()) {
      return;                          // linha vazia: ignora
   }

   // 1. procurar o comando pela primeira palavra
   Comando* cmd = procuraComando(palavras[0]);
   if (cmd == nullptr) {
      std::cout << "Comando desconhecido: " << palavras[0] << ". Escreva 'ajuda'.\n";
      return;
   }

   // 2. os argumentos sao as palavras a seguir ao nome
   std::vector<std::string> args(palavras.begin() + 1, palavras.end());

   // 3. o comando valida-se a si proprio
   std::string erro;
   if (!cmd->valida(args, erro)) {
      std::cout << "Erro: " << erro << "\n";
      std::cout << "Sintaxe: " << cmd->getSintaxe() << "\n";
      return;
   }

   // 4. comandos que precisam da fabrica nao correm sem ela
   if (cmd->precisaFabrica() && !temFabrica()) {
      std::cout << "Primeiro tem de criar a fabrica (fabrica ou carrega).\n";
      return;
   }

   // 5. tudo certo: executa
   cmd->executa(*this, args);
}

// ======================= executar comandos de um ficheiro =======================

bool Simulador::executaFicheiro(const std::string& nomeFicheiro) {
   std::ifstream f(nomeFicheiro);
   if (!f) {
      return false;                    // nao abriu
   }

   aExecutarFicheiro = true;
   std::string linha;
   while (!terminado && std::getline(f, linha)) {   // para se aparecer um "fim" no ficheiro
      if (separaPalavras(linha).empty()) {
         continue;                                  // salta linhas vazias
      }
      std::cout << "\n> " << linha << "\n";          // mostra o comando, como se fosse escrito
      processaLinha(linha);                         // EXATAMENTE o mesmo caminho do teclado
   }
   aExecutarFicheiro = false;
   return true;
}

// ======================= funcoes de apoio =======================

// "compra  t ce d" -> {"compra", "t", "ce", "d"}  (ignora espacos a mais)
std::vector<std::string> Simulador::separaPalavras(const std::string& linha) {
   std::vector<std::string> palavras;
   std::istringstream iss(linha);      // trata a string como se fosse o cin
   std::string palavra;
   while (iss >> palavra) {            // o >> salta espacos, tal como no cin
      palavras.push_back(palavra);
   }
   return palavras;
}

Comando* Simulador::procuraComando(const std::string& nome) const {
   for (Comando* c : comandos) {
      if (c->getNome() == nome) {
         return c;
      }
   }
   return nullptr;                     // nao existe
}

void Simulador::defineFabrica(Fabrica* nova) {
   delete fabrica;     // em principio e nullptr (so se cria uma vez), mas assim nunca ha fugas
   fabrica = nova;
}

void Simulador::mostraEcra() const {
   if (fabrica == nullptr) return;
   Ecra ecra;
   fabrica->preparaEcra(ecra);
   ecra.mostra();
}