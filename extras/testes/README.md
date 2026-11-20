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

## teste_executa_aninhado.txt
- `fabrica 5 5` cria a fabrica; o `executa` da linha 2 e recusado (nao se pode usar `executa` dentro de um ficheiro executado); `lposicao aa` na linha 3 continua a funcionar.

## teste_ajuda_fim.txt
- `ajuda` lista os 17 comandos; `ajuda <comando>` mostra a ajuda detalhada de cada um; `ajuda naoexiste` da erro; `fim` termina o programa (correr este ficheiro no fim).
