#!/usr/bin/env python3
"""
EmPowerElas - SCADA do tablet: servidor web + ponte com os IEDs

Roda numa Pi da maquete (ou num notebook na mesma rede). O tablet abre
http://<IP desta maquina>:8080 no navegador e passa a ser o supervisorio.

    python3 servidor.py              usa os IEDs de verdade (config.json)
    python3 servidor.py --simulado   maquete simulada, sem nenhuma Pi
    python3 servidor.py --config outro.json   usa outro arquivo de configuracao

O gemeo 3D fica em http://<IP desta maquina>:8080/gemeo/ e so le o estado
da maquete (/estado.json). Ele nunca manda comando.

Como funciona:
  - para cada IED do config.json, abre um processo ./ponte (programa em C
    com a libiec61850) que conversa MMS com aquele IED;
  - o tablet diz quais valores a tela precisa, e este servidor le esses
    valores dos IEDs a cada 400 ms e devolve para o tablet;
  - quando alguem toca num disjuntor, o tablet manda o comando para ca, e
    a ponte faz o Oper no IED, como o Elipse faria.

So usa a biblioteca padrao do Python: nao precisa instalar nada com pip.
"""

import json
import os
import shutil
import subprocess
import sys
import threading
import time
from http.server import ThreadingHTTPServer, BaseHTTPRequestHandler
from email.utils import formatdate
from urllib.parse import urlparse, parse_qs

PASTA = os.path.dirname(os.path.abspath(__file__))
PASTA_APP = os.path.join(PASTA, "app")
ARQ_TELAS = os.path.join(PASTA, "telas.json")
ARQ_TELA_PADRAO = os.path.join(PASTA_APP, "tela_padrao.json")
ARQ_CATALOGO = os.path.join(PASTA, "catalogo.json")

# Significado do addCause devolvido pelo IED quando recusa um comando
MOTIVOS = {
    0: "o IED recusou o comando",
    1: "comando nao suportado",
    2: "bloqueado pela hierarquia de comando (local/remoto)",
    3: "a selecao falhou",
    4: "posicao invalida",
    5: "o equipamento ja esta nessa posicao",
    6: "parametro mudou durante a execucao",
    8: "bloqueado pelo modo do IED",
    9: "bloqueado pelo processo (trip ativo: retire a falta antes de fechar)",
    10: "bloqueado pelo intertravamento",
    11: "bloqueado pela verificacao de sincronismo",
    12: "ainda esta manobrando",
    13: "bloqueado pela saude do equipamento",
    16: "tempo esgotado",
    17: "interrompido por um trip",
    18: "o objeto nao foi selecionado",
}


def log(msg):
    print(time.strftime("%H:%M:%S"), msg, flush=True)


def ref_qualidade(ref):
    """De onde ler a qualidade de um atributo (fica no nivel do objeto de dados)."""
    for fim in (".stVal", ".general", ".cVal.mag.f", ".mag.f", ".instMag.i", ".mag.i"):
        if ref.endswith(fim):
            return ref[: -len(fim)] + ".q"
    return None


