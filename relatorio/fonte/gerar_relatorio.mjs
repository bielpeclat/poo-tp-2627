// Gera o PDF do relatorio do Checkpoint 2 (mesmo estilo do relatorio do Checkpoint 1).
// Uso (a partir desta pasta):  npm install pdfkit && node gerar_relatorio.mjs <saida.pdf> [ecra.txt]
import fs from 'fs';
import PDFDocument from 'pdfkit';

const SAIDA = process.argv[2] || 'Relatorio_Checkpoint2_POO_2627.pdf';
const ECRA = process.argv[3] ? fs.readFileSync(process.argv[3], 'utf8').split('\n').filter(l => l.length) : [];
if (ECRA.length) ECRA[0] = ECRA[0].replace(/^> /, '');

const NAVY = '#1F3864', AZUL = '#2F5496', CINZA = '#595959', BORDA = '#BFBFBF', CABEC = '#D9E2F3', CAIXA = '#F2F2F2';
const W = 595.28, H = 841.89, ML = 71, MR = 71, TOP = 66, BOTTOM = H - 62, LARG = W - ML - MR;

// ---------------------------------------------------------------- texto com mistura de fontes
// Fontes embebidas (Liberation, equivalentes ao Arial); se nao existirem, usa as fontes base do PDF.
const DIR_FONTES = '/usr/share/fonts/truetype/liberation/';
const TEM_FONTES = fs.existsSync(DIR_FONTES + 'LiberationSans-Regular.ttf');
const FONTES = TEM_FONTES ? { n: 'F-n', b: 'F-b', c: 'F-c', i: 'F-i' }
                          : { n: 'Helvetica', b: 'Helvetica-Bold', c: 'Courier', i: 'Helvetica-Oblique' };
const FN = FONTES.n, FB = FONTES.b, FC = FONTES.c, FI = FONTES.i;
function runs(str) {            // `codigo` e **negrito**
  const out = [];
  const re = /(`[^`]+`|\*\*[^*]+\*\*)/g;
  let ultimo = 0, m;
  while ((m = re.exec(str))) {
    if (m.index > ultimo) out.push({ t: str.slice(ultimo, m.index), f: 'n' });
    const tok = m[0];
    if (tok[0] === '`') out.push({ t: tok.slice(1, -1), f: 'c' });
    else out.push({ t: tok.slice(2, -2), f: 'b' });
    ultimo = m.index + tok.length;
  }
  if (ultimo < str.length) out.push({ t: str.slice(ultimo), f: 'n' });
  return out;
}

const doc = new PDFDocument({ size: 'A4', margin: 0, bufferPages: true, info: {
  Title: 'Relatorio do Checkpoint 2 - Simulador de Fabrica em Marte', Author: 'Gabriel Costa, Filipe Fadigas' } });
doc.pipe(fs.createWriteStream(SAIDA));
if (TEM_FONTES) {
  doc.registerFont('F-n', DIR_FONTES + 'LiberationSans-Regular.ttf');
  doc.registerFont('F-b', DIR_FONTES + 'LiberationSans-Bold.ttf');
  doc.registerFont('F-i', DIR_FONTES + 'LiberationSans-Italic.ttf');
  doc.registerFont('F-c', DIR_FONTES + 'LiberationMono-Regular.ttf');
}

function tam(f, size, s) { return doc.font(FONTES[f]).fontSize(f === 'c' ? size - 1 : size).widthOfString(s); }

function layout(str, largura, size, fonteBase = 'n') {
  const palavras = [];
  for (const r of runs(str)) {
    const f = r.f === 'n' ? fonteBase : r.f;
    for (const p of r.t.split(/( )/)) if (p !== '') palavras.push({ t: p, f });
  }
  const linhas = []; let atual = [], x = 0;
  for (const p of palavras) {
    const w = tam(p.f, size, p.t);
    if (p.t === ' ' && atual.length === 0) continue;
    if (x + w > largura && p.t !== ' ' && atual.length) {
      while (atual.length && atual[atual.length - 1].t === ' ') { x -= atual.pop().w; }
      linhas.push(atual); atual = []; x = 0;
    }
    atual.push({ ...p, w, x }); x += w;
  }
  while (atual.length && atual[atual.length - 1].t === ' ') atual.pop();
  if (atual.length) linhas.push(atual);
  return linhas;
}
function asc(f, size) { doc.font(FONTES[f]).fontSize(size); return doc._font.ascender / 1000 * size; }
function desenha(linhas, x, y, size, cor = '#000000', lh = size * 1.32, centrado = 0) {
  linhas.forEach((l, i) => {
    let off = 0;
    if (centrado) { const tot = l.reduce((a, s) => a + s.w, 0); off = (centrado - tot) / 2; }
    let cx = x + off;
    for (const s of l) {
      const dy = s.f === 'c' ? asc('n', size) - asc('c', size - 1) : 0;   // alinha a linha de base do codigo com o texto
      doc.font(FONTES[s.f]).fontSize(s.f === 'c' ? size - 1 : size).fillColor(cor).text(s.t, cx, y + i * lh + dy, { lineBreak: false });
      cx += s.w;
    }
  });
  return linhas.length * lh;
}

