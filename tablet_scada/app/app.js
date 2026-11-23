/*
 * EmPowerElas - SCADA do tablet (lado do navegador)
 *
 * Duas formas de usar, como no Elipse:
 *   - Execucao: a tela mostra a maquete ao vivo e manda comandos;
 *   - Edicao: arrasta componentes, liga cada um a uma tag do IED e salva.
 *
 * As telas ficam no servidor (telas.json), entao todo tablet ve a mesma.
 */
"use strict";

const $ = (s) => document.querySelector(s);
const SVGNS = "http://www.w3.org/2000/svg";
const GRADE = 10;
const POS = { MOVIMENTO: 0, ABERTO: 1, FECHADO: 2 };   // convencao do projeto (manobra.c)

const app = {
  cfg: null,          // catalogo e IEDs, vindos do servidor
  telas: [],
  atual: 0,
  editando: false,
  copiaAntes: null,   // telas antes de entrar na edicao (para descartar)
  desfazer: [],
  sel: null,          // id do item selecionado
  valores: {},        // chave da tag -> {v, t, q} | {e} | null
  ieds: {},
  historico: {},      // chave da tag -> [[t, v], ...] (para as tendencias)
  ultimoEstado: {},   // id do item -> texto do estado (para os eventos)
  eventos: [],
  naoLidos: 0,
  ultimoEventoServidor: 0,
  semConexao: false,
  navegarCache: {},
};