# ----------------------------------------------------------------------
# Conexao com um IED de verdade, pela ponte em C
# ----------------------------------------------------------------------
class Ponte:
    def __init__(self, chave, ip, porta):
        self.chave = chave
        self.ip = ip
        self.porta = porta
        self.trava = threading.Lock()
        self.proc = None
        self.conectado = False
        self._abrir()

    def _abrir(self):
        exe = os.path.join(PASTA, "ponte")
        if not os.path.exists(exe):
            raise SystemExit("Nao achei o programa ./ponte. Rode 'make' nesta pasta antes.")
        self.proc = subprocess.Popen(
            [exe, self.ip, str(self.porta)],
            stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=sys.stderr,
            text=True, bufsize=1,
        )

    def _pedir(self, linha):
        with self.trava:
            try:
                if self.proc.poll() is not None:
                    self._abrir()
                self.proc.stdin.write(linha + "\n")
                self.proc.stdin.flush()
                resp = self.proc.stdout.readline().rstrip("\n")
            except (BrokenPipeError, OSError):
                resp = ""
            if resp in ("X", ""):
                self.conectado = False
                return None
            self.conectado = True
            return resp

    def ler(self, itens):
        """itens: lista de (fc, ref). Devolve lista de dicts (ou None se desconectado)."""
        partes = []
        for fc, ref in itens:
            partes.append(f"{fc} {ref} {ref_qualidade(ref) or '-'}")
        resp = self._pedir("LEV " + ";".join(partes))
        if resp is None or not resp.startswith("R"):
            return None
        saida = []
        for item in resp[2:].split(";"):
            campos = item.split(" ")
            if campos[0] == "E" or len(campos) < 3:
                saida.append({"e": campos[1] if len(campos) > 1 else "erro"})
                continue
            tipo, valor, q = campos[0], campos[1], campos[2]
            if tipo == "b":
                v = valor == "1"
            elif tipo == "f":
                v = float(valor)
            elif tipo in ("i", "u", "d"):
                v = int(valor)
            else:
                v = valor
            saida.append({"v": v, "t": tipo, "q": q})
        return saida

    def operar(self, ref, tipo, valor, origem):
        resp = self._pedir(f"OP {tipo} {ref} {valor} {origem}")
        if resp is None:
            return {"ok": False, "motivo": "IED desconectado"}
        if resp == "OK":
            return {"ok": True}
        campos = resp.split(" ")
        if len(campos) >= 3 and campos[2] == "objeto_inexistente":
            return {"ok": False, "motivo": "esse objeto de controle nao existe no IED"}
        causa = int(campos[1]) if len(campos) > 1 and campos[1].lstrip("-").isdigit() else 0
        return {"ok": False, "addCause": causa, "motivo": MOTIVOS.get(causa, f"recusado (addCause {causa})")}

    def listar(self):
        resp = self._pedir("LISTA")
        if resp is None or not resp.startswith("L"):
            return None
        return resp.split(" ")[1:]


