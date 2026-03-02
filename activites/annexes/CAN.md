# CAN (convertisseur analogique-numérique)

Un [CAN](https://fr.wikipedia.org/wiki/Convertisseur_analogique-num%C3%A9rique) (convertisseur analogique-numérique) ou ADC (_Analog to Digital Converter_) est un dispositif électronique dont la fonction est de traduire une grandeur analogique (généralement une tension électrique) en une valeur numérique codée sur plusieurs bits.

![](https://upload.wikimedia.org/wikipedia/commons/1/10/Symbole_CAN.png?uselang=fr)

> [!WARNING]
> A ne pas confondre avec le [bus CAN](https://fr.wikipedia.org/wiki/Bus_de_donn%C3%A9es_CAN) !

Le résultat de la conversion s'obtient par la formule : ${\displaystyle N=2^{n}{V_{e} \over V_{\text{réf}}}}$

avec :

- $N$ le résultat de conversion,
- $V_{e}$ la tension à convertir,
- $n$ le nombre de bits du convertisseur et
- $V_{\text{réf}}$ la tension de référence de la mesure.

![](./images/codage-4bits.png)

Le processus de conversion repose sur la quantification d'un signal. On appelle **quantum**, le pas minimum de conversion représenté par la variation du bit de poids faible, qui est aussi la valeur de l’imprécision de mesure. Plus le nombre $n$ de bits du convertisseur sur lesquels s'effectuent la conversion est grand, plus la quantification a un effet réduit dans la dégradation du signal (sans jamais l'annuler).

Le quantum s'exprime par la formule : ${\displaystyle q={V_{\text{réf}} \over 2^{n}}}$ en volt ($V$).

Le choix d'un convertisseur CAN repose sur trois points :

- sa vitesse de conversion (la fréquence de son horloge ou sa fréquence d'échantillonnage) ;
- sa résolution (le nombre de bits) ;
- son coût.

L’échantillonnage d’un signal analogique consiste à prélever ses valeurs (appelées échantillons) à des intervalles de temps réguliers avec une cadence suffisante pour ne pas perdre d’information. L’échantillonnage est caractérisé par sa période $T_{\text{e}}$ ou par sa fréquence $F_{\text{e}} = \frac{1}{T_{\text{e}}}$

Théorème de Shannon : La reconstitution d’un signal à partir de ses échantillons n’est possible que si la fréquence d’échantillonnage $F_{\text{e}}$ est strictement supérieure au double de la fréquence maximale du spectre du signal : $F_{\text{e}} > 2 F_{\text{max}}$

> Il existe un convertisseur qui effecute l'opération inverse : convertisseur numérique-analogique (CNA ou DAC pour _Digital to Analog Converter_) qui transforme une valeur numérique (codée sur plusieurs bits) en une valeur analogique (généralement une tension électrique) proportionnelle à la valeur numérique codée.

En résumé :

![](https://upload.wikimedia.org/wikipedia/commons/e/e2/CAN_%26_CNA.png?uselang=fr)

---
&#x1f12f; BTS LaSalle Avignon - 2025 - <<thierry.vaira@gmail.com>>
