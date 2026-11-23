# SCADA do tablet

Supervisório da maquete que roda no navegador de um tablet ou celular, no
lugar do notebook com o Elipse. Tem os dois modos do Elipse:

- **Execução:** mostra a maquete ao vivo. Tocar num disjuntor ou numa chave
  abre a janela de comando (ABRIR / FECHAR).
- **Edição:** botão "Editar tela". Arrasta componentes, liga cada um a uma
  tag do IED e salva. A tela fica guardada na Pi, então todo tablet vê a mesma.

O Elipse continua funcionando junto: o servidor IEC 61850 aceita vários
clientes ao mesmo tempo.

A mesma Pi também serve o **gêmeo digital 3D**, em `/gemeo/`. Ele só lê o
estado da maquete e nunca manda comando (ver "Gêmeo 3D" abaixo).

## Como as peças se ligam

```
tablet (navegador) ──wi-fi──► Pi com o servidor.py ──cabo──► IEDs (MMS, porta 102)
                              (servidor web + ponte)          CTRL .100 / PROT .101 / MU .103
```

O navegador não fala MMS. Por isso existe a `ponte` (em C, com a libiec61850):
ela faz o mesmo que o Elipse, ler valores e mandar o `Oper`. O `servidor.py`
fica no meio, entregando a página para o tablet e repassando os pedidos.

Em termos de rede, o que importa é só isto: **o tablet precisa estar no mesmo
wi-fi que a Pi onde o servidor roda**, e essa Pi precisa alcançar os IEDs
pelo cabo (o que já acontece hoje, porque o Elipse faz o mesmo caminho).

## Instalar (numa Pi da maquete, de preferência a do servo)

A libiec61850 já está instalada nas Pis pelo `setup.sh`. A pasta fica fora do
repositório do projeto (é um teste), por exemplo em `~/tablet_scada`.

A Pi do servo é a melhor escolha: a das telinhas já calcula o SV 4800 vezes
por segundo e a MU publica o SV com prioridade de tempo real.

```bash
cd ~/tablet_scada
make
python3 servidor.py
```

O programa mostra o endereço para abrir no tablet, algo como
`http://192.168.0.57:8080`. Não precisa instalar nada com `pip`.

### Atualizar uma Pi que já tem o supervisório

Pare o `servidor.py` (Ctrl+C), copie a pasta nova por cima da antiga e rode
`make` de novo: a `ponte` mudou (formato da norma). Depois,
`python3 servidor.py` como sempre.

Se os IPs dos IEDs mudarem, edite o `config.json`.

### No tablet

1. Abra o endereço no Chrome.
2. Menu ⋮ → **Adicionar à tela inicial**. Fica um ícone, como um app.
3. Use o botão de tela cheia (canto superior direito) na apresentação.

Como a página é servida por `http` dentro da rede local, o Android trata o
ícone como atalho do navegador, e não como app instalado. Na prática, com a
tela cheia, a diferença não aparece.

## Treinar sem a maquete

```bash
python3 servidor.py --simulado
```

Roda uma maquete simulada, sem nenhuma Pi e sem precisar do `make`: o
intertravamento das chaves e dos disjuntores, o trip abrindo o DJ1, a corrente
indo a zero com o vão aberto e a chave 1 abrindo sozinha 2 s depois do trip,
como na maquete. Como não existe o botão físico, aparece no topo um botão
**Botão da falta (simulado)**, só nesse modo. Serve para montar telas no
notebook ou ensaiar a demonstração.

## Montar uma tela

Na apresentação, qualquer visitante no Wi-Fi abre o supervisório. Por isso a
edição fica desligada: o botão **Editar tela** não aparece e o servidor recusa
salvar telas. Para montar ou mudar uma tela, coloque `"permitir_edicao": true`
no `config.json` e reinicie (`sudo systemctl restart empelas-supervisorio`).
Terminou? Volte para `false` e reinicie de novo. No modo `--simulado` a
edição fica sempre ligada.

1. **Editar tela** → toque num componente da barra de cima para adicionar.
2. Arraste para posicionar; a bolinha azul no canto muda o tamanho.
3. No painel da direita, **Ligar…** escolhe a tag:
   - aba **Maquete**: lista pronta com os nomes da maquete (`catalogo.json`);
   - aba **Navegar no IED**: lê o modelo direto do IED, como o "refazer a
     leitura dos dados" do Elipse. Serve para qualquer atributo.
4. **Salvar.**

