# Instruções — classe Ecra

## Ideia central

O terminal só imprime "para a frente e para baixo": não dá para voltar atrás e
escrever na linha 3, coluna 20. Por isso a classe `Ecra` funciona como uma
**folha de papel em memória** (um array 2D de chars):

1. desenhamos tudo na folha, por qualquer ordem e em qualquer posição;
2. no fim, `mostra()` imprime a folha inteira de uma vez, de cima para baixo.

Nada aparece no terminal até se chamar `mostra()`.

O **cursor virtual** são só dois inteiros (`cursorL`, `cursorC`) dentro do
objeto: indicam onde vai cair o próximo caracter escrito, como a posição da
caneta em cima da folha. Não tem nada a ver com o cursor do terminal.

## Quando é usada

Sempre que for preciso mostrar o ecrã (depois de cada comando que muda a
fábrica e depois de cada instante):

```cpp
ecra.limpa();                       // apaga o desenho anterior
ecra.moldura(0, 0, nl + 3, nc + 3); // moldura da fábrica
ecra.escreve(1, 2, "ABCDEFGHIJ");   // régua das colunas
ecra.escreve(2, 1, 'A');            // régua das linhas (uma letra por linha)
ecra.escreve(2, 2, '%');            // conteúdo de cada posição da fábrica
ecra.moldura(0, 30, 10, 35);        // moldura do painel
ecra.escreve(1, 32, "Instante: ");  // texto do painel
ecra.escreve(57);                   // continua onde o cursor ficou
ecra.mostra();                      // só agora aparece no terminal
```

Quem faz estas chamadas é a classe `Vista`, não o `Ecra`: o `Ecra` não sabe o
que é uma fábrica, só sabe pôr caracteres em posições.

## Para que serve cada função

| Função | O que faz | Quando se usa |
|---|---|---|
| `Ecra(l, c)` | Cria a folha com `l` linhas e `c` colunas (no máximo o que está em `Settings`) e limpa-a | Uma vez, no início |
| `limpa()` | Põe `' '` em todo o buffer e o cursor em (0,0) | Antes de redesenhar |
| `posiciona(l, c)` | Move o cursor virtual para (l, c). Não escreve nada | Antes de escrever em sequência |
| `escreve(char)` | Escreve 1 caracter no cursor e avança o cursor uma coluna (muda de linha se chegar ao fim) | **É o núcleo**: todas as outras usam esta |
| `escreve(string)` | Escreve o texto a partir do cursor, chamando `escreve(char)` para cada letra | Texto que continua o anterior |
| `escreve(int)` | Converte o número em texto e escreve-o | Números do painel (créditos, instante) |
| `escreve(l, c, char)` | `posiciona(l, c)` + `escreve(char)` | Desenhar uma posição da fábrica |
| `escreve(l, c, string)` | `posiciona(l, c)` + `escreve(string)` | Escrever uma linha do painel |
| `moldura(l, c, alt, larg)` | Desenha um retângulo com `+`, `-` e `\|` | Moldura da fábrica e do painel |
| `mostra()` | Envia todas as linhas do buffer para o `cout` | No fim de cada redesenho |

Há vários `escreve` por causa da **sobrecarga** (overloading): é a mesma ação,
escrever, para tipos de dados diferentes (char, string, número) e com ou sem
posição. Só `escreve(char)` tem lógica a sério. As outras são atalhos que a
chamam, por isso as regras dos limites ficam num único sítio.

## Decisões de comportamento

| Situação | Decisão |
|---|---|
| Tamanho pedido acima do máximo | Fica no máximo de `Settings` |
| Escrever além da última coluna | Passa para a linha de baixo, na coluna 0 |
| Escrever além da última linha | É ignorado (cortado) |
| `posiciona` fora dos limites | É ignorado |
| Moldura | `+` nos cantos, `-` horizontal, `\|` vertical |

## Plano

1. **`Ecra.h`**: buffer `char buffer[Settings::ecra_max_linhas][Settings::ecra_max_colunas]`
   (array nativo, sem coleções), `nLinhas`, `nColunas`, `cursorL`, `cursorC`, e as
   funções da tabela.
2. **`Ecra.cpp`**, por esta ordem: construtor → `limpa` → `posiciona` →
   `escreve(char)` → os outros `escreve` → `moldura` → `mostra`.
3. **`CMakeLists.txt`**: acrescentar `Ecra.h` e `Ecra.cpp` ao `add_executable`.
4. **Testar no `main`**:
   - uma moldura normal com texto lá dentro;
   - uma moldura que sai fora do ecrã;
   - texto comprido, para ver se passa para a linha de baixo;
   - `escreve(-5, 3, "x")` e `escreve(100, 100, "x")`, que não podem dar erro;
   - compilar sem nenhum warning.
5. **Commit e push**, para o colega ter o `Ecra` pronto amanhã.

Extra opcional: `operator<<` para escrever `ecra << "Instante: " << 57;`.


================================================================================
================================================================================

# REVISÃO DO CÓDIGO — Ecra (03/11/2026)

> Tudo daqui para baixo foi acrescentado depois da revisão de `Ecra.h`,
> `Ecra.cpp`, `main.cpp` e `CMakeLists.txt`. O plano original está acima.

Estado atual: compila, mas com **5 warnings** (parâmetros não usados em
`escreve(char)` e `moldura`). Esses warnings desaparecem quando as funções
forem implementadas.

## A. Erros (corrigir primeiro)