// ---------------------------------------------------------------- paginas
let y = TOP, pagina = 0;                 // pagina = indice (0 = capa)
const titulos = [];                      // {nivel, texto, pagina}
let paginasAnteriores = {};              // 1.a passagem -> numeros de pagina para o indice
function novaPagina() { doc.addPage(); pagina++; y = TOP; }
function garante(h) { if (y + h > BOTTOM) novaPagina(); }

function h1(texto) {
  garante(60); y += 8;
  titulos.push({ nivel: 1, texto, pagina });
  doc.font(FB).fontSize(14).fillColor(NAVY).text(texto, ML, y, { lineBreak: false });
  y += 24;
}
function h2(texto) {
  garante(46); y += 4;
  titulos.push({ nivel: 2, texto, pagina });
  doc.font(FB).fontSize(11.5).fillColor(AZUL).text(texto, ML, y, { lineBreak: false });
  y += 19;
}
function par(texto, size = 10.5, extra = 6) {
  const l = layout(texto, LARG, size);
  const lh = size * 1.32;
  for (let i = 0; i < l.length;) {   // permite partir o paragrafo entre paginas
    garante(lh * Math.min(2, l.length - i));
    const cabem = Math.max(1, Math.floor((BOTTOM - y) / lh));
    const fatia = l.slice(i, i + cabem);
    desenha(fatia, ML, y, size, '#000000', lh); y += fatia.length * lh; i += fatia.length;
  }
  y += extra;
}
function bullets(itens, size = 10.5) {
  for (const it of itens) {
    const l = layout(it, LARG - 16, size), lh = size * 1.32;
    garante(lh * Math.min(2, l.length));
    doc.font(FN).fontSize(size).fillColor('#000000').text('•', ML + 3, y, { lineBreak: false });
    for (let i = 0; i < l.length;) {
      garante(lh);
      const cabem = Math.max(1, Math.floor((BOTTOM - y) / lh));
      const fatia = l.slice(i, i + cabem);
      desenha(fatia, ML + 16, y, size, '#000000', lh); y += fatia.length * lh; i += fatia.length;
    }
    y += 3;
  }
  y += 3;
}
function tabela(colunas, cabecalho, linhas, size = 9.5) {
  const pad = 4, soma = colunas.reduce((a, b) => a + b, 0), esc = LARG / soma;
  const w = colunas.map(c => c * esc), lh = size * 1.3;
  const desenhaLinha = (cels, ehCab) => {
    const ls = cels.map((c, i) => layout(c, w[i] - 2 * pad, size, ehCab ? 'b' : 'n'));
    const h = Math.max(...ls.map(l => l.length)) * lh + 2 * pad;
    if (y + h > BOTTOM) { novaPagina(); cab(); return desenhaLinha(cels, ehCab); }
    let x = ML;
    cels.forEach((c, i) => {
      doc.rect(x, y, w[i], h).fillAndStroke(ehCab ? CABEC : '#FFFFFF', BORDA);
      desenha(ls[i], x + pad, y + pad + 1, size, ehCab ? NAVY : '#000000', lh);
      x += w[i];
    });
    y += h;
  };
  const cab = () => desenhaLinha(cabecalho, true);
  garante(60); cab();
  for (const l of linhas) desenhaLinha(l, false);
  y += 10;
}
function legenda(texto) {
  doc.font(FN).fontSize(9).fillColor(CINZA);
  const w = doc.widthOfString(texto);
  doc.text(texto, ML + (LARG - w) / 2, y, { lineBreak: false }); y += 16;
}