# ----------------------------------------------------------------------
# Maquete simulada (para treinar ou montar telas sem as Pis)
# ----------------------------------------------------------------------
class MaqueteSimulada:
    """Imita os 3 IEDs no formato novo (norma): chaves pelo CSWI1-3 e
    disjuntores pelo CSWI4-6 da PROT, com o intertravamento dos CILO, o trip
    abrindo o DJ1, a MU zerando a corrente com o vao 1 aberto e a chave 1
    abrindo sozinha 2 s depois do trip, como na maquete."""

    ABERTO, FECHADO, MOVIMENTO = 1, 2, 0
    TEMPO_CHAVE = 1.0          # s que o servo leva para levantar ou baixar a chave
    ATRASO_CHAVE_AUTO = 2.0    # s entre o trip e a chave 1 abrir sozinha
    PULSO = 0.6                # s que um OpOpn/OpCls fica visivel

    def __init__(self, catalogo):
        self.catalogo = catalogo
        self.trava = threading.Lock()
        self.dj = [self.ABERTO] * 3
        self.ch = [self.FECHADO] * 3
        self.pedido = [0, 0, 0]          # chave a caminho (posicao de destino)
        self.t_pedido = [0.0, 0.0, 0.0]
        self.pulso_dj = [(0, 0.0)] * 3   # (posicao pedida, ate quando aparece)
        self.cnt_dj = [0, 0, 0]
        self.cnt_ch = [0, 0, 0]
        self.falta = False
        self.trip_ate = 0.0
        self.chave_auto_em = 0.0

    def _vao1_fechado(self):
        return self.dj[0] == self.FECHADO and self.ch[0] == self.FECHADO

    def _trip(self):
        return time.time() < self.trip_ate

    def _pedir_chave(self, n, valor):
        self.pedido[n] = valor
        self.t_pedido[n] = time.time()
        self.ch[n] = self.MOVIMENTO

    def _avancar(self):
        agora = time.time()
        for n in range(3):
            if self.pedido[n] and agora - self.t_pedido[n] > self.TEMPO_CHAVE:
                self.ch[n] = self.pedido[n]
                self.pedido[n] = 0
                self.cnt_ch[n] += 1
        # falta com o vao fechado: a PROT da trip e o DJ1 abre
        if self.falta and self._vao1_fechado():
            self.trip_ate = agora + 0.8
            self.dj[0] = self.ABERTO
            self.cnt_dj[0] += 1
            self.chave_auto_em = agora + self.ATRASO_CHAVE_AUTO
        # so da maquete: a chave 1 abre sozinha depois do trip
        if self.chave_auto_em and agora >= self.chave_auto_em:
            self.chave_auto_em = 0.0
            if self.dj[0] == self.ABERTO and self.ch[0] == self.FECHADO and not self.pedido[0]:
                self._pedir_chave(0, self.ABERTO)

    def _valor(self, ref):
        import random
        r = ref.split("/", 1)[1]
        ruido = lambda base: base * (1 + random.uniform(-0.01, 0.01))
        agora = time.time()
        trip = self._trip()
        for n in range(3):
            k, kd = n + 1, n + 4
            if r in (f"XCBR{k}.Pos.stVal", f"CSWI{kd}.Pos.stVal"): return self.dj[n], "d"
            if r in (f"XSWI{k}.Pos.stVal", f"CSWI{k}.Pos.stVal"): return self.ch[n], "d"
            if r in (f"CILO{k}.EnaOpn.stVal", f"CILO{k}.EnaCls.stVal"): return self.dj[n] == self.ABERTO, "b"
            if r == f"CILO{kd}.EnaOpn.stVal": return True, "b"
            if r == f"CILO{kd}.EnaCls.stVal":
                return self.ch[n] != self.MOVIMENTO and not (n == 0 and trip), "b"
            if r == f"CSWI{k}.OpOpn.general": return self.pedido[n] == self.ABERTO, "b"
            if r == f"CSWI{k}.OpCls.general": return self.pedido[n] == self.FECHADO, "b"
            alvo, ate = self.pulso_dj[n]
            if r == f"CSWI{kd}.OpOpn.general": return alvo == self.ABERTO and agora < ate, "b"
            if r == f"CSWI{kd}.OpCls.general": return alvo == self.FECHADO and agora < ate, "b"
            if r == f"XCBR{k}.OpCnt.stVal": return self.cnt_dj[n], "i"
            if r == f"XSWI{k}.OpCnt.stVal": return self.cnt_ch[n], "i"
        # a MU zera as correntes com o vao 1 aberto; as tensoes sao da barra
        fechado = self._vao1_fechado()
        f = self.falta and fechado
        i = 1.0 if fechado else 0.0
        medidas = {
            "MMXU1.A.phsA.cVal.mag.f": ruido(800 if f else 100) * i,
            "MMXU1.A.phsB.cVal.mag.f": ruido(100) * i,
            "MMXU1.A.phsC.cVal.mag.f": ruido(100) * i,
            "MMXU1.A.neut.cVal.mag.f": (ruido(700) if f else abs(ruido(1) - 1)) * i,
            "MMXU1.PhV.phsA.cVal.mag.f": ruido(87 if f else 289),
            "MMXU1.PhV.phsB.cVal.mag.f": ruido(289),
            "MMXU1.PhV.phsC.cVal.mag.f": ruido(289),
            "MMXU1.PPV.phsAB.cVal.mag.f": ruido(340 if f else 500),
            "MMXU1.PPV.phsBC.cVal.mag.f": ruido(500),
            "MMXU1.PPV.phsCA.cVal.mag.f": ruido(340 if f else 500),
        }
        if r in medidas: return round(medidas[r], 2), "f"
        if r in ("PIOC1.Str.general", "PIOC1.Op.general", "PTRC1.Tr.general"): return trip, "b"
        if r == "FLTGGIO1.SPCSO1.stVal": return self.falta, "b"
        return None, None

    def ler(self, itens):
        with self.trava:
            self._avancar()
            saida = []
            for fc, ref in itens:
                v, t = self._valor(ref)
                saida.append({"e": "inexistente"} if t is None else {"v": v, "t": t, "q": "g"})
            return saida

    def alternar_falta(self):
        """Faz o papel do botao da falta que fica na maquete."""
        with self.trava:
            self.falta = not self.falta
            self._avancar()
            return self.falta

    def operar(self, ref, tipo, valor, origem):
        r = ref.split("/", 1)[1]
        with self.trava:
            self._avancar()
            for n in range(3):
                k, kd = n + 1, n + 4
                if r == f"CSWI{kd}.Pos":          # disjuntor, pelo IED de controle
                    if valor not in (1, 2):
                        return {"ok": False, "addCause": 6, "motivo": MOTIVOS[6]}
                    if valor == self.FECHADO and self.ch[n] == self.MOVIMENTO:
                        return {"ok": False, "addCause": 10,
                                "motivo": f"bloqueado pelo intertravamento: a chave {k} esta em movimento"}
                    if valor == self.FECHADO and n == 0 and self._trip():
                        return {"ok": False, "addCause": 10,
                                "motivo": "bloqueado pelo intertravamento: o trip da protecao esta ativo"}
                    if self.dj[n] == valor:
                        return {"ok": False, "addCause": 5, "motivo": MOTIVOS[5]}
                    self.dj[n] = valor
                    self.cnt_dj[n] += 1
                    self.pulso_dj[n] = (valor, time.time() + self.PULSO)
                    self._avancar()      # fechar em cima da falta da trip na hora
                    return {"ok": True}
                if r == f"CSWI{k}.Pos":           # chave, pelo IED de controle
                    if valor not in (1, 2):
                        return {"ok": False, "addCause": 6, "motivo": MOTIVOS[6]}
                    if self.pedido[n]:
                        return {"ok": False, "addCause": 12, "motivo": MOTIVOS[12]}
                    if self.dj[n] != self.ABERTO:
                        return {"ok": False, "addCause": 10,
                                "motivo": f"bloqueado pelo intertravamento: abra o disjuntor {k} antes"}
                    if self.ch[n] == valor:
                        return {"ok": False, "addCause": 5, "motivo": MOTIVOS[5]}
                    self._pedir_chave(n, valor)
                    return {"ok": True}
                if r == f"XCBR{k}.Pos":
                    return {"ok": False, "addCause": 0,
                            "motivo": f"o disjuntor so aceita comando pelo IED de controle (CSWI{kd})"}
                if r == f"XSWI{k}.Pos":
                    return {"ok": False, "addCause": 0,
                            "motivo": "a chave so aceita comando pelo IED de controle (CSWI)"}
        return {"ok": False, "motivo": "esse objeto de controle nao existe no IED"}

    def listar(self):
        nomes = []
        for t in self.catalogo["tags"]:
            ld, resto = t["ref"].split("/", 1)
            partes = resto.split(".")
            nomes.append(f"{ld}/{partes[0]}${t['fc']}$" + "$".join(partes[1:]))
        for c in self.catalogo["comandos"]:
            ld, resto = c["ref"].split("/", 1)
            ln, do = resto.split(".", 1)
            nomes.append(f"{ld}/{ln}$CO${do}$Oper")
        return nomes