### A1. `limpa()`: ciclo interior errado — GRAVE
`Ecra.cpp:30`
```cpp
for (int j = 0; i < nColunas; j++)   // ERRADO: compara i
for (int j = 0; j < nColunas; j++)   // CERTO
```
Como `i` nunca muda dentro deste ciclo, a condição é sempre verdadeira, e `j`
cresce sem parar e escreve fora do array. O programa rebenta (ou corrompe memória)
**logo no construtor**, porque o construtor chama `limpa()`. O compilador não avisa.

### A2. `posiciona()`: usa o máximo de `Settings` em vez do tamanho em uso
`Ecra.cpp:43` e `:50`: tem de comparar com `nLinhas` e `nColunas`. Se o ecrã for
criado com 20x50, `posiciona(30, 70)` é aceite e o cursor fica fora da parte
usada.

### A3. `posiciona()`: a coluna 0 é rejeitada
`Ecra.cpp:50`: `c < 1` devia ser `c < 0`. A coluna 0 é válida.

### A4. `posiciona()`: posição inválida manda o cursor para (0,0)
Quando a posição é inválida, o código põe o cursor em 0. Assim,
`escreve(-5, 3, "x")` escreve o `x` em (0,3), por cima do canto da moldura.
A decisão do plano é **ignorar** a escrita.

Solução simples: se a posição for inválida, pôr o cursor "fora" do ecrã, por
exemplo `cursorL = nLinhas`. O `escreve(char)` já vai ignorar tudo quando
`cursorL` está fora (ver A5). Assim, a escrita que vem a seguir é descartada.

Valida linha e coluna **em conjunto**: se uma delas for inválida, a posição
inteira é inválida. Hoje, uma linha válida com uma coluna inválida move a linha
e põe a coluna a 0.

### A5. `escreve(char)`: confunde a borda do ecrã com a moldura
`Ecra.cpp:57-64`: a função não escreve o `ch` e muda o cursor para a linha 1
quando está na linha 0 ou na última. Mas **a linha 0 e a última são linhas
válidas do ecrã**: o `Ecra` não sabe que existem molduras (ver a explicação
acima). A lógica deve ser só:

1. se `cursorL < 0` ou `cursorL >= nLinhas` → não faz nada, `return`;
2. `buffer[cursorL][cursorC] = ch;`
3. `cursorC++;`
4. se `cursorC == nColunas` → `cursorC = 0; cursorL++;`

## B. Por fazer

- [ ] `getLinhas()` e `getColunas()`: declaradas mas não implementadas. Ainda
      compila porque ninguém as chama, mas dá erro de linkagem quando forem usadas.
- [ ] `escreve(const std::string&)`: um ciclo que chama `escreve(char)` para
      cada caracter.
- [ ] `escreve(int l, int c, char)` e `escreve(int l, int c, const std::string&)`:
      `posiciona(l, c)` e depois o `escreve` correspondente.
- [ ] `escreve(int numero)`: está no plano mas falta no `.h`. Usar
      `std::to_string(numero)` e chamar `escreve(string)`. Dá jeito para o painel.
- [ ] `moldura(l, c, altura, largura)`, com altura e largura **a incluir as bordas**:
  - se `altura < 2` ou `largura < 2`, não desenha (decidir e comentar);
  - cantos: `+` em (l, c), (l, c+largura-1), (l+altura-1, c) e (l+altura-1, c+largura-1);
  - `-` nas linhas `l` e `l+altura-1`, das colunas `c+1` a `c+largura-2`;
  - `|` nas colunas `c` e `c+largura-1`, das linhas `l+1` a `l+altura-2`;
  - usar sempre `escreve(linha, coluna, ch)`. Com A4 corrigido, as partes que
    saem do ecrã são ignoradas uma a uma, e uma moldura meio fora desenha só a
    parte visível.
- [ ] `mostra()`: para cada linha `i < nLinhas`, enviar os `nColunas`
      caracteres e um `'\n'`. Precisa de `#include <iostream>` no `Ecra.cpp`.
- [ ] Testes no `main.cpp` (ainda não inclui o `Ecra.h`). Ver o passo 4 do plano.

## C. Melhorias (não são erros)

- `Ecra.h:21`: o comentário diz `''` mas deve ser `' '` (espaço).
  `Ecra.cpp:24`: o comentário diz "por tudo a 0", mas o que se põe são espaços.
- Construtor: usar a **lista de inicialização**
  (`Ecra::Ecra(int l, int c) : nLinhas(...), nColunas(...), cursorL(0), cursorC(0)`).
  É matéria de POO e os docentes gostam de ver. Os atributos ficam inicializados
  antes do corpo do construtor.
- Construtor: um valor `< 1` passa a ser o máximo. Funciona, mas fica a
  decisão por escrever no relatório (outra opção seria usar 1).
- `Ecra.cpp:5`: `#include "Settings.h"` é desnecessário, porque o `Ecra.h` já o
  inclui. Não faz mal.
- Indentação: o `Ecra` usa 3 espaços e o `main` usa 4. Escolham um e usem-no
  em todo o projeto.

## D. Atenção aos acentos dentro do Ecra

Já está em `extras/nao_esquecer.txt` não usar acentos no código. Isto também
vale para **os textos escritos no `Ecra`**: em UTF-8, `é` ocupa 2 bytes, ou seja,
2 posições do buffer. `"Créditos"` gasta 9 posições mas aparece com 8 letras,
e o `|` direito do painel fica desalinhado. Escrever `"Creditos"`.

## E. Ordem sugerida

1. A1 (limpa) → A5 (escreve char) → A2, A3, A4 (posiciona).
2. Os `escreve` que faltam → `mostra` → `moldura` → getters.
3. Testes no `main`, compilar, confirmar **0 warnings**.
4. Commit e push.