// ---------------------------------------------------------------- diagrama de classes
function diagrama(x0, y0) {
  const col = { e: 0, m: 158, d: 335 }, bw = 118;
  const P = (x, y) => [x0 + x, y0 + y];
  const caixa = (x, yy, h, t1, resto, opts = {}) => {
    const [px, py] = P(x, yy);
    doc.save();
    if (opts.tracejada) doc.dash(3, { space: 2 });
    doc.rect(px, py, bw, h).fillAndStroke(opts.tracejada ? '#FFFFFF' : CABEC, NAVY);
    doc.restore();
    const linhas = [t1, ...(Array.isArray(resto) ? resto : (resto ? [resto] : []))];
    const alt = linhas.length * 10;
    linhas.forEach((t, i) => {
      doc.font(i === 0 ? FB : (opts.abstrata && i === 0 ? FI : FN)).fontSize(i === 0 ? 8.5 : 7.5).fillColor(NAVY);
      const w = doc.widthOfString(t);
      doc.text(t, px + (bw - w) / 2, py + (h - alt) / 2 + i * 10 + 1, { lineBreak: false });
    });
  };
  const linha = (a, b, c, d, tracejada) => {
    doc.save(); if (tracejada) doc.dash(3, { space: 2 });
    doc.moveTo(...P(a, b)).lineTo(...P(c, d)).lineWidth(0.8).strokeColor(NAVY).stroke(); doc.restore();
  };
  const losango = (x, yy, dx, dy) => {   // ponta em (x,yy), a apontar para tras (dx,dy = direcao da linha)
    const L = 14, Wd = 4, px = -dy, py = dx;
    const pts = [[x, yy], [x + dx * L / 2 + px * Wd, yy + dy * L / 2 + py * Wd], [x + dx * L, yy + dy * L], [x + dx * L / 2 - px * Wd, yy + dy * L / 2 - py * Wd]];
    doc.polygon(...pts.map(p => P(p[0], p[1]))).fillAndStroke(NAVY, NAVY);
  };
  const triangulo = (x, yy, dx, dy) => {  // ponta em (x,yy)
    const L = 10, Wd = 5, px = -dy, py = dx;
    const pts = [[x, yy], [x + dx * L + px * Wd, yy + dy * L + py * Wd], [x + dx * L - px * Wd, yy + dy * L - py * Wd]];
    doc.polygon(...pts.map(p => P(p[0], p[1]))).fillAndStroke('#FFFFFF', NAVY);
  };
  const seta = (x, yy, dx, dy) => {       // ponta aberta em (x,yy); dx,dy aponta para o lado oposto
    const L = 7, Wd = 3.5, px = -dy, py = dx;
    doc.save().moveTo(...P(x + dx * L + px * Wd, yy + dy * L + py * Wd)).lineTo(...P(x, yy)).lineTo(...P(x + dx * L - px * Wd, yy + dy * L - py * Wd)).lineWidth(0.8).strokeColor(NAVY).stroke().restore();
  };
  const txtEsq = (t, xDir, yy) => { doc.font(FN).fontSize(7); const w = doc.widthOfString(t); doc.fillColor(CINZA).text(t, ...P(xDir - w, yy), { lineBreak: false }); };
  const txt = (t, x, yy) => { doc.font(FN).fontSize(7).fillColor(CINZA).text(t, ...P(x, yy), { lineBreak: false }); };

  // caixas
  caixa(col.e, 0, 30, 'Comando', '«abstrata»', { abstrata: true });
  caixa(col.e, 62, 30, 'CmdXxx', '17 classes (1 por comando)');
  caixa(col.e, 124, 30, 'RegistoComandos', 'criaTodosComandos()');
  caixa(col.m, 0, 30, 'Simulador');
  caixa(col.m, 62, 30, 'Ecra');
  caixa(col.m, 124, 30, 'Engenheiro', 'planeada (so o .h)', { tracejada: true });
  caixa(col.d, 0, 30, 'Fabrica');
  caixa(col.d, 62, 30, 'Posicao');
  caixa(col.d, 124, 30, 'Maquina', '«abstrata»', { abstrata: true });
  caixa(col.d, 186, 46, '6 tipos de máquina', ['Perfuradora, Transportador,', 'Refinaria, Oficina,', 'Lancador, Silo']);
  caixa(col.d, 270, 30, 'Item', '«abstrata»', { abstrata: true });
  caixa(col.d, 338, 46, '7 itens', ['MinerioFerro, SilicioBruto, Gelo,', 'PlacaFerro, SilicioPuro, Agua,', 'KitHabitat']);

  const cx = col.d + bw / 2;     // x da coluna da direita
  // relacoes
  linha(col.m + bw, 15, col.d, 15); losango(col.m + bw, 15, 1, 0); txt('1', col.m + bw + 22, 6);      // Simulador possui Fabrica
  linha(bw, 15, col.m, 15); losango(col.m, 15, -1, 0); txt('1..*', bw + 2, 6);                         // Simulador possui Comando
  linha(bw / 2, 62, bw / 2, 40); triangulo(bw / 2, 30, 0, 1);                                          // CmdXxx -> Comando (heranca)
  linha(bw / 2, 124, bw / 2, 99, true); seta(bw / 2, 92, 0, 1);                                        // Registo cria CmdXxx
  linha(col.m + 10, 30, bw, 136, true); seta(bw, 136, 1, -0.1);                                        // Simulador usa Registo
  linha(cx, 30, cx, 62); losango(cx, 30, 0, 1); txt('26x26', cx + 6, 40);                              // Fabrica possui Posicao
  linha(cx, 92, cx, 124); losango(cx, 92, 0, 1); txt('0..1', cx + 6, 104);                             // Posicao possui Maquina
  linha(cx, 166, cx, 186); triangulo(cx, 154, 0, 1);                                                   // tipos -> Maquina
  linha(cx, 232, cx, 270); losango(cx, 232, 0, 1); txtEsq('Transportador e Silo', cx - 6, 248);        // tipos possuem Item
  linha(cx, 310, cx, 338); triangulo(cx, 300, 0, 1);                                                   // itens -> Item
  linha(col.d + 10, 30, col.m + bw, 73, true); seta(col.m + bw, 73, 1, -0.9);                          // Fabrica usa Ecra
  linha(col.m + bw, 139, col.d, 139, true); txt('associado', col.m + bw + 9, 129);                    // Engenheiro - Maquina
}