class IedSimulado:
    """Um IED da maquete simulada (todos compartilham a mesma maquete)."""

    def __init__(self, maquete):
        self.maquete = maquete
        self.conectado = True

    def ler(self, itens):
        return self.maquete.ler(itens)

    def operar(self, ref, tipo, valor, origem):
        return self.maquete.operar(ref, tipo, valor, origem)

    def listar(self):
        return self.maquete.listar()


# ----------------------------------------------------------------------
# Leitura ciclica: so le o que alguma tela aberta esta pedindo
# ----------------------------------------------------------------------
class Supervisorio:
    def __init__(self, config, simulado):
        self.config = config
        self.simulado = simulado
        with open(ARQ_CATALOGO, encoding="utf-8") as f:
            self.catalogo = json.load(f)
        self.ieds = {}
        self.maquete = None
        if simulado:
            maquete = self.maquete = MaqueteSimulada(self.catalogo)
            for chave in config["ieds"]:
                self.ieds[chave] = IedSimulado(maquete)
        else:
            for chave, c in config["ieds"].items():
                self.ieds[chave] = Ponte(chave, c["ip"], c.get("porta", 102))
        self.trava = threading.Lock()
        self.pedidas = {}      # chave da tag -> instante do ultimo pedido
        self.valores = {}      # chave da tag -> {"v","t","q"} ou {"e"}
        self.eventos = []      # comandos dados pelos tablets
        self.id_evento = 0
        self.cache_navegar = {}
        for chave in self.ieds:
            threading.Thread(target=self._ciclo, args=(chave,), daemon=True).start()

    @staticmethod
    def chave_tag(ied, fc, ref):
        return f"{ied}:{fc}:{ref}"

    def pedir(self, chaves):
        agora = time.time()
        with self.trava:
            for c in chaves:
                self.pedidas[c] = agora
            return {c: self.valores.get(c) for c in chaves}

    def _ciclo(self, ied):
        intervalo = self.config.get("intervalo_ms", 400) / 1000
        while True:
            inicio = time.time()
            with self.trava:
                limite = inicio - 15
                for c in [c for c, t in self.pedidas.items() if t < limite]:
                    del self.pedidas[c]
                minhas = [c for c in self.pedidas if c.split(":", 1)[0] == ied]
            if minhas:
                for i in range(0, len(minhas), 40):
                    lote = minhas[i:i + 40]
                    itens = [tuple(c.split(":", 2)[1:]) for c in lote]
                    res = self.ieds[ied].ler(itens)
                    with self.trava:
                        for c, r in zip(lote, res or [None] * len(lote)):
                            self.valores[c] = r
            elif not self.simulado:
                self.ieds[ied].ler([])   # mantem a conexao viva e o estado em dia
            dt = time.time() - inicio
            time.sleep(max(0.05, intervalo - dt))

    def comandar(self, ied, ref, tipo, valor, desc, origem):
        if ied not in self.ieds:
            return {"ok": False, "motivo": "IED desconhecido"}
        if tipo not in ("d", "b", "i", "f"):
            return {"ok": False, "motivo": "tipo de comando invalido"}
        try:
            valor = float(valor) if tipo == "f" else int(valor)
        except (TypeError, ValueError):
            return {"ok": False, "motivo": "valor invalido"}
        res = self.ieds[ied].operar(ref, tipo, valor, origem)
        texto = f"{desc or ref}: " + ("comando aceito" if res["ok"] else "RECUSADO, " + res["motivo"])
        log(f"[COMANDO] ({origem}) {texto}")
        with self.trava:
            self.id_evento += 1
            self.eventos.append({"id": self.id_evento, "hora": time.time(), "texto": texto,
                                 "ok": res["ok"], "origem": origem})
            self.eventos = self.eventos[-200:]
        return res

    # ------------------------------------------------------------------
    # Estado resumido para o gemeo 3D (somente leitura: o gemeo nunca
    # manda comando). Formato que o gemeo entende:
    #   {"dj1":true,...,"ch1":true,...,"trava1":false,...,"arvore":false,"fita":"normal"}
    #   true = fechado / fechada / travada; fita: "normal" | "comando" | "trip"
    # ------------------------------------------------------------------
    TAGS_GEMEO = (
        [(f"dj{k}", "CTRL", "ST", f"EmpElas_CTRLVAO/XCBR{k}.Pos.stVal") for k in (1, 2, 3)]
        + [(f"ch{k}", "CTRL", "ST", f"EmpElas_CTRLVAO/XSWI{k}.Pos.stVal") for k in (1, 2, 3)]
        + [(f"lib{k}", "PROT", "ST", f"EmpElas_PROTMEDPROT/CILO{k}.EnaOpn.stVal") for k in (1, 2, 3)]
        + [("arvore", "MU", "ST", "EmpElas_MUMU01/FLTGGIO1.SPCSO1.stVal"),
           ("trip", "PROT", "ST", "EmpElas_PROTMEDPROT/PTRC1.Tr.general")]
        + [(f"op{k}{x}", "PROT", "ST", f"EmpElas_PROTMEDPROT/CSWI{k}.Op{x}.general")
           for k in range(1, 7) for x in ("Opn", "Cls")]
    )

    def estado_gemeo(self):
        if not self.ieds.get("CTRL") or not self.ieds["CTRL"].conectado:
            return None
        chaves = {nome: self.chave_tag(ied, fc, ref) for nome, ied, fc, ref in self.TAGS_GEMEO}
        lidos = self.pedir(list(chaves.values()))
        val = {}
        for nome, c in chaves.items():
            r = lidos.get(c)
            if r and "e" not in r and r.get("q") != "i":
                val[nome] = r["v"]
        est = {}
        for k in (1, 2, 3):
            for eq in ("dj", "ch"):
                v = val.get(f"{eq}{k}")
                if v in (1, 2):              # 1 = aberto, 2 = fechado; em movimento fica como estava
                    est[f"{eq}{k}"] = v == 2
            if isinstance(val.get(f"lib{k}"), bool):
                est[f"trava{k}"] = not val[f"lib{k}"]
        if isinstance(val.get("arvore"), bool):
            est["arvore"] = val["arvore"]
        # A fita segura o trip e o comando por um tempo, para dar tempo de ver.
        # O trip da maquete dura menos de um decimo de segundo (o DJ1 abre e a
        # corrente zera), entao a leitura a cada 400 ms quase nunca pega o
        # PTRC1.Tr ligado. Por isso tambem conta como trip o DJ1 abrir com a
        # arvore na linha, e como comando qualquer outra mudanca de posicao.
        agora = time.time()
        antes = getattr(self, "_gemeo_antes", {})
        self._gemeo_antes = dict(val)
        mudou = [n for n in ("dj1", "dj2", "dj3", "ch1", "ch2", "ch3")
                 if n in val and n in antes and val[n] != antes[n]]
        abriu_na_falta = "dj1" in mudou and val.get("dj1") == 1 and val.get("arvore") is True
        if val.get("trip") is True or abriu_na_falta:
            self._fita_trip_ate = agora + 3.0
        if (any(val.get(f"op{k}{x}") is True for k in range(1, 7) for x in ("Opn", "Cls"))
                or (mudou and not abriu_na_falta)
                or any(val.get(f"ch{k}") == 0 for k in (1, 2, 3))):
            self._fita_cmd_ate = agora + 1.5
        if agora < getattr(self, "_fita_trip_ate", 0):
            est["fita"] = "trip"
        elif agora < getattr(self, "_fita_cmd_ate", 0):
            est["fita"] = "comando"
        else:
            est["fita"] = "normal"
        return est

    def eventos_desde(self, ultimo):
        with self.trava:
            return [e for e in self.eventos if e["id"] > ultimo]

    def status(self):
        return {k: {"nome": self.config["ieds"][k]["nome"], "conectado": i.conectado}
                for k, i in self.ieds.items()}

    def navegar(self, ied):
        """Lista os atributos (para ler) e os objetos de controle (para comandar) do IED."""
        if ied not in self.ieds:
            return None
        nomes = self.ieds[ied].listar()
        if nomes is None:
            return None
        conjunto = set(nomes)
        leituras, comandos = [], []
        for nome in nomes:
            if "/" not in nome:
                continue
            ld, var = nome.split("/", 1)
            partes = var.split("$")
            if len(partes) < 3:
                continue
            ln, fc, resto = partes[0], partes[1], partes[2:]
            if fc == "CO" and resto[-1] == "Oper" and len(resto) == 2:
                do = resto[0]
                tipo = "d" if do == "Pos" else "b"
                comandos.append({"ref": f"{ld}/{ln}.{do}", "tipo": tipo})
            if fc not in ("ST", "MX", "SP", "CF", "SG", "SE", "DC", "EX", "BL", "SV"):
                continue
            leituras.append({"fc": fc, "ref": f"{ld}/{ln}." + ".".join(resto), "_nome": nome})
        # fica so com as folhas (atributos de verdade, nao estruturas)
        prefixos = set()
        for nome in nomes:
            partes = nome.split("$")
            for i in range(1, len(partes)):
                prefixos.add("$".join(partes[:i]))
        folhas = [{"fc": l["fc"], "ref": l["ref"]} for l in leituras
                  if l["_nome"] not in prefixos and not l["ref"].endswith((".q", ".t"))]
        return {"leituras": folhas, "comandos": comandos}