// ---------------------------------------------------------------- utilidades
const esc = (s) => String(s ?? "").replace(/[&<>"']/g, (c) => ({ "&": "&amp;", "<": "&lt;", ">": "&gt;", '"': "&quot;", "'": "&#39;" }[c]));
const chaveTag = (t) => (t && t.ied && t.ref ? `${t.ied}:${t.fc || "ST"}:${t.ref}` : null);
const ajustar = (n) => Math.round(n / GRADE) * GRADE;
const novoId = () => Math.random().toString(36).slice(2, 9);
const clonar = (o) => JSON.parse(JSON.stringify(o));
const hora = (t) => new Date(t).toLocaleTimeString("pt-BR");

async function api(caminho, opcoes = {}) {
  const r = await fetch(caminho, {
    method: opcoes.method || "GET",
    headers: opcoes.body ? { "Content-Type": "application/json" } : undefined,
    body: opcoes.body ? JSON.stringify(opcoes.body) : undefined,
  });
  const dados = await r.json();
  if (!r.ok) throw new Error(dados.erro || `erro ${r.status}`);
  return dados;
}

function toast(texto, tipo = "") {
  const d = document.createElement("div");
  d.className = "toast " + tipo;
  d.textContent = texto;
  $("#toasts").append(d);
  setTimeout(() => d.remove(), tipo === "ruim" ? 6000 : 3500);
}

function lerTag(t) {
  const k = chaveTag(t);
  return k ? app.valores[k] : undefined;
}

// ---------------------------------------------------------------- componentes
/*
 * Cada tipo de componente diz: tamanho padrao, propriedades editaveis e como
 * desenhar. "tag" = valor lido do IED; "cmd" = objeto de controle.
 */
const COR = { fechado: "var(--fechado)", aberto: "var(--aberto)", mov: "var(--movimento)", sem: "var(--sem-dado)" };

function estadoPosicao(val) {
  if (!val || val.e !== undefined || val.v === undefined) return { cor: COR.sem, texto: "SEM DADO", chave: "?" };
  if (val.q === "i") return { cor: COR.sem, texto: "DADO INVÁLIDO", chave: "inv", invalido: true };
  if (val.v === POS.FECHADO) return { cor: COR.fechado, texto: "FECHADO", chave: "F" };
  if (val.v === POS.ABERTO) return { cor: COR.aberto, texto: "ABERTO", chave: "A" };
  if (val.v === POS.MOVIMENTO) return { cor: COR.mov, texto: "EM MOVIMENTO", chave: "M" };
  return { cor: COR.sem, texto: "INDEFINIDO", chave: "?" };
}

function textoNumero(val, casas) {
  if (!val || val.e !== undefined || typeof val.v !== "number") return "—";
  return val.v.toLocaleString("pt-BR", { minimumFractionDigits: casas, maximumFractionDigits: casas });
}

function cadeado(x, y) {
  return `<g transform="translate(${x} ${y})">
    <rect x="-9" y="-2" width="18" height="14" rx="3" fill="var(--movimento)"/>
    <path d="M-5 -2v-4a5 5 0 0 1 10 0v4" fill="none" stroke="var(--movimento)" stroke-width="3"/>
    <circle cx="0" cy="5" r="2" fill="#000"/></g>`;
}

const TIPOS = {
  disjuntor: {
    nome: "Disjuntor", w: 60, h: 60,
    props: [
      { k: "rotulo", r: "Rótulo", t: "texto", padrao: "DJ" },
      { k: "pos", r: "Posição (tag)", t: "tag" },
      { k: "cmd", r: "Comando abrir/fechar", t: "cmd" },
      { k: "liberada", r: "Intertravamento: fechar liberado (tag)", t: "tag", dica: "Booleano. Falso mostra o cadeado (ex.: CILO4.EnaCls). Abrir o disjuntor nunca é bloqueado." },
      { k: "mostrarEstado", r: "Mostrar ABERTO/FECHADO", t: "bool", padrao: true },
    ],
    desenhar(it, p) {
      const e = estadoPosicao(lerTag(p.pos));
      const { w, h } = it;
      const lib = lerTag(p.liberada);
      const bloqueado = lib && lib.e === undefined && lib.v === false;
      return `<rect width="${w}" height="${h}" rx="6" fill="${e.invalido ? "url(#hachura)" : e.cor}" stroke="#0006" stroke-width="2"/>
        ${bloqueado ? cadeado(-16, h / 2 - 6) : ""}
        <text x="${w / 2}" y="${h / 2 + 7}" text-anchor="middle" font-size="${Math.min(w, h) * 0.38}" font-weight="800" fill="#0b0f14">${esc(e.chave === "inv" ? "?" : e.chave)}</text>
        <text class="rotulo" x="${w + 10}" y="${h / 2 - 2}">${esc(p.rotulo)}</text>
        ${p.mostrarEstado !== false ? `<text class="rotulo-2" x="${w + 10}" y="${h / 2 + 16}">${e.texto}</text>` : ""}`;
    },
    estado: (p) => estadoPosicao(lerTag(p.pos)).texto,
  },

  chave: {
    nome: "Chave", w: 50, h: 90,
    props: [
      { k: "rotulo", r: "Rótulo", t: "texto", padrao: "CH" },
      { k: "pos", r: "Posição (tag)", t: "tag" },
      { k: "cmd", r: "Comando abrir/fechar", t: "cmd" },
      { k: "liberada", r: "Intertravamento: liberada (tag)", t: "tag", dica: "Booleano. Falso mostra o cadeado (ex.: CILO1.EnaOpn)." },
      { k: "mostrarEstado", r: "Mostrar ABERTA/FECHADA", t: "bool", padrao: true },
    ],
    desenhar(it, p) {
      const e = estadoPosicao(lerTag(p.pos));
      const { w, h } = it;
      const cx = w / 2, topo = 12, base = h - 12;
      const ang = e.chave === "F" ? 0 : e.chave === "M" ? 16 : e.chave === "A" ? 34 : 22;
      const comp = base - topo - 6;
      const rad = (ang * Math.PI) / 180;
      const xp = cx + Math.sin(rad) * comp, yp = base - Math.cos(rad) * comp;
      const lib = lerTag(p.liberada);
      const bloqueada = lib && lib.e === undefined && lib.v === false;
      const textoEstado = e.texto.replace("ABERTO", "ABERTA").replace("FECHADO", "FECHADA");
      return `<rect width="${w}" height="${h}" fill="transparent"/>
        <line x1="${cx}" y1="0" x2="${cx}" y2="${topo}" stroke="var(--linha)" stroke-width="5"/>
        <line x1="${cx}" y1="${base}" x2="${cx}" y2="${h}" stroke="var(--linha)" stroke-width="5"/>
        <line x1="${cx - 10}" y1="${topo}" x2="${cx + 10}" y2="${topo}" stroke="var(--linha)" stroke-width="4"/>
        <line x1="${cx}" y1="${base}" x2="${xp}" y2="${yp}" stroke="${e.invalido ? "var(--invalido)" : e.cor}" stroke-width="7" stroke-linecap="round" ${e.chave === "M" ? 'stroke-dasharray="8 5"' : ""}/>
        <circle cx="${cx}" cy="${base}" r="6" fill="${e.cor}" stroke="#0008" stroke-width="2"/>
        ${bloqueada ? cadeado(-16, h / 2 - 6) : ""}
        <text class="rotulo" x="${w + 8}" y="${h / 2 - 2}">${esc(p.rotulo)}</text>
        ${p.mostrarEstado !== false ? `<text class="rotulo-2" x="${w + 8}" y="${h / 2 + 16}">${textoEstado}</text>` : ""}`;
    },
    estado: (p) => estadoPosicao(lerTag(p.pos)).texto.replace("ABERTO", "ABERTA").replace("FECHADO", "FECHADA"),
  },

  medida: {
    nome: "Medida", w: 140, h: 76,
    props: [
      { k: "rotulo", r: "Rótulo", t: "texto", padrao: "Corrente" },
      { k: "tag", r: "Valor (tag)", t: "tag" },
      { k: "unidade", r: "Unidade", t: "texto", padrao: "A" },
      { k: "casas", r: "Casas decimais", t: "num", padrao: 0 },
      { k: "limite", r: "Alarme acima de (vazio = sem alarme)", t: "num", padrao: "" },
    ],
    desenhar(it, p) {
      const val = lerTag(p.tag);
      const n = val && typeof val.v === "number" ? val.v : null;
      const alarme = p.limite !== "" && p.limite != null && n != null && n > Number(p.limite);
      const inval = val && val.q === "i";
      const { w, h } = it;
      return `<rect width="${w}" height="${h}" rx="8" fill="${alarme ? "#4a1519" : "var(--superficie)"}" stroke="${alarme ? "var(--alarme)" : "var(--borda)"}" stroke-width="2"/>
        <text class="rotulo-2" x="12" y="20">${esc(p.rotulo).toUpperCase()}</text>
        <text class="rotulo-2" x="${w - 10}" y="20" text-anchor="end">${esc(p.unidade)}</text>
        <text class="valor" x="12" y="${h - 14}" font-size="${Math.min(30, h * 0.42)}" ${inval ? 'fill="var(--invalido)"' : ""}>${textoNumero(val, Number(p.casas) || 0)}</text>`;
    },
  },

  indicador: {
    nome: "Indicador", w: 180, h: 36,
    props: [
      { k: "rotulo", r: "Rótulo", t: "texto", padrao: "Indicação" },
      { k: "tag", r: "Estado (tag)", t: "tag" },
      { k: "textoOn", r: "Texto quando verdadeiro", t: "texto", padrao: "" },
      { k: "textoOff", r: "Texto quando falso", t: "texto", padrao: "" },
      { k: "corOn", r: "Cor quando verdadeiro", t: "cor", padrao: "#ff5a5f" },
      { k: "corOff", r: "Cor quando falso", t: "cor", padrao: "#3a4654" },
      { k: "piscar", r: "Piscar quando verdadeiro", t: "bool", padrao: false },
    ],
    desenhar(it, p) {
      const val = lerTag(p.tag);
      const ligado = val && val.e === undefined && (val.v === true || (typeof val.v === "number" && val.v !== 0));
      const r = Math.min(it.h / 2 - 2, 14);
      const texto = ligado ? p.textoOn : p.textoOff;
      return `<rect width="${it.w}" height="${it.h}" fill="transparent"/>
        <circle cx="${r + 2}" cy="${it.h / 2}" r="${r}" fill="${ligado ? p.corOn : p.corOff}" stroke="#0008" stroke-width="2" ${ligado && p.piscar ? 'class="piscar"' : ""}/>
        <text class="rotulo" x="${2 * r + 12}" y="${it.h / 2 + (texto ? -2 : 5)}">${esc(p.rotulo)}</text>
        ${texto ? `<text class="rotulo-2" x="${2 * r + 12}" y="${it.h / 2 + 15}">${esc(texto)}</text>` : ""}`;
    },
    estado: (p) => {
      const val = lerTag(p.tag);
      if (!val || val.e !== undefined) return null;
      const ligado = val.v === true || (typeof val.v === "number" && val.v !== 0);
      return ligado ? (p.textoOn || "LIGADO") : (p.textoOff || "DESLIGADO");
    },
  },

  botao: {
    nome: "Botão", w: 180, h: 56,
    props: [
      { k: "texto", r: "Texto", t: "texto", padrao: "Comando" },
      { k: "cmd", r: "Comando", t: "cmd" },
      { k: "modo", r: "Ao tocar", t: "opcoes", padrao: "alternar", opcoes: [["alternar", "Alternar (lê a tag e manda o contrário)"], ["fixo", "Mandar sempre o mesmo valor"]] },
      { k: "tag", r: "Estado atual (tag, para alternar)", t: "tag" },
      { k: "valor", r: "Valor fixo", t: "texto", padrao: "1" },
      { k: "textoAtivo", r: "Texto quando o estado é verdadeiro", t: "texto", padrao: "" },
      { k: "cor", r: "Cor", t: "cor", padrao: "#3d8bfd" },
      { k: "confirmar", r: "Pedir confirmação", t: "bool", padrao: true },
    ],
    desenhar(it, p) {
      const val = lerTag(p.tag);
      const ativo = val && val.v === true;
      const texto = ativo && p.textoAtivo ? p.textoAtivo : p.texto;
      return `<rect width="${it.w}" height="${it.h}" rx="10" fill="${esc(p.cor)}" ${ativo ? 'stroke="#fff" stroke-width="3"' : ""}/>
        <text x="${it.w / 2}" y="${it.h / 2 + 6}" text-anchor="middle" font-size="17" font-weight="700" fill="#fff">${esc(texto)}</text>`;
    },
  },

  texto: {
    nome: "Texto", w: 220, h: 34,
    props: [
      { k: "texto", r: "Texto", t: "texto", padrao: "Texto" },
      { k: "tamanho", r: "Tamanho", t: "num", padrao: 20 },
      { k: "cor", r: "Cor", t: "cor", padrao: "#e6ebf0" },
      { k: "negrito", r: "Negrito", t: "bool", padrao: true },
    ],
    desenhar(it, p) {
      return `<rect width="${it.w}" height="${it.h}" fill="transparent"/>
        <text x="0" y="${it.h / 2 + Number(p.tamanho) * 0.35}" font-size="${Number(p.tamanho) || 20}" fill="${esc(p.cor)}" font-weight="${p.negrito ? 700 : 400}">${esc(p.texto)}</text>`;
    },
  },

  barra: {
    nome: "Barra/linha", w: 200, h: 8,
    props: [{ k: "cor", r: "Cor", t: "cor", padrao: "#9aa7b4" }],
    desenhar: (it, p) => `<rect width="${it.w}" height="${it.h}" rx="2" fill="${esc(p.cor)}"/>`,
  },

  painel: {
    nome: "Painel", w: 300, h: 200,
    props: [
      { k: "titulo", r: "Título", t: "texto", padrao: "Painel" },
      { k: "cor", r: "Cor do fundo", t: "cor", padrao: "#151c25" },
    ],
    fundo: true,
    desenhar: (it, p) => `<rect width="${it.w}" height="${it.h}" rx="12" fill="${esc(p.cor)}" stroke="var(--borda)"/>
      ${p.titulo ? `<text class="rotulo-2" x="16" y="24" font-size="13">${esc(p.titulo).toUpperCase()}</text>` : ""}`,
  },

  tendencia: {
    nome: "Tendência", w: 420, h: 180,
    props: [
      { k: "titulo", r: "Título", t: "texto", padrao: "Tendência" },
      { k: "tag1", r: "Curva 1 (tag)", t: "tag" }, { k: "rot1", r: "Nome da curva 1", t: "texto", padrao: "1" }, { k: "cor1", r: "Cor 1", t: "cor", padrao: "#ff5a5f" },
      { k: "tag2", r: "Curva 2 (tag)", t: "tag" }, { k: "rot2", r: "Nome da curva 2", t: "texto", padrao: "2" }, { k: "cor2", r: "Cor 2", t: "cor", padrao: "#f5b83d" },
      { k: "tag3", r: "Curva 3 (tag)", t: "tag" }, { k: "rot3", r: "Nome da curva 3", t: "texto", padrao: "3" }, { k: "cor3", r: "Cor 3", t: "cor", padrao: "#3d8bfd" },
      { k: "min", r: "Mínimo do eixo", t: "num", padrao: 0 },
      { k: "max", r: "Máximo do eixo", t: "num", padrao: 1000 },
      { k: "janela", r: "Janela (s)", t: "num", padrao: 60 },
    ],
    desenhar(it, p) {
      const { w, h } = it;
      const x0 = 46, y0 = 34, x1 = w - 12, y1 = h - 22;
      const min = Number(p.min) || 0, max = Number(p.max) || 1, jan = (Number(p.janela) || 60) * 1000;
      const agora = Date.now();
      let s = `<rect width="${w}" height="${h}" rx="12" fill="var(--superficie)" stroke="var(--borda)"/>
        <text class="rotulo-2" x="16" y="22" font-size="13">${esc(p.titulo).toUpperCase()}</text>`;
      for (let i = 0; i <= 4; i++) {
        const y = y0 + ((y1 - y0) * i) / 4;
        const v = max - ((max - min) * i) / 4;
        s += `<line x1="${x0}" y1="${y}" x2="${x1}" y2="${y}" stroke="var(--grade)" stroke-width="1"/>
          <text class="rotulo-2" x="${x0 - 6}" y="${y + 4}" text-anchor="end" font-size="11">${Math.round(v)}</text>`;
      }
      let leg = 0;
      for (const n of [1, 2, 3]) {
        const k = chaveTag(p["tag" + n]);
        if (!k) continue;
        const pts = (app.historico[k] || []).filter(([t]) => agora - t <= jan)
          .map(([t, v]) => {
            const x = x1 - ((agora - t) / jan) * (x1 - x0);
            const y = y1 - ((Math.min(max, Math.max(min, v)) - min) / (max - min)) * (y1 - y0);
            return `${x.toFixed(1)},${y.toFixed(1)}`;
          });
        if (pts.length > 1) s += `<polyline points="${pts.join(" ")}" fill="none" stroke="${esc(p["cor" + n])}" stroke-width="2.5" stroke-linejoin="round"/>`;
        const ult = lerTag(p["tag" + n]);
        s += `<text x="${w - 14 - leg * 110}" y="22" text-anchor="end" font-size="12" fill="${esc(p["cor" + n])}">${esc(p["rot" + n])} ${textoNumero(ult, 0)}</text>`;
        leg++;
      }
      return s;
    },
  },
};

function novoItem(tipo, x, y) {
  const T = TIPOS[tipo];
  const props = {};
  for (const c of T.props) if (c.padrao !== undefined) props[c.k] = c.padrao;
  return { id: novoId(), tipo, x: ajustar(x), y: ajustar(y), w: T.w, h: T.h, props };
}

// ---------------------------------------------------------------- desenho
const tela = () => app.telas[app.atual];

function desenharAbas() {
  const nav = $("#abas");
  nav.innerHTML = "";
  app.telas.forEach((t, i) => {
    const b = document.createElement("button");
    b.textContent = t.nome;
    b.className = i === app.atual ? "ativa" : "";
    b.onclick = () => { app.atual = i; app.sel = null; app.ultimoEstado = {}; desenharTudo(); };
    nav.append(b);
  });
}

function desenharTudo() {
  const t = tela();
  const svg = $("#tela");
  if (!t) { $("#camada").innerHTML = ""; return; }
  svg.setAttribute("viewBox", `0 0 ${t.largura} ${t.altura}`);
  const fundo = $("#fundo");
  fundo.setAttribute("width", t.largura);
  fundo.setAttribute("height", t.altura);
  desenharAbas();
  desenharItens();
  desenharPropriedades();
}

function desenharItens() {
  const t = tela();
  if (!t) return;
  // paineis ficam sempre atras
  const ordem = [...t.itens].sort((a, b) => (TIPOS[b.tipo]?.fundo ? 1 : 0) - (TIPOS[a.tipo]?.fundo ? 1 : 0));
  let s = "";
  for (const it of ordem) {
    const T = TIPOS[it.tipo];
    if (!T) continue;
    let corpo;
    try { corpo = T.desenhar(it, it.props || {}); } catch (e) { corpo = `<rect width="${it.w}" height="${it.h}" fill="var(--invalido)"/>`; }
    s += `<g class="item" data-id="${it.id}" transform="translate(${it.x} ${it.y})">${corpo}</g>`;
  }
  $("#camada").innerHTML = s;
  desenharSelecao();
}

function desenharSelecao() {
  const g = $("#camada-selecao");
  const it = app.editando && itemSelecionado();
  if (!it) { g.innerHTML = ""; return; }
  g.innerHTML = `<rect class="selecao" x="${it.x - 4}" y="${it.y - 4}" width="${it.w + 8}" height="${it.h + 8}" rx="4"/>
    <circle class="alca" data-alca="1" cx="${it.x + it.w + 4}" cy="${it.y + it.h + 4}" r="11"/>`;
}

const itemSelecionado = () => tela()?.itens.find((i) => i.id === app.sel) || null;

// ---------------------------------------------------------------- leitura ciclica
function tagsDaTela() {
  const t = tela();
  const chaves = new Set();
  if (!t) return [];
  for (const it of t.itens) {
    const T = TIPOS[it.tipo];
    if (!T) continue;
    for (const c of T.props) if (c.t === "tag") {
      const k = chaveTag(it.props?.[c.k]);
      if (k) chaves.add(k);
    }
  }
  return [...chaves];
}

async function ciclo() {
  try {
    const r = await api("/api/estado", { method: "POST", body: tagsDaTela() });
    const agora = Date.now();
    for (const [k, v] of Object.entries(r.valores)) {
      app.valores[k] = v;
      if (v && typeof v.v === "number" && v.t === "f") {
        const h = (app.historico[k] ||= []);
        h.push([agora, v.v]);
        while (h.length && agora - h[0][0] > 300000) h.shift();
      }
    }
    app.ieds = r.ieds;
    desenharStatus();
    if (app.semConexao) { app.semConexao = false; $("#aviso-conexao").hidden = true; }
    detectarMudancas();
    if (!arrasto) desenharItens();
  } catch (e) {
    if (!app.semConexao) { app.semConexao = true; $("#aviso-conexao").hidden = false; }
  }
  setTimeout(ciclo, 500);
}

function desenharStatus() {
  const d = $("#status-ieds");
  d.innerHTML = Object.entries(app.ieds).map(([k, i]) =>
    `<span class="pilula ${i.conectado ? "ok" : ""}" title="${esc(i.nome)}">${esc(k)}</span>`).join("")
    + (app.cfg?.simulado ? `<span class="pilula" style="color:var(--movimento)">SIMULADO</span>` : "");
}

// ---------------------------------------------------------------- eventos
function adicionarEvento(texto, tipo, t = Date.now(), detalhe = "") {
  app.eventos.unshift({ t, texto, tipo, detalhe });
  app.eventos = app.eventos.slice(0, 300);
  if ($("#painel-eventos").hidden) app.naoLidos++;
  desenharEventos();
}

function detectarMudancas() {
  const t = tela();
  if (!t) return;
  for (const it of t.itens) {
    const T = TIPOS[it.tipo];
    if (!T?.estado) continue;
    const nome = it.props?.rotulo;
    const est = T.estado(it.props || {});
    if (!est || !nome) continue;
    const antes = app.ultimoEstado[it.id];
    app.ultimoEstado[it.id] = est;
    if (antes !== undefined && antes !== est && est !== "EM MOVIMENTO")
      adicionarEvento(`${nome}: ${est}`, /ABERT|LIGADO|FALTA|GOOSE|INVÁLIDO|SEM DADO/.test(est) ? "ruim" : "bom");
  }
}

async function buscarEventosServidor() {
  try {
    const lista = await api(`/api/eventos?desde=${app.ultimoEventoServidor}`);
    for (const e of lista) {
      app.ultimoEventoServidor = e.id;
      adicionarEvento(e.texto, e.ok ? "bom" : "ruim", e.hora * 1000, e.origem);
    }
  } catch (e) { /* o aviso de conexao ja aparece pelo ciclo */ }
  setTimeout(buscarEventosServidor, 1500);
}

function desenharEventos() {
  const c = $("#contador-eventos");
  c.hidden = app.naoLidos === 0;
  c.textContent = app.naoLidos > 99 ? "99+" : app.naoLidos;
  const ol = $("#lista-eventos");
  if (!app.eventos.length) { ol.innerHTML = `<li class="vazio">Nenhum evento ainda. Manobras e mudanças de estado aparecem aqui.</li>`; return; }
  ol.innerHTML = app.eventos.map((e) =>
    `<li class="${e.tipo}"><time>${hora(e.t)}</time><span>${esc(e.texto)}</span>${e.detalhe ? `<small>${esc(e.detalhe)}</small>` : "<small></small>"}</li>`).join("");
}

// ---------------------------------------------------------------- comandos (execucao)
function abrirModal(html, largo = false) {
  const caixa = $("#modal-caixa");
  caixa.className = largo ? "largo" : "";
  caixa.innerHTML = html;
  $("#modal").hidden = false;
}
const fecharModal = () => { $("#modal").hidden = true; $("#modal-caixa").innerHTML = ""; };

async function enviarComando(cmd, valor, desc) {
  if (!cmd?.ied || !cmd?.ref) { toast("Este componente ainda não tem comando ligado. Edite a tela.", "ruim"); return; }
  try {
    const r = await api("/api/comando", { method: "POST", body: { ied: cmd.ied, ref: cmd.ref, tipo: cmd.tipo || "d", valor, desc } });
    if (r.ok) toast(`${desc}: comando aceito pelo IED`, "bom");
    else toast(`${desc}: o IED recusou — ${r.motivo}`, "ruim");
  } catch (e) {
    toast("Não consegui falar com o servidor da maquete.", "ruim");
  }
}

function tocarItem(it) {
  const p = it.props || {};
  if (it.tipo === "disjuntor" || it.tipo === "chave") {
    const chave = it.tipo === "chave";
    const e = estadoPosicao(lerTag(p.pos));
    const lib = lerTag(p.liberada);
    const bloqueada = lib && lib.e === undefined && lib.v === false;
    const estado = chave ? e.texto.replace("ABERTO", "ABERTA").replace("FECHADO", "FECHADA") : e.texto;
    abrirModal(`<h2>${esc(p.rotulo || (chave ? "Chave" : "Disjuntor"))}</h2>
      <p class="sub">${chave ? "Chave seccionadora" : "Disjuntor"}${p.cmd?.ref ? ` · <code>${esc(p.cmd.ref)}</code>` : ""}</p>
      <div class="estado-grande" style="color:${e.cor === COR.sem ? "var(--texto-2)" : e.cor}">${estado}</div>
      ${bloqueada ? (chave
        ? `<div class="alerta">Intertravamento: <b>bloqueada</b>. O disjuntor do vão está fechado, então o IED de controle vai recusar a manobra.</div>`
        : `<div class="alerta">Intertravamento: <b>fechar bloqueado</b>. A chave do vão está em movimento ou a proteção ainda está em trip. Abrir continua liberado.</div>`) : ""}
      <div class="botoes-comando">
        <button class="abrir" data-v="${POS.ABERTO}">ABRIR</button>
        <button class="fechar" data-v="${POS.FECHADO}">FECHAR</button>
      </div>
      <div class="rodape-modal"><button class="btn" data-fechar>Cancelar</button></div>`);
    $("#modal-caixa").querySelectorAll("[data-v]").forEach((b) => b.onclick = () => {
      fecharModal();
      const v = Number(b.dataset.v);
      enviarComando(p.cmd, v, `${p.rotulo || "Equipamento"} — ${v === POS.ABERTO ? "abrir" : "fechar"}`);
    });
  } else if (it.tipo === "botao") {
    let valor = p.valor;
    if (p.modo === "alternar") {
      const val = lerTag(p.tag);
      if (!val || val.e !== undefined) { toast("Ainda não sei o estado atual para alternar.", "ruim"); return; }
      valor = val.v === true || val.v === 1 ? 0 : 1;
    }
    const tipo = p.cmd?.tipo || "b";
    if (tipo === "b" && typeof valor === "string") valor = /^(1|true|sim|verdadeiro)$/i.test(valor.trim()) ? 1 : 0;
    const desc = p.texto || "Botão";
    if (p.confirmar === false) { enviarComando(p.cmd, valor, desc); return; }
    abrirModal(`<h2>${esc(desc)}</h2><p class="sub">Enviar <b>${esc(valor)}</b> para <code>${esc(p.cmd?.ref || "(sem comando ligado)")}</code>?</p>
      <div class="rodape-modal"><button class="btn" data-fechar>Cancelar</button><button class="btn btn-primario" id="confirmar">Enviar</button></div>`);
    $("#confirmar").onclick = () => { fecharModal(); enviarComando(p.cmd, valor, desc); };
  } else if (it.tipo === "medida" || it.tipo === "indicador") {
    const t = p.tag;
    const v = lerTag(t);
    abrirModal(`<h2>${esc(p.rotulo)}</h2><p class="sub"><code>${esc(t?.ref || "sem tag")}</code> (${esc(t?.ied || "")}, FC ${esc(t?.fc || "")})</p>
      <div class="estado-grande">${v && v.e === undefined ? esc(typeof v.v === "number" ? v.v.toLocaleString("pt-BR") : v.v) : "sem dado"}</div>
      <p class="sub">Qualidade: ${v?.q === "g" ? "boa" : v?.q === "i" ? "inválida" : v?.q === "q" ? "duvidosa" : "—"}</p>
      <div class="rodape-modal"><button class="btn" data-fechar>Fechar</button></div>`);
  }
}

// ---------------------------------------------------------------- edicao
let arrasto = null;

function pontoSvg(ev) {
  const svg = $("#tela");
  const pt = svg.createSVGPoint();
  pt.x = ev.clientX; pt.y = ev.clientY;
  return pt.matrixTransform(svg.getScreenCTM().inverse());
}

function guardarDesfazer() {
  app.desfazer.push(clonar(app.telas));
  if (app.desfazer.length > 60) app.desfazer.shift();
}

function configurarPonteiro() {
  const svg = $("#tela");
  // Execucao: abre o comando no "click", nao no "pointerdown". No toque, o
  // navegador dispara um click logo depois; se a janela abrisse no
  // pointerdown, esse click cairia no fundo dela e a fecharia na hora.
  svg.addEventListener("click", (ev) => {
    if (app.editando) return;
    const g = ev.target.closest(".item");
    const it = g && tela().itens.find((i) => i.id === g.dataset.id);
    if (it) tocarItem(it);
  });
  svg.addEventListener("pointerdown", (ev) => {
    const g = ev.target.closest(".item");
    if (!app.editando) return;
    const p = pontoSvg(ev);
    const sel = itemSelecionado();
    if (ev.target.dataset.alca && sel) {
      guardarDesfazer();
      arrasto = { modo: "tamanho", it: sel, x0: p.x, y0: p.y, w0: sel.w, h0: sel.h };
    } else if (g) {
      const it = tela().itens.find((i) => i.id === g.dataset.id);
      app.sel = it.id;
      guardarDesfazer();
      arrasto = { modo: "mover", it, dx: p.x - it.x, dy: p.y - it.y, mexeu: false };
      desenharPropriedades();
    } else {
      app.sel = null;
      desenharPropriedades();
    }
    desenharSelecao();
    if (arrasto) svg.setPointerCapture(ev.pointerId);
  });
  svg.addEventListener("pointermove", (ev) => {
    if (!arrasto) return;
    const p = pontoSvg(ev);
    const it = arrasto.it;
    const t = tela();
    if (arrasto.modo === "mover") {
      it.x = Math.max(0, Math.min(t.largura - 10, ajustar(p.x - arrasto.dx)));
      it.y = Math.max(0, Math.min(t.altura - 10, ajustar(p.y - arrasto.dy)));
      arrasto.mexeu = true;
    } else {
      it.w = Math.max(GRADE, ajustar(arrasto.w0 + p.x - arrasto.x0));
      it.h = Math.max(4, ajustar(arrasto.h0 + p.y - arrasto.y0) || 4);
    }
    const g = $(`#camada [data-id="${it.id}"]`);
    if (g) {
      if (arrasto.modo === "mover") g.setAttribute("transform", `translate(${it.x} ${it.y})`);
      else g.innerHTML = TIPOS[it.tipo].desenhar(it, it.props);
    }
    desenharSelecao();
  });
  const soltar = () => {
    if (!arrasto) return;
    if (arrasto.modo === "mover" && !arrasto.mexeu) app.desfazer.pop();
    arrasto = null;
    desenharItens();
    desenharPropriedades();
  };
  svg.addEventListener("pointerup", soltar);
  svg.addEventListener("pointercancel", soltar);
}

function entrarEdicao() {
  app.editando = true;
  app.copiaAntes = clonar(app.telas);
  app.desfazer = [];
  document.body.classList.add("editando");
  $("#barra-edicao").hidden = false;
  $("#btn-editar").textContent = "Sair da edição";
  $("#btn-editar").classList.add("ativo");
  desenharTudo();
}

function sairEdicao() {
  app.editando = false;
  app.sel = null;
  document.body.classList.remove("editando");
  $("#barra-edicao").hidden = true;
  $("#btn-editar").textContent = "Editar tela";
  $("#btn-editar").classList.remove("ativo");
  $("#propriedades").hidden = true;
  desenharTudo();
}

const houveMudanca = () => JSON.stringify(app.telas) !== JSON.stringify(app.copiaAntes);

async function salvar() {
  try {
    await api("/api/telas", { method: "PUT", body: { telas: app.telas } });
    app.copiaAntes = clonar(app.telas);
    toast("Tela salva. Os outros tablets veem a nova versão ao recarregar.", "bom");
    return true;
  } catch (e) {
    toast("Não consegui salvar: " + e.message, "ruim");
    return false;
  }
}

function pedirSaida() {
  if (!houveMudanca()) { sairEdicao(); return; }
  abrirModal(`<h2>Salvar as mudanças?</h2><p class="sub">Você mudou a tela e ainda não salvou.</p>
    <div class="rodape-modal"><button class="btn" data-fechar>Continuar editando</button>
    <button class="btn btn-perigo" id="m-descartar">Descartar</button><button class="btn btn-primario" id="m-salvar">Salvar</button></div>`);
  $("#m-descartar").onclick = () => { app.telas = app.copiaAntes; app.atual = Math.min(app.atual, app.telas.length - 1); fecharModal(); sairEdicao(); };
  $("#m-salvar").onclick = async () => { fecharModal(); if (await salvar()) sairEdicao(); };
}

function desenharPaleta() {
  const icones = {
    disjuntor: `<rect x="9" y="2" width="16" height="20" rx="3" fill="var(--fechado)"/>`,
    chave: `<path d="M17 2v4M17 18v4M17 18l7-11" stroke="var(--linha)" stroke-width="3" fill="none"/>`,
    medida: `<rect x="2" y="3" width="30" height="18" rx="3" fill="none" stroke="var(--linha)" stroke-width="2"/><text x="17" y="17" font-size="11" text-anchor="middle" fill="var(--texto)">123</text>`,
    indicador: `<circle cx="10" cy="12" r="7" fill="var(--alarme)"/><path d="M20 12h12" stroke="var(--linha)" stroke-width="2"/>`,
    botao: `<rect x="2" y="5" width="30" height="14" rx="4" fill="var(--destaque)"/>`,
    texto: `<text x="17" y="18" font-size="16" text-anchor="middle" font-weight="700" fill="var(--texto)">Aa</text>`,
    barra: `<rect x="2" y="10" width="30" height="5" fill="var(--linha)"/>`,
    painel: `<rect x="3" y="3" width="28" height="18" rx="4" fill="none" stroke="var(--linha)" stroke-width="2" stroke-dasharray="3 2"/>`,
    tendencia: `<path d="M2 18l7-6 6 3 7-10 10 7" stroke="var(--alarme)" stroke-width="2" fill="none"/>`,
  };
  $("#paleta").innerHTML = Object.entries(TIPOS).map(([k, T]) =>
    `<button data-tipo="${k}"><svg viewBox="0 0 34 24">${icones[k]}</svg>${T.nome}</button>`).join("");
  $("#paleta").querySelectorAll("button").forEach((b) => b.onclick = () => {
    const t = tela();
    if (!t) return;
    guardarDesfazer();
    const it = novoItem(b.dataset.tipo, t.largura / 2 - TIPOS[b.dataset.tipo].w / 2, t.altura / 2 - TIPOS[b.dataset.tipo].h / 2);
    t.itens.push(it);
    app.sel = it.id;
    desenharItens();
    desenharPropriedades();
  });
}

function textoVinculo(v, cmd) {
  if (!v?.ref) return `<code>(nada ligado)</code>`;
  return `<code>${esc(v.ied)} · ${cmd ? `tipo ${esc(v.tipo || "d")}` : esc(v.fc)} · ${esc(v.ref)}</code>`;
}

function desenharPropriedades() {
  const painel = $("#propriedades");
  const it = app.editando && itemSelecionado();
  if (!it) { painel.hidden = true; return; }
  painel.hidden = false;
  const T = TIPOS[it.tipo];
  const p = it.props;
  let s = `<h3>${T.nome}</h3>
    <div class="campo-linha">
      <label class="campo"><span>X</span><input type="number" data-geo="x" value="${it.x}" step="10"></label>
      <label class="campo"><span>Y</span><input type="number" data-geo="y" value="${it.y}" step="10"></label>
      <label class="campo"><span>Largura</span><input type="number" data-geo="w" value="${it.w}" step="10"></label>
      <label class="campo"><span>Altura</span><input type="number" data-geo="h" value="${it.h}" step="2"></label>
    </div>`;
  for (const c of T.props) {
    const v = p[c.k];
    if (c.t === "texto") s += `<label class="campo"><span>${c.r}</span><input data-k="${c.k}" value="${esc(v ?? "")}"></label>`;
    else if (c.t === "num") s += `<label class="campo"><span>${c.r}</span><input type="number" data-k="${c.k}" data-num="1" value="${esc(v ?? "")}"></label>`;
    else if (c.t === "cor") s += `<label class="campo"><span>${c.r}</span><input type="color" data-k="${c.k}" value="${esc(v || "#ffffff")}"></label>`;
    else if (c.t === "bool") s += `<label class="campo"><span>${c.r}</span><select data-k="${c.k}" data-bool="1"><option value="1" ${v ? "selected" : ""}>Sim</option><option value="0" ${!v ? "selected" : ""}>Não</option></select></label>`;
    else if (c.t === "opcoes") s += `<label class="campo"><span>${c.r}</span><select data-k="${c.k}">${c.opcoes.map(([o, r]) => `<option value="${o}" ${v === o ? "selected" : ""}>${r}</option>`).join("")}</select></label>`;
    else if (c.t === "tag" || c.t === "cmd") s += `<div class="campo"><span>${c.r}</span><div class="vinculo">${textoVinculo(v, c.t === "cmd")}
        <button class="btn" data-ligar="${c.k}" data-modo="${c.t}">Ligar…</button>${v?.ref ? `<button class="btn" data-soltar="${c.k}" title="Desligar">✕</button>` : ""}</div></div>`;
    if (c.dica) s += `<p class="dica">${c.dica}</p>`;
  }
  painel.innerHTML = s;

  painel.querySelectorAll("[data-geo]").forEach((inp) => inp.onchange = () => {
    guardarDesfazer();
    it[inp.dataset.geo] = Math.max(inp.dataset.geo === "h" ? 4 : 0, Number(inp.value) || 0);
    desenharItens();
  });
  painel.querySelectorAll("[data-k]").forEach((inp) => {
    const aplicar = () => {
      let v = inp.value;
      if (inp.dataset.bool) v = v === "1";
      else if (inp.dataset.num) v = v === "" ? "" : Number(v);
      it.props[inp.dataset.k] = v;
      desenharItens();
    };
    inp.onfocus = guardarDesfazer;
    inp.oninput = aplicar;
    inp.onchange = aplicar;
  });
  painel.querySelectorAll("[data-ligar]").forEach((b) => b.onclick = () => escolherVinculo(it, b.dataset.ligar, b.dataset.modo));
  painel.querySelectorAll("[data-soltar]").forEach((b) => b.onclick = () => {
    guardarDesfazer();
    delete it.props[b.dataset.soltar];
    desenharItens();
    desenharPropriedades();
  });
}

// Janela para escolher a tag/comando: catalogo da maquete ou navegando no IED
function escolherVinculo(it, campo, modo) {
  const cmd = modo === "cmd";
  let aba = "catalogo";
  let iedNav = it.props[campo]?.ied || Object.keys(app.cfg.ieds)[0];
  let filtro = "";
  let tipoCmd = it.props[campo]?.tipo || "d";

  const aplicar = (v) => {
    guardarDesfazer();
    it.props[campo] = v;
    fecharModal();
    desenharItens();
    desenharPropriedades();
  };

  async function render() {
    let lista = "";
    if (aba === "catalogo") {
      const itens = cmd ? app.cfg.catalogo.comandos : app.cfg.catalogo.tags;
      const grupos = {};
      for (const x of itens) {
        if (filtro && !(x.desc + " " + x.ref).toLowerCase().includes(filtro.toLowerCase())) continue;
        (grupos[x.grupo] ||= []).push(x);
      }
      for (const [g, xs] of Object.entries(grupos)) {
        lista += `<h4>${esc(g)}</h4>` + xs.map((x, i) =>
          `<button data-cat="${esc(x.id)}">${esc(x.desc)}<code>${esc(x.ied)} · ${esc(cmd ? x.ref : x.fc + " · " + x.ref)}</code></button>`).join("");
      }
    } else {
      let dados = app.navegarCache[iedNav];
      if (!dados) {
        lista = `<h4>Lendo o modelo do IED…</h4>`;
      } else if (dados.erro) {
        lista = `<h4>${esc(dados.erro)}</h4>`;
      } else {
        const fonte = cmd ? dados.comandos : dados.leituras.filter((l) => ["ST", "MX"].includes(l.fc));
        const f = filtro.toLowerCase();
        const achados = fonte.filter((l) => !f || l.ref.toLowerCase().includes(f));
        lista = `<h4>${achados.length} ${cmd ? "objeto(s) de controle" : "atributo(s) ST/MX"}${achados.length > 300 ? " — mostrando 300, use o filtro" : ""}</h4>` +
          achados.slice(0, 300).map((l, i) => `<button data-nav="${i}">${esc(l.ref.split("/")[1])}<code>${esc(cmd ? l.ref + " · tipo " + l.tipo : l.fc + " · " + l.ref)}</code></button>`).join("");
        render.achados = achados;
      }
    }
    abrirModal(`<h2>${cmd ? "Ligar comando" : "Ligar tag"}</h2>
      <p class="sub">${cmd ? "Escolha o objeto de controle que vai receber o Oper." : "Escolha o atributo que o componente vai mostrar."}</p>
      <div class="abas-modal">
        <button data-aba="catalogo" class="${aba === "catalogo" ? "ativa" : ""}">Maquete</button>
        <button data-aba="navegar" class="${aba === "navegar" ? "ativa" : ""}">Navegar no IED</button>
      </div>
      <div class="filtro">
        ${aba === "navegar" ? `<select id="v-ied">${Object.entries(app.cfg.ieds).map(([k, i]) => `<option value="${k}" ${k === iedNav ? "selected" : ""}>${esc(k)}</option>`).join("")}</select>` : ""}
        <input id="v-filtro" placeholder="Filtrar (ex.: XCBR1, MMXU, Pos)" value="${esc(filtro)}">
        ${cmd && aba === "navegar" ? `<select id="v-tipo" title="Tipo do valor do comando"><option value="d" ${tipoCmd === "d" ? "selected" : ""}>Posição (1/2)</option><option value="b" ${tipoCmd === "b" ? "selected" : ""}>Booleano</option><option value="i" ${tipoCmd === "i" ? "selected" : ""}>Inteiro</option><option value="f" ${tipoCmd === "f" ? "selected" : ""}>Real</option></select>` : ""}
      </div>
      <div class="lista-tags">${lista || "<h4>Nada encontrado</h4>"}</div>
      <div class="rodape-modal">${aba === "navegar" ? `<button class="btn" id="v-reler">Ler o modelo de novo</button>` : ""}<button class="btn" data-fechar>Cancelar</button></div>`, true);

    const caixa = $("#modal-caixa");
    caixa.querySelectorAll("[data-aba]").forEach((b) => b.onclick = () => { aba = b.dataset.aba; filtro = ""; render(); });
    const inpF = $("#v-filtro");
    inpF.oninput = () => { filtro = inpF.value; const pos = inpF.selectionStart; render().then(() => { const i = $("#v-filtro"); i.focus(); i.setSelectionRange(pos, pos); }); };
    if ($("#v-ied")) $("#v-ied").onchange = (e) => { iedNav = e.target.value; render(); carregarNavegacao(); };
    if ($("#v-tipo")) $("#v-tipo").onchange = (e) => { tipoCmd = e.target.value; };
    if ($("#v-reler")) $("#v-reler").onclick = () => { delete app.navegarCache[iedNav]; render(); carregarNavegacao(); };
    caixa.querySelectorAll("[data-cat]").forEach((b) => b.onclick = () => {
      const x = (cmd ? app.cfg.catalogo.comandos : app.cfg.catalogo.tags).find((y) => y.id === b.dataset.cat);
      aplicar(cmd ? { ied: x.ied, ref: x.ref, tipo: x.tipo } : { ied: x.ied, fc: x.fc, ref: x.ref });
    });
    caixa.querySelectorAll("[data-nav]").forEach((b) => b.onclick = () => {
      const l = render.achados[Number(b.dataset.nav)];
      aplicar(cmd ? { ied: iedNav, ref: l.ref, tipo: $("#v-tipo")?.value || l.tipo } : { ied: iedNav, fc: l.fc, ref: l.ref });
    });
  }

  async function carregarNavegacao() {
    const ied = iedNav;
    if (app.navegarCache[ied]) return;
    try {
      app.navegarCache[ied] = await api(`/api/navegar?ied=${encodeURIComponent(ied)}`);
    } catch (e) {
      app.navegarCache[ied] = { erro: e.message };
    }
    if (aba === "navegar" && iedNav === ied && !$("#modal").hidden) render();
  }

  render();
  carregarNavegacao();
}

function propriedadesTela() {
  const t = tela();
  abrirModal(`<h2>Tela</h2>
    <label class="campo"><span>Nome</span><input id="t-nome" value="${esc(t.nome)}"></label>
    <div class="campo-linha">
      <label class="campo"><span>Largura</span><input id="t-w" type="number" value="${t.largura}"></label>
      <label class="campo"><span>Altura</span><input id="t-h" type="number" value="${t.altura}"></label>
    </div>
    <p class="dica">A tela se ajusta sozinha ao tamanho do tablet ou celular, mantendo a proporção.</p>
    <div class="rodape-modal">
      ${app.telas.length > 1 ? `<button class="btn btn-perigo" id="t-excluir">Excluir tela</button>` : ""}
      <button class="btn" data-fechar>Cancelar</button><button class="btn btn-primario" id="t-ok">OK</button>
    </div>`);
  $("#t-ok").onclick = () => {
    guardarDesfazer();
    t.nome = $("#t-nome").value.trim() || t.nome;
    t.largura = Math.max(320, Number($("#t-w").value) || t.largura);
    t.altura = Math.max(240, Number($("#t-h").value) || t.altura);
    fecharModal();
    desenharTudo();
  };
  if ($("#t-excluir")) $("#t-excluir").onclick = () => {
    guardarDesfazer();
    app.telas.splice(app.atual, 1);
    app.atual = Math.max(0, app.atual - 1);
    app.sel = null;
    fecharModal();
    desenharTudo();
  };
}

function configurarBotoes() {
  $("#btn-editar").onclick = () => (app.editando ? pedirSaida() : entrarEdicao());
  $("#btn-tela-cheia").onclick = () => {
    if (document.fullscreenElement) document.exitFullscreen?.();
    else document.documentElement.requestFullscreen?.().catch(() => toast("Este navegador não deixou abrir em tela cheia."));
  };
  $("#btn-eventos").onclick = () => {
    $("#painel-eventos").hidden = false;
    app.naoLidos = 0;
    desenharEventos();
  };
  $("#fechar-eventos").onclick = () => { $("#painel-eventos").hidden = true; };
  // so no modo simulado: faz o papel do botao da falta que fica na maquete
  $("#btn-sim-falta").onclick = async () => {
    try {
      const r = await api("/api/simular_falta", { method: "POST", body: {} });
      toast(r.falta ? "Simulação: alguém apertou o botão da falta (árvore na linha)." : "Simulação: botão apertado de novo, a árvore saiu da linha.", r.falta ? "ruim" : "bom");
    } catch (e) { toast("Não consegui simular a falta.", "ruim"); }
  };
  $("#modal").addEventListener("click", (e) => {
    if (e.target.id === "modal" || e.target.closest("[data-fechar]")) fecharModal();
  });

  $("#ed-salvar").onclick = salvar;
  $("#ed-cancelar").onclick = () => {
    app.telas = clonar(app.copiaAntes);
    app.atual = Math.min(app.atual, app.telas.length - 1);
    app.sel = null;
    sairEdicao();
  };
  $("#ed-desfazer").onclick = () => {
    if (!app.desfazer.length) return toast("Nada para desfazer.");
    app.telas = app.desfazer.pop();
    app.atual = Math.min(app.atual, app.telas.length - 1);
    desenharTudo();
  };
  $("#ed-excluir").onclick = () => {
    const it = itemSelecionado();
    if (!it) return toast("Toque num componente para selecionar.");
    guardarDesfazer();
    tela().itens = tela().itens.filter((i) => i.id !== it.id);
    app.sel = null;
    desenharItens();
    desenharPropriedades();
  };
  $("#ed-duplicar").onclick = () => {
    const it = itemSelecionado();
    if (!it) return toast("Toque num componente para selecionar.");
    guardarDesfazer();
    const c = clonar(it);
    c.id = novoId(); c.x += 20; c.y += 20;
    tela().itens.push(c);
    app.sel = c.id;
    desenharItens();
    desenharPropriedades();
  };
  $("#ed-nova-tela").onclick = () => {
    guardarDesfazer();
    app.telas.push({ id: novoId(), nome: `Tela ${app.telas.length + 1}`, largura: 1280, altura: 720, itens: [] });
    app.atual = app.telas.length - 1;
    app.sel = null;
    desenharTudo();
  };
  $("#ed-tela-props").onclick = propriedadesTela;

  document.addEventListener("keydown", (e) => {
    if (!app.editando || e.target.matches("input, select, textarea")) return;
    const it = itemSelecionado();
    if ((e.key === "Delete" || e.key === "Backspace") && it) { e.preventDefault(); $("#ed-excluir").click(); }
    if ((e.ctrlKey || e.metaKey) && e.key === "z") { e.preventDefault(); $("#ed-desfazer").click(); }
    const passo = { ArrowLeft: [-GRADE, 0], ArrowRight: [GRADE, 0], ArrowUp: [0, -GRADE], ArrowDown: [0, GRADE] }[e.key];
    if (passo && it) { e.preventDefault(); it.x += passo[0]; it.y += passo[1]; desenharItens(); }
  });
  window.addEventListener("beforeunload", (e) => { if (app.editando && houveMudanca()) e.preventDefault(); });
}

// ---------------------------------------------------------------- inicio
async function iniciar() {
  configurarBotoes();
  configurarPonteiro();
  desenharPaleta();
  desenharEventos();
  for (;;) {
    try {
      app.cfg = await api("/api/config");
      const d = await api("/api/telas");
      app.telas = d.telas?.length ? d.telas : [{ id: novoId(), nome: "Tela 1", largura: 1280, altura: 720, itens: [] }];
      break;
    } catch (e) {
      $("#aviso-conexao").hidden = false;
      await new Promise((r) => setTimeout(r, 2000));
    }
  }
  $("#aviso-conexao").hidden = true;
  app.ieds = app.cfg.ieds;
  $("#btn-sim-falta").hidden = !app.cfg.simulado;
  // Editar tela: so com "permitir_edicao": true no config.json (ou no modo simulado)
  $("#btn-editar").hidden = !app.cfg.edicao;
  desenharStatus();
  desenharTudo();
  ciclo();
  buscarEventosServidor();
}

iniciar();
