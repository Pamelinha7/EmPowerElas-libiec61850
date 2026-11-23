# Etapa: valores de tensão e corrente

Os valores da maquete agora seguem o projeto de subestação de 500 kV do livro
do Mamede: subestação de 500/34,5 kV que escoa um parque fotovoltaico, com 2
transformadores de 128/160/200 MVA (ONAN/ONAF1/ONAF2) e 1 linha de 500 kV. A
MU mede essa linha.

## O que mudou

| | Antes | Agora |
| --- | --- | --- |
| Tensão entre fases | 500 kV fixos | varia devagar entre ~508 e 527 kV (fase ≈ 293 a 304 kV), diferença entre fases menor que 1% |
| Corrente normal | 100 A | ~250 A, com nuvens de vez em quando (queda de 20% a 60% por 8 a 40 s) |
| Fator de potência | ~0,9 | ~0,996 (inversores fotovoltaicos) |
| Corrente de falta (fase A) | 800 A | 1500 A |
| Ajuste do PIOC | 300 A | 600 A |

## De onde vêm os números

- **Tensão:** a barra de 500 kV costuma operar um pouco acima do nominal. A
  faixa escolhida fica dentro das tensões dos tapes do transformador (Tabela
  9.1: de 447,5 a 545,9 kV, em passos de 6,563 kV, 7 acima e 8 abaixo do tape
  principal de 500 kV).
- **Corrente:** I = S / (√3 × V). Com 500 kV, 128 MVA dá 147,8 A e 200 MVA dá
  230,9 A por transformador. Na linha, com os dois: de 295,6 A (ONAN) até
  461,9 A (ONAF2, máximo de projeto). Num dia de sol típico, uns 250 A.
- **Ajuste do PIOC:** acima da maior carga da linha (462 A), com folga
  (600 A ≈ 1,3 × 462 A), para a proteção nunca atuar com carga normal.
- **Falta:** 1500 A, bem acima do ajuste. No TC de 600:5 do vão de linha, dá
  12,5 A no secundário, dentro da faixa de exatidão do TC (até 20 × In).

A curva do sol pelo horário não foi usada: a corrente ficaria dependendo da
hora da apresentação.

**Para responder numa pergunta:** num parque solar de verdade, a corrente de
falta que vem do lado do parque é pequena, porque os inversores limitam a
corrente a pouco mais que a nominal. Por isso as linhas desses parques usam
proteção de distância (21) ou diferencial (87L). A maquete usa a sobrecorrente
instantânea (50, PIOC) porque é o jeito mais simples de mostrar o caminho
medida → decisão → trip.

## Onde ficam os valores

- `empelas_mu/server_mu.c`: `V_LINHA_KV`, `V_VAR1_KV`, `V_VAR2_KV`,
  `I_CARGA_A`, `ANG_CARGA_GRAUS`, `NUVEM_*`, `I_FALTA_A`.
- `empelas_prot/server_prot.c`: `PIOC_PARTIDA`.
- `tablet_scada`: alarme das medidas (600 A), escala do gráfico (0 a 1800 A),
  textos da tela e a maquete simulada (`servidor.py --simulado`).

No LCD1 da PROT, correntes de 1000 A para cima aparecem em milhares, com uma
casa: `A1,5k B251 C253` (1500 A na fase A).

## Testado

Com as três Pis rodando juntas numa rede virtual: tensão variando, 250 A sem
trip, uma nuvem derrubando a corrente para ~195 A e voltando, falta de 1500 A
com trip ("ajuste 600 A"), chave 1 abrindo sozinha e religamento. O
supervisório passou no teste automático com os valores novos.
