# Simulador de Fábrica em Marte — Relatório do Checkpoint 2

Programação Orientada a Objetos 2026/2027 · DEIS/ISEC

| Nome | Número |
|---|---|
| Filipe Fadigas | 2018001655 |
| Gabriel Costa | 2025140643 |

## Índice

1. Estado da implementação
2. Classes implementadas
3. Relações entre as classes
4. Opções tomadas
5. Mecanismo de atuação por instante
6. Silo
7. Testes
8. Participação individual

## 1. Estado da implementação

O programa compila sem warnings (`-Wall -Wextra -pedantic`) e termina com `fim` sem deixar memória por libertar (verificado com AddressSanitizer). Estão implementados:

- Todo o checkpoint 1: `Ecra`, `Coordenada`, `Posicao`, `Settings` e a criação da fábrica (aleatória ou por ficheiro) desenhada através do ecrã.
- Leitura e validação dos 17 comandos, pelo teclado e pelo comando `executa`. Cada comando valida os seus parâmetros e dá a sua ajuda.
- Comandos com efeito: `ajuda`, `fabrica`, `carrega`, `lposicao`, `compra`, `vende`, `roda`, `avanca`, `estado`, `executa` e `fim`.
- Comandos que só validam (o `executa` informa que fica para a entrega final): `melhora`, `contrata`, `atribui`, `despede`, `grava` e `recupera`.
- Hierarquia de itens, hierarquia de máquinas e o Silo completo (sem `melhora`).
- Mecanismo de atuação das máquinas a cada instante. O comportamento completo da perfuradora, refinaria, oficina e lançador fica para a entrega final (têm só o esqueleto); o transportador e o silo já entregam à máquina vizinha.

## 2. Classes implementadas

| Classe | Papel |
|---|---|
| `Ecra` | Buffer de caracteres genérico (limpa, posiciona, escreve, moldura, mostra). Não sabe nada da fábrica; toda a apresentação passa por ela. |
| `Coordenada` | Converte o par de letras (ex.: `ce`) em linha e coluna e vice-versa; valida o formato. |
| `Posicao` | Uma célula da grelha: terreno (solo, cratera ou depósito), tipo e quantidade de matéria-prima e a máquina que lá estiver. |
| `Fabrica` | Grelha de posições, créditos e instante. Cria o terreno (aleatório ou `carrega`), desenha-se no ecrã e oferece `compraMaquina`, `vendeMaquina`, `rodaMaquina`, `avancaInstante`, `estado` e `listaPosicao`. É dona das máquinas. |
| `Simulador` | Lê comandos do teclado ou de ficheiro, procura o comando, pede-lhe a validação e manda-o executar. É dono da `Fabrica` e dos objetos `Comando`. |
| `Comando` (abstrata) | Base de todos os comandos: `valida`, `executa`, `getAjuda` e `precisaFabrica`. Tem funções de apoio para validar parâmetros (número de argumentos, inteiro, direção, tipo de máquina, formato de posição) e `paraDirecao`. |
| 17 classes `CmdXxx` | Uma por comando (`CmdCompra`, `CmdAvanca`, `CmdEstado`, …), cada uma com a sua validação, a sua ajuda e o seu `executa`. |
| `RegistoComandos` | Função `criaTodosComandos()`: devolve um objeto de cada comando. O `Simulador` não precisa de ser alterado quando aparece um comando novo. |
| `Item` (abstrata) | Nome, caracter e valor (vindos de `Settings`). Filhas: `MinerioFerro`, `SilicioBruto`, `Gelo`, `PlacaFerro`, `SilicioPuro`, `Agua` e `KitHabitat`. Só dados, sem lógica. |
| `Maquina` (abstrata) | Posição, direção de saída, valor de venda (50% do custo). Define o que cada máquina tem de implementar: custo, caracter, nome, descrição, `aceita`, `recebe` e `atua`. |
| `Perfuradora`, `Transportador`, `Refinaria`, `Oficina`, `Lancador`, `Silo` | Os tipos de máquina. Transportador e Silo já entregam itens; as restantes têm `atua` como esqueleto. |

## 3. Relações entre as classes

- **Herança:** `Comando` → 17 `CmdXxx`; `Maquina` → 6 tipos de máquina; `Item` → 7 itens.
- **Composição (posse):** `Simulador` possui a `Fabrica` e os `Comando`; `Fabrica` possui as `Posicao` e, através delas, as `Maquina`; `Transportador` e `Silo` possuem os `Item` que guardam. Quem possui apaga: os destrutores libertam tudo em cadeia (`Simulador` → `Fabrica` → `Maquina` → `Item`).
- **Uso:** os comandos usam o `Simulador` para chegar à `Fabrica`; a `Fabrica` usa o `Ecra` para se desenhar; as máquinas usam a `Fabrica` (em `atua`) para perguntar quem é a máquina vizinha e para registar eventos no painel.

