"""Teste automatico do SCADA do tablet (Playwright).
Suba antes o servidor:  python3 servidor.py --simulado   e rode:  python3 testes/teste_tablet.py
(no modo simulado as medidas variam 1%, como numa medicao de verdade)"""
import os, sys
from playwright.sync_api import sync_playwright

OUT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "capturas")
os.makedirs(OUT, exist_ok=True)
URL = "http://localhost:8080"
falhas, erros_console = [], []

def confere(cond, msg):
    print(("OK   " if cond else "FALHOU ") + msg)
    if not cond:
        falhas.append(msg)

def item(page, texto):
    return page.locator("#camada g.item", has_text=texto).first

def tocar(page, texto):
    # a tela redesenha a cada leitura, entao toca pela posicao, como um dedo
    bb = item(page, texto).bounding_box()
    page.touchscreen.tap(bb["x"] + 14, bb["y"] + bb["height"] / 2)

def texto_item(page, texto):
    return item(page, texto).text_content()

def toast(page):
    page.wait_for_selector(".toast", timeout=4000)
    t = page.locator(".toast").last.inner_text()
    page.evaluate("document.querySelectorAll('.toast').forEach(t => t.remove())")
    return t

with sync_playwright() as p:
    b = p.chromium.launch(headless=True)
    ctx = b.new_context(viewport={"width": 1280, "height": 800}, has_touch=True, device_scale_factor=1)
    page = ctx.new_page()
    page.on("console", lambda m: m.type == "error" and erros_console.append(m.text))
    page.on("pageerror", lambda e: erros_console.append(str(e)))

    page.goto(URL)
    page.wait_for_load_state("networkidle")
    page.wait_for_timeout(1500)
    page.screenshot(path=f"{OUT}/1_inicio.png")

    confere(page.locator(".pilula.ok").count() == 3, "os 3 IEDs aparecem conectados")
    confere("ABERTO" in texto_item(page, "DJ1"), "DJ1 comeca aberto")
    confere("FECHADA" in texto_item(page, "CH1"), "CH1 comeca fechada")
    confere(page.locator("#camada g.item", has_text="IA").first.text_content().strip().startswith("IA"), "medida IA aparece")

    # 1) fecha o DJ1
    tocar(page, "DJ1")
    page.wait_for_selector("#modal:not([hidden])")
    page.click(".botoes-comando .fechar")
    t = toast(page); confere("aceito" in t, f"DJ1 fechar aceito ({t})")
    page.wait_for_timeout(1000)
    confere("FECHADO" in texto_item(page, "DJ1"), "DJ1 ficou fechado")

    # 2) tenta abrir a CH1 com o DJ1 fechado: o IED tem que recusar
    tocar(page, "CH1")
    page.wait_for_selector("#modal:not([hidden])")
    confere(page.locator(".alerta").count() == 1, "modal da CH1 avisa do intertravamento")
    page.screenshot(path=f"{OUT}/2_intertravamento.png")
    page.click(".botoes-comando .abrir")
    t = toast(page); confere("intertravamento" in t, f"CH1 recusada pelo intertravamento ({t})")

    # 3) a falta agora e so pelo botao da maquete: a tela nao tem mais o botao da arvore
    confere(page.locator("#camada g.item", has_text="Derrubar").count() == 0, "a tela nao tem o botao de derrubar a arvore")
    confere(page.locator("#btn-sim-falta").is_visible(), "no modo simulado aparece o botao da falta simulado")
    # arvore na linha -> trip -> DJ1 abre sozinho -> a MU zera a corrente
    page.click("#btn-sim-falta")
    t = toast(page); confere("falta" in t, f"falta simulada ({t})")
    page.wait_for_timeout(1500)
    confere("ABERTO" in texto_item(page, "DJ1"), "o trip abriu o DJ1")
    ia = page.locator("#camada g.item", has_text="IA").first.text_content()
    confere("0" in ia.split(), f"IA foi a zero com o DJ1 aberto ({ia.split()})")
    confere("FALTA" in page.locator("#camada g.item", has_text="rvore").first.text_content(), "indicador da arvore mostra FALTA")
    page.screenshot(path=f"{OUT}/3_falta_trip.png")

    # 4) como na maquete, a CH1 abre sozinha uns 2 s depois do trip
    page.wait_for_timeout(3000)
    confere("ABERTA" in texto_item(page, "CH1"), "CH1 abriu sozinha depois do trip")
    # fechar o DJ1 com a CH1 em movimento: cadeado no DJ1 e o IED recusa
    tocar(page, "CH1")
    page.click(".botoes-comando .fechar")
    t = toast(page); confere("aceito" in t, f"CH1 fechar aceito ({t})")
    viu = False
    for _ in range(15):
        page.wait_for_timeout(100)
        if item(page, "DJ1").locator("path").count() >= 1:
            viu = True
            break
    confere(viu, "DJ1 mostra o cadeado com a chave em movimento")
    page.screenshot(path=f"{OUT}/3b_cadeado_dj.png")
    tocar(page, "DJ1")
    page.wait_for_selector("#modal:not([hidden])")
    confere("fechar bloqueado" in page.inner_text("#modal-caixa"), "modal do DJ1 avisa do fechar bloqueado")
    page.click(".botoes-comando .fechar")
    t = toast(page); confere("intertravamento" in t or "movimento" in t, f"DJ1 recusado com a chave andando ({t})")
    page.wait_for_timeout(1500)
    # fechar em cima da falta: trip de novo
    tocar(page, "DJ1"); page.click(".botoes-comando .fechar")
    t = toast(page); confere("aceito" in t, f"DJ1 fechar em cima da falta aceito ({t})")
    page.wait_for_timeout(800)
    confere("ABERTO" in texto_item(page, "DJ1"), "fechar em cima da falta: trip de novo")
    # retira a falta e religa
    page.click("#btn-sim-falta"); toast(page)
    page.wait_for_timeout(3200)
    if "ABERTA" in texto_item(page, "CH1"):
        tocar(page, "CH1"); page.click(".botoes-comando .fechar"); toast(page); page.wait_for_timeout(1500)
    tocar(page, "DJ1"); page.click(".botoes-comando .fechar")
    t = toast(page); confere("aceito" in t, f"religar DJ1 aceito ({t})")
    page.wait_for_timeout(1200)
    ia = page.locator("#camada g.item", has_text="IA").first.text_content()
    confere(any(x.isdigit() and 140 <= int(x) <= 260 for x in ia.split()), f"corrente de volta ({ia.split()})")

    # 5) eventos
    page.wait_for_timeout(1600)
    page.click("#btn-eventos")
    n_ev = page.locator("#lista-eventos li").count()
    confere(n_ev >= 5, f"lista de eventos registrou as manobras ({n_ev})")
    page.screenshot(path=f"{OUT}/4_eventos.png")
    page.click("#fechar-eventos")

    # 6) edicao: novo componente, ligar tag pelo catalogo e pela navegacao no IED
    page.click("#btn-editar")
    antes = page.locator("#camada g.item").count()
    page.click("#paleta button[data-tipo=medida]")
    confere(page.locator("#camada g.item").count() == antes + 1, "medida nova adicionada")
    page.fill("#propriedades input[data-k=rotulo]", "Neutro")
    page.click("#propriedades [data-ligar=tag]")
    page.fill("#v-filtro", "neutro")
    page.locator(".lista-tags button", has_text="Corrente neutro").click()
    confere("MMXU1.A.neut" in page.inner_text("#propriedades"), "tag ligada pelo catalogo")
    # arrasta o componente
    g = page.locator("#camada g.item", has_text="NEUTRO").first
    bx = g.bounding_box()
    page.mouse.move(bx["x"] + 20, bx["y"] + 20); page.mouse.down()
    page.mouse.move(bx["x"] - 300, bx["y"] + 150, steps=8); page.mouse.up()
    nx = page.input_value("#propriedades input[data-geo=x]")
    confere(nx != "", f"arrastar move o componente (x={nx})")
    # navegar no IED
    page.click("#propriedades [data-ligar=tag]")
    page.click("[data-aba=navegar]")
    page.wait_for_selector(".lista-tags button[data-nav]", timeout=8000)
    qtd = page.locator(".lista-tags button[data-nav]").count()
    confere(qtd > 20, f"navegar no IED lista atributos ({qtd})")
    page.fill("#v-filtro", "PPV.phsBC")
    page.wait_for_timeout(300)
    page.locator(".lista-tags button[data-nav]").first.click()
    confere("PPV.phsBC" in page.inner_text("#propriedades"), "tag ligada pela navegacao no IED")
    page.screenshot(path=f"{OUT}/5_edicao.png")
    page.click("#ed-salvar")
    t = toast(page); confere("salva" in t, f"tela salva ({t})")
    page.click("#btn-editar")

    # 7) recarrega: a tela salva volta, e o valor novo aparece
    page.reload(); page.wait_for_load_state("networkidle"); page.wait_for_timeout(1500)
    confere(page.locator("#camada g.item").count() == antes + 1, "tela salva sobreviveu ao recarregar")
    vbc = page.locator("#camada g.item", has_text="NEUTRO").first.text_content()
    confere(any(str(x) in vbc.split() for x in range(500, 535)), f"componente novo mostra VBC entre 500 e 535 kV ({vbc.split()})")

    # 7b) gemeo 3D servido pela mesma Pi, so leitura
    g3 = ctx.new_page()
    g3.on("pageerror", lambda e: erros_console.append("gemeo: " + str(e)))
    g3.goto(URL + "/gemeo")
    g3.wait_for_function("window.__gemeoPronto === true", timeout=120000)
    g3.wait_for_timeout(2500)
    chip = g3.inner_text("#chipTxt")
    confere("Ao vivo" in chip, f"gemeo ligado ao vivo ({chip})")
    dj1 = g3.evaluate("window.gemeo.estado.dj[1]")
    confere(dj1 is True, f"gemeo mostra o DJ1 fechado como a maquete ({dj1})")
    g3.screenshot(path=f"{OUT}/7_gemeo.png")
    g3.close()

    # 8) celular em pe
    cel = b.new_context(viewport={"width": 390, "height": 844}, has_touch=True, is_mobile=True)
    pc = cel.new_page(); pc.goto(URL); pc.wait_for_load_state("networkidle"); pc.wait_for_timeout(1200)
    largura = pc.evaluate("document.documentElement.scrollWidth")
    confere(largura <= 390, f"sem rolagem lateral no celular ({largura}px)")
    pc.screenshot(path=f"{OUT}/6_celular.png")

    b.close()

confere(not erros_console, f"sem erros no console {erros_console[:3]}")
print(f"\n{len(falhas)} falha(s)")
sys.exit(1 if falhas else 0)