// ---------------------------------------------------------------- conteudo
function corpo() {
  h1('1. Introdução');
  par('Este relatório descreve o que fizemos no **Checkpoint 2** do trabalho prático de Programação Orientada a Objetos: um simulador de uma fábrica em Marte, feito em C++ e a correr na consola. Atualiza o relatório do Checkpoint 1, refletindo as classes efetivamente implementadas, as opções tomadas e a participação individual de cada um.');
  par('Neste checkpoint o enunciado pede a leitura e a validação de todos os comandos (pelo teclado e pelo `executa`), o `ajuda` completo, os comandos `fabrica`, `carrega`, `compra`, `vende`, `roda`, `avanca`, `estado` e `lposicao`, o Silo completo (sem `melhora`), o mecanismo de atuação das máquinas a cada instante planeado e iniciado, e a saída limpa com `fim`. Seguindo o pedido do docente, o projeto inclui também os ficheiros `.h` do `Engenheiro` (só o `.h`) e das máquinas (`Maquina` e os seis tipos); a implementação do `Engenheiro`, o `melhora`, o `grava`/`recupera` e o comportamento completo de cada máquina ficam para a entrega final. O projeto compila com `-Wall -Wextra -pedantic` sem avisos e foi testado com o AddressSanitizer, sem erros nem memória por libertar.');
  tabela([5, 1.4, 3.6], ['Requisito do Checkpoint 2', 'Estado', 'Onde está'], [
    ['Requisitos do Checkpoint 1', 'Feito', '`Ecra`, `Coordenada`, `Posicao`, `Fabrica`'],
    ['Leitura e validação de todos os comandos (teclado e `executa`)', 'Feito', '`Simulador::processaLinha`, `Comando::valida`'],
    ['`ajuda`, completo (sem e com parâmetro)', 'Feito', '`CmdAjuda`, `getAjuda` de cada comando'],
    ['`fabrica`, `carrega`, `lposicao`', 'Feito', '`CmdFabrica`, `CmdCarrega`, `CmdLPosicao`'],
    ['`compra`, `vende`, `roda`, `avanca`, `estado`', 'Feito', '`CmdCompra`, `CmdVende`, `CmdRoda`, `CmdAvanca`, `CmdEstado`, `Fabrica`'],
    ['Silo completo (sem `melhora`)', 'Feito', '`Silo`'],
    ['Mecanismo de atuação por instante, planeado e iniciado', 'Feito', '`Fabrica::avancaInstante`, `Maquina::atua`'],
    ['Saída limpa com `fim`', 'Feito', '`CmdFim`, destrutores do `Simulador`, `Fabrica`, `Maquina`'],
    ['Relatório', 'Feito', 'Este documento'],
  ]);

  h1('2. Organização do projeto');
  bullets([
    'Cada classe tem o seu `.h` e o seu `.cpp`. Exceções: `Settings` e `Item` só têm `.h` com código (as classes concretas de itens têm os dois) e o `Engenheiro` só tem o `.h`, como pedido.',
    '`main.cpp`: cria um `Simulador` e chama `corre()`. Quando o programa termina, o destrutor do `Simulador` liberta tudo.',
    '`mapas/`: `mapa1.txt` (válido) e dois mapas com erros propositados, um com um carácter inválido e outro com uma linha de tamanho errado.',
    '`extras/testes/`: ficheiros de comandos para o `executa`, um teste interno do Silo (fora do projeto) e um `README` com o resultado esperado de cada um.',
    '`CMakeLists.txt`: C++20, avisos ativos, todos os `.cpp` e `.h` da raiz incluídos automaticamente (`file(GLOB ...)`) e cópia da pasta `mapas` para junto do executável.',
  ]);

  h1('3. Classes implementadas');
  h2('3.1 Settings');
  par('Reúne as constantes do simulador: tamanhos máximos do ecrã (40×80) e da fábrica (26×26), créditos iniciais, custos, durações, probabilidades de perda e valor dos itens. Todos os valores do enunciado são lidos daqui; nenhum está escrito no resto do código.');
  h2('3.2 Ecra');
  par('Buffer de caracteres (no máximo 40×80) com um cursor virtual. O resto do programa escreve nele em qualquer ordem (`posiciona`, `escreve`, `moldura`) e só no fim o `mostra()` envia tudo para o `cout`. Não sabe nada sobre a fábrica. Escrever fora do ecrã é ignorado.');
  h2('3.3 Coordenada');
  par('Traduz o texto do enunciado (duas letras minúsculas, por exemplo `ce`) para índices da grelha e vice-versa. `valida(texto, maxLinhas, maxColunas)` é estática e confirma o formato antes de se construir a `Coordenada`.');
  h2('3.4 Posicao');
  par('Uma célula do mapa: tipo de terreno (solo, cratera, ferro, silício ou gelo), quantidade de matéria-prima e, agora, um ponteiro para a `Maquina` que lá estiver (`getMaquina`, `colocaMaquina`, `retiraMaquina`). A classe protege as suas regras (nunca há um depósito com quantidade 0).');
  h2('3.5 Fabrica');
  par('Guarda o estado do mundo: tamanho, créditos, instante, a grelha de `Posicao` e o resumo do último instante. É dona das máquinas: o destrutor apaga todas, e a cópia está proibida para nunca haver duas fábricas a apagar as mesmas máquinas.');
  bullets([
    '`Fabrica(l, c)`, `carrega(ficheiro)`, `preparaEcra`, `listaPosicao(lc, raio)`: criação (aleatória ou por mapa), desenho (moldura, régua, terreno, máquinas por cima e painel) e consulta, como no Checkpoint 1, agora também com a máquina presente.',
    '`compraMaquina(tipo, pos, dir, erro)`: falha se a posição estiver fora, for uma cratera, estiver ocupada ou se não houver créditos; escreve a razão em `erro`. `vendeMaquina` devolve 50% do custo e `rodaMaquina` muda a direção de saída.',
    '`avancaInstante()`: incrementa o instante, limpa o resumo anterior e chama `atua` em cada máquina uma vez. `registaEvento(texto)` deixa as máquinas anunciarem o que aconteceu (aparece no painel). `getMaquinaVizinha(pos, dir)` diz a uma máquina quem está ao seu lado.',
    '`estado()`: texto do comando `estado` (instante, créditos e as máquinas com a sua descrição).',
  ]);
  h2('3.6 Simulador');
  par('Lê os comandos e liga-os à fábrica. É dono da `Fabrica` (criada por `fabrica` ou `carrega`, entregue por `defineFabrica`) e dos objetos `Comando`. `corre()` é o ciclo principal: lê uma linha com `getline` e termina com `fim` ou no fim da entrada. `processaLinha(linha)` é o único ponto de entrada de comandos, venham do teclado ou de ficheiro: (1) separa a linha em palavras, (2) procura o comando, (3) pede-lhe para validar, (4) verifica se precisa de fábrica e se ela já existe, (5) manda executar. `executaFicheiro` lê um ficheiro linha a linha e usa exatamente o mesmo `processaLinha`; recusa um `executa` dentro de outro.');
  h2('3.7 Comando e as classes CmdXxx');
  par('`Comando` é a classe base abstrata, com `getAjuda()`, `precisaFabrica()`, `valida(args, erro)` e `executa(sim, args)`. Tem funções de apoio para validar parâmetros: `verificaNumArgs`, `eInteiro`, `eDirecao`, `eTipoMaquina`, `eFormatoPosicao`, `posicaoNaFabrica` e `paraDirecao` (converte `c|b|e|d` em `Direcao`). Cada um dos 17 comandos é uma classe derivada que valida os seus próprios parâmetros, dá a sua própria ajuda (sintaxe, parâmetros, efeito, falhas, exemplo) e se executa:');
  bullets([
    'Com efeito: `ajuda`, `fabrica`, `carrega`, `executa`, `fim`, `lposicao`, `compra`, `vende`, `roda`, `avanca` e `estado`.',
    'Só validam (o `executa` informa que fica para a entrega final): `melhora`, `contrata`, `atribui`, `despede`, `grava` e `recupera`.',
  ]);
  h2('3.8 RegistoComandos');
  par('A função `criaTodosComandos()` devolve um `vector<Comando*>` com um objeto de cada comando. O `Simulador` chama-a no construtor, fica dono dos objetos e apaga-os no destrutor, por isso não precisa de ser alterado quando aparece um comando novo.');
  h2('3.9 Item e os itens concretos');
  par('`Item` é abstrata e só tem dados: `getNome()`, `getCaracter()` e `getValor()` (o valor vem do `Settings`). As sete classes concretas são `MinerioFerro`, `SilicioBruto`, `Gelo`, `PlacaFerro`, `SilicioPuro`, `Agua` e `KitHabitat`. A lógica de refinação fica para a entrega final.');
  h2('3.10 Maquina e os tipos de máquina');
  par('`Maquina` é abstrata: guarda a posição e a direção de saída e calcula o valor de venda (50% do custo). Cada tipo define `getCusto`, `getCaracter`, `getNome`, `getDescricao` (usada pelo `lposicao` e pelo `estado`) e as funções do mecanismo de instantes: `aceita(item)` (diz se pode receber), `recebe(item, instante)` (recebe mesmo) e `atua(fabrica)` (o que faz em cada instante). Os tipos são `Perfuradora` (`P`), `Transportador` (seta, ou o caracter do item que leva), `Refinaria` (`R`), `Oficina` (`O`), `Lancador` (`L`) e `Silo` (`S`). No Checkpoint 2 o `atua` da perfuradora, refinaria, oficina e lançador é um esqueleto; o `Transportador` e o `Silo` já entregam itens à máquina vizinha.');
  h2('3.11 Silo');
  par('Guarda itens de qualquer tipo, **sem limite de capacidade**, numa **lista ligada feita à mão** (o enunciado proíbe coleções da biblioteca standard). Cada nó guarda o item, o instante em que chegou e o ponteiro para o seguinte; a classe guarda o primeiro nó (o item mais antigo) e o último, por isso inserir no fim e retirar do início é direto e só se usa a memória dos itens realmente guardados. Em cada instante, com a probabilidade `Settings::silo_prob_perda` perde o item mais antigo (apagado e anunciado no painel); se não o perdeu, tenta entregar o mais antigo à máquina vizinha na direção de saída. O destrutor liberta todos os nós e itens, por isso vender um silo com itens perde-os sem fugas de memória.');
  h2('3.12 Engenheiro (apenas o .h)');
  par('Planeado para a entrega final. O `Engenheiro.h` declara o id automático (um contador partilhado, o primeiro é o 1), o nome, a máquina associada (ou `nullptr` se estiver livre) e as funções `associa` e `liberta`. Ainda não tem `.cpp`, não é usado por nenhuma outra classe e o painel continua a mostrar 0 engenheiros.');

  h1('4. Relação entre as classes');
  par('O diagrama mostra as classes implementadas (a azul) e a planeada para a entrega final (a tracejado). O losango é composição (quem possui apaga), o triângulo é herança e a seta tracejada é dependência. `Settings` e `Coordenada` são usadas por quase todas e não estão desenhadas para o diagrama não ficar cheio de linhas.');
  garante(396); diagrama(ML + (LARG - 453) / 2, y + 4); y += 396;
  legenda('Figura 1 – Diagrama de classes do Checkpoint 2.');
  tabela([2.4, 1.5, 5.6], ['Relação', 'Tipo', 'Porquê'], [
    ['`Simulador` e `Fabrica`', 'Composição', 'O `Simulador` cria-a (via `defineFabrica`) e apaga-a no destrutor.'],
    ['`Simulador` e `Comando`', 'Composição', 'Tem um objeto de cada comando e apaga-os no destrutor.'],
    ['`Simulador` e `RegistoComandos`', 'Dependência', 'Chama `criaTodosComandos()` no construtor para obter os comandos.'],
    ['`CmdXxx` e `Comando`', 'Herança', 'Cada comando é uma classe derivada; o `Simulador` só conhece `Comando*` (polimorfismo).'],
    ['`Fabrica` e `Posicao`', 'Composição', 'A grelha 26×26 de `Posicao` faz parte da `Fabrica`.'],
    ['`Posicao` e `Maquina`', 'Composição (0..1)', 'A máquina que está na posição é apagada pela `Fabrica` (destrutor, `vendeMaquina`).'],
    ['Tipos de máquina e `Maquina`', 'Herança', 'Cada máquina atua à sua maneira: comportamento em funções virtuais.'],
    ['`Transportador`/`Silo` e `Item`', 'Composição', 'Possuem os itens que guardam; ao entregar um item a outra máquina, deixam de ser donos.'],
    ['Itens concretos e `Item`', 'Herança', 'Só dados (nome, caracter, valor).'],
    ['`Fabrica` e `Ecra`', 'Dependência', 'Recebe o `Ecra` por referência em `preparaEcra`. O `Ecra` não conhece a `Fabrica`.'],
    ['Máquinas e `Fabrica`', 'Dependência', 'No `atua` perguntam à `Fabrica` quem é a máquina vizinha e anunciam eventos.'],
    ['`Engenheiro` e `Maquina`', 'Associação (planeada)', 'Um engenheiro livre ou associado a uma máquina; não é dono dela.'],
  ]);

  h1('5. Funcionalidades e testes');
  par('Testámos com ficheiros de comandos (`executa extras/testes/<ficheiro>`), com um teste interno do Silo e com programas de teste temporários. A figura é a saída real do ecrã depois de `carrega mapas/mapa1.txt`, `compra p ac b`, `compra t bc d`, `compra t bd d`, `compra l be d` e `avanca`: a perfuradora `P`, os transportadores `>` e o lançador `L` por cima do terreno, e o painel com instante 1, 810 créditos e 4 máquinas.');
  if (ECRA.length) {
    const lh = 9.6, h = ECRA.length * lh + 14;
    garante(h + 30);
    doc.rect(ML + 70, y, LARG - 140, h).fillAndStroke(CAIXA, BORDA);
    ECRA.forEach((l, i) => doc.font(FC).fontSize(8).fillColor('#000000').text(l, ML + 78, y + 7 + i * lh, { lineBreak: false }));
    y += h + 6;
    legenda('Figura 2 – Ecrã com máquinas, depois de um instante.');
  }
  tabela([3.3, 4.7], ['Teste', 'Resultado'], [
    ['`teste_sintaxe.txt`: todos os comandos com parâmetros a mais, a menos, não inteiros, tipo, posição ou direção inválidos', 'Cada um falha com o seu erro e mostra a sintaxe. Antes de existir fábrica, os comandos que a precisam são recusados.'],
    ['`teste_fabrica_carrega.txt`: `carrega` com mapa inválido, tamanho errado e ficheiro inexistente; `lposicao` com várias posições e raios', 'Os três falham e não criam fábrica; `mapa1.txt` carrega. `fabrica`/`carrega` repetidos são recusados. `lposicao aa 2` só lista as posições que existem; um raio enorme (`999999999`) responde logo.'],
    ['`teste_executa_aninhado.txt`', 'Um `executa` dentro de um ficheiro executado é recusado e o resto do ficheiro continua.'],
    ['`teste_ajuda_fim.txt`', '`ajuda` lista os 17 comandos; `ajuda <comando>` mostra a ajuda detalhada; `fim` termina o programa.'],
    ['`teste_maquinas.txt`', '`compra` coloca `P`, `>` e `L` no ecrã; `roda` muda a seta; `vende` devolve 50% (um transportador de 5 devolve 2); `vende`/`roda` sem máquina falham.'],
    ['`teste_compra_erros.txt`', 'Falha em cratera, em posição ocupada, fora da fábrica e sem créditos (4 oficinas deixam 195 e a 5.ª é recusada); depois de `vende`, a compra já funciona.'],
    ['`teste_silo.txt`', '`compra s` coloca um silo; `avanca 5` mostra 5 ecrãs; `vende` devolve 60 créditos (50% de 120).'],
    ['`teste_silo.cpp` (interno, fora do projeto)', 'Insere itens à mão: o mais antigo sai primeiro, aceita 500 itens (sem limite), com perda 0% nunca perde e com 100% perde um por instante, sem fugas de memória.'],
    ['Fila de transportadores (programa temporário)', 'Um item anda exatamente 1 posição por instante, tanto para a direita como para a esquerda, qualquer que seja a ordem em que a grelha é percorrida.'],
    ['AddressSanitizer e 40 execuções com 400 comandos aleatórios', 'Sem erros, sem comportamento indefinido e sem memória por libertar na saída com `fim` (ou no fim da entrada).'],
  ]);

  h1('6. Opções tomadas');
  bullets([
    '**Polimorfismo nos comandos.** O `Simulador` só conhece `Comando*`: não há nenhum `if`/`switch` por nome de comando. Para acrescentar um comando basta criar a classe e uma linha em `criaTodosComandos()`.',
    '**Duas validações.** `valida` só olha para o texto (não precisa da fábrica, por isso funciona mesmo antes de ela existir); só no `executa` se confirma que a posição cabe na fábrica criada.',
    '**Quem possui, apaga.** O `Simulador` apaga a fábrica e os comandos; a `Fabrica` apaga as máquinas; `Transportador` e `Silo` apagam os itens que guardam. A cópia da `Fabrica` e das máquinas está proibida (`= delete`) para evitar apagar a mesma memória duas vezes.',
    '**Um item anda no máximo 1 posição por instante.** Cada máquina que guarda itens regista o instante em que recebeu cada um e só o entrega num instante posterior, por isso o resultado não depende da ordem em que a grelha é percorrida.',
    '**Silo com lista ligada e ponteiro para o último nó.** Inserir no fim e retirar do início não obriga a percorrer a lista, e a memória usada é a dos itens guardados. A probabilidade de perda fica num atributo, pronto para o `melhora` da entrega final.',
    '**O executa é igual ao teclado.** Usa o mesmo `processaLinha`; só muda a origem do texto. Mostra cada linha antes de a executar e recusa um `executa` dentro de outro.',
    '**O avanca n mostra o ecrã a cada instante** e todos os comandos que alteram a fábrica (`compra`, `vende`, `roda`) voltam a mostrá-lo; quando uma ação falha, o utilizador é informado da razão.',
    '**Comandos ainda por fazer só validam.** `melhora`, `contrata`, `atribui`, `despede`, `grava` e `recupera` validam os parâmetros e, se estiverem certos, dizem que ficam disponíveis na entrega final.',
    '**Raio do lposicao limitado ao tamanho da fábrica.** Um raio maior mostra o mesmo que um raio do tamanho da fábrica, e assim um valor enorme não bloqueia o programa.',
    '**Sem adiantar matéria.** O `Engenheiro` só tem o `.h` pedido pelo docente; o `grava`/`recupera` e o comportamento completo das máquinas não foram começados.',
    'Sem acentos nem caracteres especiais no código, e todos os valores vêm do `Settings`.',
  ]);

  h1('7. Por fazer na entrega final');
  tabela([2.6, 5.4], ['Funcionalidade', 'Plano'], [
    ['`Engenheiro`', 'Fazer o `.cpp`, guardar os engenheiros na `Fabrica`, salário a cada instante e redução da duração das operações das máquinas associadas.'],
    ['`contrata`, `atribui`, `despede`, `melhora`', 'Passar do «só valida» para o efeito real (custos e melhorias do `Settings`).'],
    ['`grava` e `recupera`', 'Cópia da fábrica e de tudo o que ela contém. As máquinas são ponteiros, por isso é preciso um método virtual de duplicação em vez de copiar a `Fabrica`.'],
    ['Máquinas', '`Perfuradora` (extração do depósito e perda), `Refinaria` (transformação), `Oficina` (receita do kit de habitat) e `Lancador` (envio, perda e créditos), mais o `estado` com os itens enviados para a Terra.'],
  ]);

  h1('8. Participação individual');
  par('**Gabriel Costa**');
  bullets([
    'As 17 classes `CmdXxx` e o `RegistoComandos`: validação e ajuda de todos os comandos e ligação do `compra`, `vende`, `roda`, `avanca` e `estado` à fábrica.',
    'A hierarquia `Item` (7 classes concretas), o `Silo` e o `Engenheiro.h`.',
    'Ficheiros de teste do `executa`, teste interno do Silo, correção do raio do `lposicao` e este relatório.',
    'Checkpoint 1: `Ecra`, `Coordenada` e `Posicao`.',
  ]);
  par('**Filipe Fadigas**');
  bullets([
    'O `Simulador` (ciclo de leitura, `processaLinha`, `executaFicheiro`) e o `main`.',
    'A classe base `Comando` e as suas funções de validação de apoio.',
    'A hierarquia `Maquina` e os tipos `Perfuradora`, `Transportador`, `Refinaria`, `Oficina` e `Lancador`.',
    'A `Fabrica`: terreno, máquinas na grelha, `compraMaquina`, `vendeMaquina`, `rodaMaquina`, `avancaInstante`, `estado`, painel e libertação da memória.',
  ]);

  h1('9. Conclusão');
  par('Neste checkpoint o simulador passou a ser interativo: lê e valida os 17 comandos, pelo teclado ou por ficheiro, cria a fábrica, compra, vende e roda máquinas, avança no tempo e mostra o estado. O Silo está completo e o mecanismo de atuação por instante está montado e testado com os transportadores. Fica para a entrega final o comportamento completo das máquinas, os engenheiros, as melhorias e a gravação de cópias da fábrica.');
}

