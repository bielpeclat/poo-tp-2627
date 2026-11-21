# Ficheiros de teste do executa

Correr a partir da pasta do projeto (onde existe `mapas/` e `extras/`), com `executa extras/testes/<ficheiro>`.
Cada linha e um comando, sem comentarios. Resultados esperados:

## teste_sintaxe.txt
- Linha 1 (`ajuda`) funciona.
- Linha 2: comando desconhecido.
- Linhas 3 a 7 (`compra`, `vende`, `avanca`, `estado`, `lposicao`): sintaxe certa, mas recusados por ainda nao existir fabrica.
- Linhas 8 a 13 (`fabrica` com parametros errados): erro especifico, nao cria fabrica.
- Linhas 14 e 15 (`ajuda 1 2`, `fim 1`): numero de parametros errado.
- Linha 16 (`fabrica 10 10`): cria a fabrica e mostra o ecra.
- Linhas 17 a 44: cada uma falha na validacao com o seu erro (tipo, posicao, direcao, inteiro, numero de parametros).

## teste_fabrica_carrega.txt
- Linhas 1 a 3: `carrega` falha (caracter invalido, tamanho errado, ficheiro inexistente) e nao cria fabrica.
- Linha 4: `lposicao` recusado, ainda nao ha fabrica.
- Linha 5: `carrega mapas/mapa1.txt` cria a fabrica (6x10) e mostra o ecra.
- Linhas 6 e 7: `fabrica` e `carrega` recusados, a fabrica ja existe.
- Linha 8: `ac` e um deposito de ferro. Linha 9: `bh` e uma cratera, com raio 1 mostra 9 posicoes.
- Linha 10: `ff` e valida (fabrica 6x10). Linha 11: `gg` esta fora da fabrica, erro.
- Linha 12: `lposicao aa 2` mostra so as posicoes que existem (canto).
- Linha 13: `lposicao aa 999999999` (raio enorme) responde logo, com as 60 posicoes da fabrica, sem ficar preso num ciclo.

## teste_executa_aninhado.txt
- `fabrica 5 5` cria a fabrica; o `executa` da linha 2 e recusado (nao se pode usar `executa` dentro de um ficheiro executado); `lposicao aa` na linha 3 continua a funcionar.

## teste_maquinas.txt
- Carrega `mapas/mapa1.txt` e compra uma perfuradora (`ac`), dois transportadores (`bc`, `bd`) e um lancador (`be`), cada uma com o seu caracter no ecra (`P`, seta, `L`).
- `avanca` mostra 1 ecra (instante 1). `roda bc b` muda a seta do transportador de `>` para `v`.
- `estado` e `lposicao bc 1` mostram as maquinas. `vende bd` devolve 50% do custo (5 -> 2, os creditos sobem 2). Segundo `vende bd`, `roda bd c` e `vende ff` falham (nao ha maquina).

## teste_compra_erros.txt
- `compra p bh d`: cratera. `compra t ba b` (apos comprar em `ba`): posicao ocupada. `compra t ga d` e `compra t zz d`: fora da fabrica (6x10).
- 4 oficinas (800 creditos) deixam 195 creditos: a 5.a e a 6.a oficina falham por creditos insuficientes.
- `vende da` devolve 100 creditos e a compra seguinte (`df`) ja funciona (95 creditos no fim).

## teste_silo.txt
- Compra um silo (`ca`) e dois transportadores (`cb`, `cc`); `lposicao ca 2` mostra o silo vazio; `avanca 5` mostra 5 ecras (silo e transportadores vazios, nada a assinalar).
- `vende ca` devolve 60 creditos (50% de 120) e `vende cb` e `vende cc` devolvem 2 cada.
- Os itens do silo (perda, ordem do mais antigo, sem limite) testam-se em `teste_silo.cpp` (ver abaixo).

## teste_silo.cpp + corre_teste_silo.sh (teste interno, fora do projeto e do zip)
- Como no CP2 nenhuma maquina produz itens, este programa insere itens a mao no silo.
- `bash extras/testes/corre_teste_silo.sh` (a partir da pasta do projeto) compila com AddressSanitizer e corre com a perda a 0% (nunca perde, o mais antigo sai primeiro) e a 100% (perde um por instante). Sem fugas de memoria e sem warnings. O `Settings.h` original nao e alterado (usa uma copia).

## teste_ajuda_fim.txt
- `ajuda` lista os 17 comandos; `ajuda <comando>` mostra a ajuda detalhada de cada um; `ajuda naoexiste` da erro; `fim` termina o programa (correr este ficheiro no fim).