# ----------------------------------------------------------------------
# Servidor web
# ----------------------------------------------------------------------
TIPOS = {
    ".html": "text/html; charset=utf-8", ".js": "text/javascript; charset=utf-8",
    ".css": "text/css; charset=utf-8", ".json": "application/json; charset=utf-8",
    ".svg": "image/svg+xml", ".png": "image/png", ".jpg": "image/jpeg", ".jpeg": "image/jpeg",
    ".webmanifest": "application/manifest+json", ".txt": "text/plain; charset=utf-8",
    ".woff2": "font/woff2",
}


def carregar_telas():
    for arq in (ARQ_TELAS, ARQ_TELA_PADRAO):
        if os.path.exists(arq):
            with open(arq, encoding="utf-8") as f:
                return json.load(f)
    return {"telas": []}


def salvar_telas(dados):
    if os.path.exists(ARQ_TELAS):
        shutil.copyfile(ARQ_TELAS, ARQ_TELAS + ".bak")
    tmp = ARQ_TELAS + ".tmp"
    with open(tmp, "w", encoding="utf-8") as f:
        json.dump(dados, f, ensure_ascii=False, indent=1)
    os.replace(tmp, ARQ_TELAS)


def criar_handler(sup):
    trava_telas = threading.Lock()

    class Handler(BaseHTTPRequestHandler):
        server_version = "EmPowerElasSCADA/1.0"

        def log_message(self, fmt, *args):
            pass

        def _json(self, obj, codigo=200):
            corpo = json.dumps(obj, ensure_ascii=False).encode("utf-8")
            self.send_response(codigo)
            self.send_header("Content-Type", "application/json; charset=utf-8")
            self.send_header("Cache-Control", "no-store")
            self.send_header("Content-Length", str(len(corpo)))
            self.end_headers()
            self.wfile.write(corpo)

        def _corpo(self):
            n = int(self.headers.get("Content-Length") or 0)
            if n > 5_000_000:
                raise ValueError("grande demais")
            return json.loads(self.rfile.read(n) or b"null")

        def do_GET(self):
            url = urlparse(self.path)
            q = parse_qs(url.query)
            if url.path == "/api/config":
                return self._json({"ieds": sup.status(), "simulado": sup.simulado,
                                   "catalogo": sup.catalogo})
            if url.path == "/api/telas":
                with trava_telas:
                    return self._json(carregar_telas())
            if url.path == "/api/eventos":
                return self._json(sup.eventos_desde(int(q.get("desde", ["0"])[0])))
            if url.path == "/estado.json":
                est = sup.estado_gemeo()
                if est is None:
                    return self._json({"erro": "sem contato com a Pi do servo"}, 503)
                return self._json(est)
            if url.path == "/api/navegar":
                ied = q.get("ied", [""])[0]
                r = sup.navegar(ied)
                if r is None:
                    return self._json({"erro": "nao consegui ler o modelo do IED (ele esta conectado?)"}, 503)
                return self._json(r)
            return self._arquivo(url.path)

        def do_POST(self):
            url = urlparse(self.path)
            try:
                dados = self._corpo()
            except ValueError:
                return self._json({"erro": "JSON invalido"}, 400)
            if url.path == "/api/estado":
                chaves = [c for c in (dados or []) if isinstance(c, str) and c.count(":") >= 2]
                return self._json({"valores": sup.pedir(chaves), "ieds": sup.status()})
            if url.path == "/api/simular_falta":
                if not sup.simulado:
                    return self._json({"erro": "a falta da maquete de verdade e so pelo botao fisico"}, 403)
                falta = sup.maquete.alternar_falta()
                log(f"[SIMULADO] botao da falta: {'arvore na linha' if falta else 'arvore retirada'}")
                return self._json({"ok": True, "falta": falta})
            if url.path == "/api/comando":
                d = dados or {}
                origem = "tablet-" + self.client_address[0].split(".")[-1]
                return self._json(sup.comandar(d.get("ied"), d.get("ref", ""), d.get("tipo", ""),
                                               d.get("valor"), d.get("desc"), origem))
            return self._json({"erro": "nao encontrado"}, 404)

        def do_PUT(self):
            if urlparse(self.path).path != "/api/telas":
                return self._json({"erro": "nao encontrado"}, 404)
            try:
                dados = self._corpo()
            except ValueError:
                return self._json({"erro": "JSON invalido"}, 400)
            if not isinstance(dados, dict) or not isinstance(dados.get("telas"), list):
                return self._json({"erro": "formato invalido"}, 400)
            with trava_telas:
                salvar_telas(dados)
            log(f"[TELAS] salvas por {self.client_address[0]} ({len(dados['telas'])} tela(s))")
            return self._json({"ok": True})

        def _arquivo(self, caminho):
            if caminho.endswith("/"):
                caminho += "index.html"
            arq = os.path.normpath(os.path.join(PASTA_APP, caminho.lstrip("/")))
            if not arq.startswith(PASTA_APP + os.sep):
                return self._json({"erro": "nao encontrado"}, 404)
            if os.path.isdir(arq):           # /gemeo -> /gemeo/
                self.send_response(301)
                self.send_header("Location", caminho + "/")
                self.send_header("Content-Length", "0")
                self.end_headers()
                return
            if not os.path.isfile(arq):
                return self._json({"erro": "nao encontrado"}, 404)
            mtime = int(os.path.getmtime(arq))
            ultima = formatdate(mtime, usegmt=True)
            if self.headers.get("If-Modified-Since") == ultima:
                self.send_response(304)
                self.send_header("Cache-Control", "no-cache")
                self.end_headers()
                return
            with open(arq, "rb") as f:
                corpo = f.read()
            self.send_response(200)
            self.send_header("Content-Type", TIPOS.get(os.path.splitext(arq)[1], "application/octet-stream"))
            self.send_header("Cache-Control", "no-cache")
            self.send_header("Last-Modified", ultima)
            self.send_header("Content-Length", str(len(corpo)))
            self.end_headers()
            self.wfile.write(corpo)

    return Handler


