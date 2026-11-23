# Etapa: rede da maquete, ligar sozinho e relógio

Esta etapa deixa a maquete pronta para ser ligada na tomada e funcionar sozinha,
com o supervisório e o gêmeo abertos pelo Wi-Fi, sem o SV atrapalhar.

## Como a rede ficou

```
 SWITCH  ◄── cabos das 3 Pis (eth0)       rede 192.168.10.x: SV, GOOSE e MMS
          ◄── notebook do Elipse (cabo, endereço fixo, ex. 192.168.10.50)

 ROTEADOR (só Wi-Fi "EmPowerElas", sem cabo nenhum para o switch)
          ◄── CTRL (wlan0), celulares, tablet e o notebook da TV
```

**Por que o switch.** A MU manda o SV 4800 vezes por segundo, para todos da
rede (multicast). Um roteador doméstico repassa isso para o Wi-Fi, onde uma
mensagem "para todos" vai na velocidade mais baixa, perto de 1 ms de ar por
mensagem. Com 4800 por segundo o Wi-Fi entope e o roteador trava ou reinicia
(luzes acesas e rede parada). No cabo, as mesmas mensagens dão uns 5 Mbit/s e
não pesam nada. Por isso as Pis ficam num switch e o roteador não tem cabo
nenhum ligado nele: o SV nunca chega ao Wi-Fi. Se o roteador cair, a maquete
continua funcionando; só o Wi-Fi dos visitantes para.

Diminuir a taxa do SV não resolve: mesmo com metade, o Wi-Fi continua sem
tempo livre, e a maquete sairia dos 80 pontos por ciclo da norma.

## Endereços

| Equipamento | Cabo (eth0, switch) | Wi-Fi (wlan0) |
| --- | --- | --- |
| CTRL (Pi do servo) | 192.168.10.100 | 192.168.0.10 no `EmPowerElas` |
| PROT (Pi das telinhas) | 192.168.10.101 | Wi-Fi do laboratório |
| MU | 192.168.10.103 | Wi-Fi do laboratório |
| Roteador | – | 192.168.0.1 (DHCP de .100 a .199) |

Os endereços do cabo são fixos em cada Pi, no `/etc/dhcpcd.conf`. O
`nogateway` faz o cabo nunca virar caminho para a internet:

```
interface eth0
static ip_address=192.168.10.101/24
nogateway
```

Na CTRL, o endereço do Wi-Fi depende da rede em que ela entrar. No
`/etc/dhcpcd.conf`, cada rede tem seu bloco `ssid`:

```
ssid <nome do Wi-Fi do laboratório>
static ip_address=192.168.2.252/24
static routers=192.168.2.1
static domain_name_servers=8.8.8.8

ssid EmPowerElas
static ip_address=192.168.0.10/24
```

No `/etc/wpa_supplicant/wpa_supplicant.conf`, o `EmPowerElas` tem
`priority=10`: quando ele está no ar, a CTRL entra nele. A senha fica
guardada embaralhada (feita com `wpa_passphrase`).

## Para usar

- **Supervisório:** conectar no Wi-Fi `EmPowerElas` e abrir
  `http://192.168.0.10:8080`.
- **Gêmeo 3D:** `http://192.168.0.10:8080/gemeo/` (só mostra, não manda comando).
- **Entrar na CTRL pelo terminal:** `ssh pi@192.168.0.10`, com o PC no
  `EmPowerElas`.
- **Entrar na PROT e na MU sem o Wi-Fi do laboratório:** pela CTRL,
  `ssh pi@192.168.10.101` (PROT) ou `ssh pi@192.168.10.103` (MU).
- **Desligar:** `sudo poweroff` em cada Pi e esperar o LED verde parar antes
  de tirar da tomada. Puxar da tomada com a Pi gravando pode estragar o cartão.

## Ligar sozinho na tomada

Cada programa virou um serviço do systemd. Os arquivos estão em `servicos/`:

| Serviço | Pi | O que roda |
| --- | --- | --- |
| `empelas-mu` | MU | `/home/pi/empelas/empelas_mu/empelas_mu` |
| `empelas-prot` | PROT | `empelas_prot` |
| `empelas-ctrl` | CTRL | `empelas_ctrl` |
| `empelas-supervisorio` | CTRL | `python3 ~/tablet_scada/servidor.py`, como usuário `pi` |

Antes de começar, cada serviço espera até 30 s o cabo (`eth0`) ter endereço.
Se o programa parar, o systemd liga de novo em 3 s.

Instalar numa Pi (exemplo da PROT):

```bash
sudo cp servicos/empelas-prot.service /etc/systemd/system/
sudo systemctl daemon-reload
sudo systemctl enable --now empelas-prot
```

Ver as mensagens do programa: `journalctl -u empelas-prot -f` (Ctrl+C só
fecha a visualização). Com o serviço ativo, não rode o programa à mão.

## Relógio

A PROT pega a hora da internet (chrony, servidores ntp.br) e entrega para as
outras pelo cabo: no `chrony.conf` dela estão `allow 192.168.10.0/24` e
`local stratum 8`. Sem internet, ela continua entregando a própria hora, e as
três Pis ficam iguais entre si.

Na MU e na CTRL:

```bash
sudo cp servicos/empelas.sources /etc/chrony/sources.d/
sudo systemctl enable --now chrony
```

Nas três, o serviço espera até 30 s o relógio acertar antes de ligar o
programa, porque um salto grande de horário no meio do funcionamento confunde
os tempos internos:

```bash
sudo mkdir -p /etc/systemd/system/empelas-prot.service.d
sudo cp servicos/relogio.conf /etc/systemd/system/empelas-prot.service.d/
sudo systemctl daemon-reload
```

Conferir: `date; chronyc sources | grep '\^\*'`. Na MU e na CTRL, a linha com
`^*` é a `192.168.10.101`. Os programas mostram `Relogio sincronizado` na
partida.

## Testado na maquete

- comandos pelo supervisório, intertravamento das chaves e dos disjuntores,
  falta pelo botão, religar em cima da falta e os vãos 2 e 3;
- gêmeo acompanhando a maquete, só lendo;
- tirar tudo da tomada e ligar de novo, ainda com as Pis no roteador: as três
  Pis, o supervisório e o gêmeo voltaram sozinhos;
- relógio das três Pis sincronizado;
- supervisório e gêmeo abertos pelo Wi-Fi `EmPowerElas`, com as Pis no switch.

Falta repetir o teste da tomada com o switch e o roteador novos, e deixar um
celular no Wi-Fi por um tempo com a maquete ligada.