## 4. Opções tomadas

- **Polimorfismo nos comandos:** o `Simulador` só conhece `Comando*`; não há nenhum `if`/`switch` por nome de comando. Cada comando valida os seus parâmetros em `valida` (sem precisar da fábrica) e só no `executa` verifica se a posição cabe na fábrica criada.
- **Posse clara de memória:** o `Simulador` apaga a fábrica e os comandos; a `Fabrica` apaga as máquinas; as cópias da `Fabrica` e das máquinas com ponteiros estão proibidas (`= delete`) para evitar apagar duas vezes.
- **Ficheiro de comandos:** `executa` usa exatamente o mesmo `processaLinha` do teclado e recusa um `executa` dentro de outro.
- **Valores no `Settings`:** nenhum custo, probabilidade ou duração está escrito no código; tudo vem de `Settings`.
- **Sem acentos no código**, como combinado no grupo.
- **CMake:** os ficheiros `.cpp` e `.h` da raiz entram automaticamente (`file(GLOB ... CONFIGURE_DEPENDS)`), por isso criar uma classe nova não obriga a editar o `CMakeLists.txt`.

## 5. Mecanismo de atuação por instante

`Fabrica::avancaInstante()` incrementa o instante, limpa o resumo do instante anterior e percorre a grelha, chamando `atua` em cada máquina uma vez. Os eventos que as máquinas anunciam (ex.: "transportador bloqueado") aparecem no painel.

Para um item nunca andar duas posições no mesmo instante, independentemente da ordem em que a grelha é percorrida, cada máquina que guarda itens regista o instante em que recebeu cada um e só o entrega num instante posterior. O comando `avanca n` repete `avancaInstante` n vezes e mostra o ecrã a cada instante.

## 6. Silo

- Guarda itens de qualquer tipo, **sem limite de capacidade**, numa **lista ligada feita à mão** (sem coleções da STL, como exige o enunciado). Cada nó guarda o item, o instante de receção e o ponteiro para o seguinte.
- Funciona como fila: guarda-se um ponteiro para o primeiro nó (item mais antigo) e outro para o último, por isso inserir no fim e retirar do início custa O(1) e só se usa a memória dos itens realmente guardados.
- Em cada instante: com probabilidade `Settings::silo_prob_perda` perde o item mais antigo (apagado, e anunciado no painel); se não o perdeu, tenta entregar o mais antigo à máquina vizinha na direção de saída. Se ela aceitar, o nó é retirado sem apagar o item (passou a ser da outra máquina).
- O destrutor liberta todos os nós e itens: vender um silo com itens perde-os, sem fugas de memória.
- O silo ainda não tem `melhora` (entrega final): a probabilidade de perda está num atributo, pronto para ser reduzida.

## 7. Testes

Na pasta `extras/testes` há ficheiros para o `executa` (sintaxe, `fabrica`/`carrega`, `executa` aninhado, `ajuda`/`fim`, máquinas, erros de compra e silo) e um teste interno do silo (`teste_silo.cpp`), que insere itens à mão porque ainda nenhuma máquina os produz. O teste do silo corre com a perda a 0% (nunca perde; o mais antigo sai primeiro) e a 100% (perde um item por instante) e sem fugas de memória. O README da pasta explica o resultado esperado de cada ficheiro.

## 8. Participação individual

**Gabriel Costa**
- As 17 classes `CmdXxx` e o `RegistoComandos`: validação e ajuda de todos os comandos e ligação do `compra`, `vende`, `roda`, `avanca` e `estado` à fábrica.
- Hierarquia `Item` (7 classes) e o `Silo` (lista ligada própria).
- Ficheiros de teste do `executa` e teste interno do silo; este relatório.
- Checkpoint 1: `Ecra` e `Coordenada`.

**Filipe Fadigas**
- `Simulador` (ciclo de leitura, `processaLinha`, `executaFicheiro`) e `main`.
- Classe base `Comando` e funções de validação de apoio.
- Hierarquia `Maquina` e os tipos `Perfuradora`, `Transportador`, `Refinaria`, `Oficina` e `Lancador`.
- `Fabrica` com máquinas: `Posicao` a guardar a máquina, `compraMaquina`, `vendeMaquina`, `rodaMaquina`, `avancaInstante`, `estado`, painel e libertação da memória.