def enderecos_locais():
    try:
        saida = subprocess.run(["hostname", "-I"], capture_output=True, text=True, timeout=2).stdout
        return saida.split()
    except Exception:
        return []


def main():
    simulado = "--simulado" in sys.argv
    arq_config = os.path.join(PASTA, "config.json")
    if "--config" in sys.argv:
        arq_config = sys.argv[sys.argv.index("--config") + 1]
    with open(arq_config, encoding="utf-8") as f:
        config = json.load(f)
    porta = config.get("porta_web", 8080)
    sup = Supervisorio(config, simulado)
    servidor = ThreadingHTTPServer(("0.0.0.0", porta), criar_handler(sup))
    print("-" * 60)
    print(" EmPowerElas - SCADA do tablet" + ("  [MAQUETE SIMULADA]" if simulado else ""))
    if not simulado:
        for k, c in config["ieds"].items():
            print(f"   {k:5s} {c['nome']}  ->  {c['ip']}:{c.get('porta', 102)}")
    print(" No tablet (mesma rede wi-fi), abra no navegador:")
    for ip in enderecos_locais() or ["<IP desta maquina>"]:
        if ":" not in ip:
            print(f"   http://{ip}:{porta}")
    print(" Gemeo 3D (so mostra, nao manda comandos): o mesmo endereco + /gemeo/")
    print(" Ctrl+C para parar.")
    print("-" * 60, flush=True)
    try:
        servidor.serve_forever()
    except KeyboardInterrupt:
        print("\nParando.")


if __name__ == "__main__":
    main()