// ---------------------------------------------------------------- capa e indice
function capa() {
  const c = (t, yy, size, bold, cor = '#000000') => {
    doc.font(bold ? FB : FN).fontSize(size).fillColor(cor);
    doc.text(t, (W - doc.widthOfString(t)) / 2, yy, { lineBreak: false });
  };
  c('Instituto Superior de Engenharia de Coimbra', 100, 14, true, NAVY);
  c('Departamento de Engenharia Informática e de Sistemas', 120, 12, false);
  c('Licenciatura em Engenharia Informática · 2.º ano', 137, 12, false);
  c('Programação Orientada a Objetos · 2026/2027', 155, 12, false);
  doc.moveTo(ML + 40, 190).lineTo(W - MR - 40, 190).lineWidth(1.2).strokeColor(NAVY).stroke();
  c('Simulador de Fábrica em Marte', 258, 26, true, NAVY);
  c('Trabalho Prático', 296, 15, false, CINZA);
  doc.moveTo(ML + 40, 330).lineTo(W - MR - 40, 330).lineWidth(1.2).strokeColor(NAVY).stroke();
  c('Relatório do Checkpoint 2', 352, 18, true);
  const x0 = 120, w1 = 240, w2 = 115, ty = 440, rh = 22;
  const linhas = [['Aluno', 'N.º de aluno'], ['Gabriel Peclat dos Reis Costa', '2025140643'], ['Filipe Fadigas', '2018001655']];
  linhas.forEach((l, i) => {
    doc.rect(x0, ty + i * rh, w1, rh).fillAndStroke(i === 0 ? CABEC : '#FFFFFF', BORDA);
    doc.rect(x0 + w1, ty + i * rh, w2, rh).fillAndStroke(i === 0 ? CABEC : '#FFFFFF', BORDA);
    doc.font(i === 0 ? FB : FN).fontSize(11).fillColor(i === 0 ? NAVY : '#000000');
    doc.text(l[0], x0 + 8, ty + i * rh + 6, { lineBreak: false });
    doc.text(l[1], x0 + w1 + 8, ty + i * rh + 6, { lineBreak: false });
  });
  c('Novembro de 2026', 592, 12, false);
}
function indice() {
  doc.font(FB).fontSize(16).fillColor(NAVY).text('Índice', ML, TOP + 4, { lineBreak: false });
  let yy = TOP + 44;
  const itens = titulos.filter(t => t.nivel === 1 || t.nivel === 2);
  for (const t of itens) {
    const x = t.nivel === 1 ? ML : ML + 12;
    const size = t.nivel === 1 ? 10.5 : 10;
    const fonte = t.nivel === 1 ? FB : FN;
    const pg = String((paginasAnteriores[t.texto] ?? t.pagina) - 1);
    doc.font(fonte).fontSize(size).fillColor('#000000');
    const wt = doc.widthOfString(t.texto), wp = doc.widthOfString(pg);
    doc.text(t.texto, x, yy, { lineBreak: false });
    doc.font(FN).fontSize(size);
    const ponto = doc.widthOfString('. ');
    const livre = W - MR - wp - 4 - (x + wt + 4);
    doc.text('. '.repeat(Math.max(0, Math.floor(livre / ponto))), x + wt + 4, yy, { lineBreak: false });
    doc.text(pg, W - MR - wp, yy, { lineBreak: false });
    yy += t.nivel === 1 ? 18 : 15.5;
  }
}

// ---------------------------------------------------------------- execucao
capa();
novaPagina();           // pagina 1: indice (preenchido no fim, quando se sabem as paginas)
const paginaIndice = pagina;
novaPagina();           // pagina 2: comeca o corpo
corpo();
const total = pagina + 1;
doc.switchToPage(paginaIndice);
indice();
for (let i = 2; i < total; i++) {
  doc.switchToPage(i);
  const t = `POO 2026/2027 · Checkpoint 2 · Página ${i - 1}`;
  doc.font(FN).fontSize(8.5).fillColor(CINZA);
  doc.text(t, (W - doc.widthOfString(t)) / 2, H - 40, { lineBreak: false });
}
doc.end();
console.log('paginas:', total, '(corpo:', total - 2, ')');