Componentes: disjuntor, chave (com cadeado do CILO), medida (com alarme por
limite), indicador, botão de comando, texto, barra, painel e tendência.

## Convenções que vêm do projeto

- Posição na tela: **1 = aberto, 2 = fechado, 0 = em movimento**. Os IEDs
  mandam a posição no formato da norma (dois bits: `01` = aberto, `10` =
  fechado), e a `ponte` já converte com o `Dbpos_fromMmsValue` da biblioteca.
- Comando: a tela manda 1 (abrir) ou 2 (fechar) e a `ponte` monta o `ctlVal`
  como o IED pede. Nos CSWI da maquete, ele é booleano: `true` = fechar,
  `false` = abrir, como manda a norma.
- Cores: verde = fechado, vermelho = aberto, amarelo = em movimento, cinza =
  sem dado. Hachura roxa = qualidade inválida (por exemplo, quando o GOOSE de
  posições para de chegar no IED de controle).
- Chaves e disjuntores são comandados pelo IED de controle, na Pi das
  telinhas: chaves no `CSWI1-3`, disjuntores no `CSWI4-6`. O `XCBR` da Pi do
  servo só mostra a posição e não aceita comando.
- Intertravamento: chave N só manobra com o DJ N aberto (`CILO1-3`). O DJ N
  abre sempre e só fecha com a chave N parada; o DJ1 também não fecha com o
  trip ativo (`CILO4-6.EnaCls`). O cadeado aparece na chave ou no disjuntor
  bloqueado. O tablet não decide o intertravamento, só avisa: quem recusa é o
  IED, e o motivo (`addCause`) aparece na tela.
- A falta é feita só pelo botão da maquete. A tela mostra se a árvore está na
  linha (`FLTGGIO1.SPCSO1`), mas não tem mais botão para derrubar a árvore.

## Gêmeo 3D

Abra `http://<IP da Pi>:8080/gemeo/` no notebook ligado à TV, na mesma rede.
O botão **Gêmeo 3D** no topo do supervisório abre o mesmo endereço.

- O desenho 3D roda no navegador do notebook. A Pi só entrega os arquivos e o
  estado da maquete, então o peso fica no notebook, não na Pi.
- O gêmeo lê `/estado.json` a cada 0,5 s. Esse endereço só responde o estado
  (disjuntores, chaves, travas, árvore e o que a fita mostra) e não aceita
  comando nenhum.
- Sem internet, as fontes do gêmeo ficam as do sistema. O resto funciona
  igual, porque o Three.js e os modelos 3D estão dentro da pasta `app`.

## Arquivos

| Arquivo | O que é |
|---|---|
| `ponte.c`, `Makefile` | ponte MMS em C (um processo por IED) |
| `servidor.py` | servidor web, leitura cíclica e maquete simulada |
| `config.json` | IPs dos IEDs e porta da página |
| `catalogo.json` | tags e comandos da maquete com nomes amigáveis |
| `app/` | o app do tablet (HTML, CSS e JS, sem internet) |
| `app/tela_padrao.json` | tela unifilar que vem pronta |
| `app/gemeo/` | gêmeo digital 3D (só leitura) e os modelos 3D |
| `app/vendor/three/` | Three.js, para o gêmeo rodar sem internet |
| `telas.json` | criado ao salvar; apagar volta para a tela padrão |
| `testes/teste_tablet.py` | teste automático do app (Playwright) |

## O que foi testado

Testado contra os servidores das três Pis (mesmo código e mesmos modelos),
compilados e rodando juntos numa rede virtual, com a libiec61850 1.6.2:

- leitura das 53 tags do catálogo, sem erro, com as posições no formato da
  norma;
- fechar o DJ1 pelo CSWI4; CH1 recusada pelo intertravamento (addCause 10);
  DJ1 de novo, "já está nessa posição" (addCause 5); comando direto no XCBR1
  recusado;
- falta pelo botão: trip, DJ1 aberto, corrente a zero e chave 1 abrindo
  sozinha; fechar em cima da falta, trip de novo; retirar e religar;
- o `/estado.json` do gêmeo acompanhando tudo isso.

No modo simulado, com o navegador simulando um tablet com tela de toque, o
`testes/teste_tablet.py` passa inteiro: comandos, intertravamento com cadeado
no disjuntor, falta simulada, edição de tela, gêmeo ao vivo e celular de
390 px sem rolagem lateral.

Ainda falta testar na maquete de verdade.
