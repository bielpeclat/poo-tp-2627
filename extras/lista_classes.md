# Lista de classes — planeamento

| Classe | Papel |
|---|---|
| `Ecra` | Buffer de caracteres genérico. Não sabe nada da fábrica |
| `Posicao` (ou `Celula`) | Terreno (solo, cratera ou depósito), tipo de matéria-prima, quantidade, e a máquina que lá estiver |
| `Fabrica` | Grelha de posições, créditos, instante, máquinas, engenheiros, itens enviados |
| `Vista` (ou `Desenhador`) | Desenha a `Fabrica` e o painel dentro de um `Ecra`. Assim o `Ecra` continua genérico |
| `Simulador` | Lê comandos, interpreta-os e mantém a fábrica e as cópias gravadas |
| `Maquina` (abstrata) → `Perfuradora`, `Transportador`, `Refinaria`, `Oficina`, `Silo`, `Lancador` | Hierarquia de máquinas |
| `Item` (abstrata) → `MateriaPrima` (ferro, silício, gelo), `ProdutoRefinado` (placa, silício puro, água), `KitHabitat` | Hierarquia de itens |
| `Engenheiro` | ID, nome, máquina associada |
| `Comando` (abstrata) → `CmdFabrica`, `CmdCarrega`, `CmdCompra`, … | Um comando por classe, com `executa()` virtual |
