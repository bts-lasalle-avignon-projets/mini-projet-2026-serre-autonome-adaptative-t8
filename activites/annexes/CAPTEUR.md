# Capteur

## Notions de base

Un [capteur](https://fr.wikipedia.org/wiki/Capteur) est un dispositif permettant d'interpréter l'état d'une grandeur physique observée en une grandeur exploitable, telle qu'une tension électrique.

> [!IMPORTANT]
> Le capteur se distingue de l'instrument de mesure par le fait qu'il ne s'agit que d'une interface entre un processus physique et une information manipulable. Par opposition, l'instrument de mesure est un appareil se suffisant à lui-même.

Un [transducteur](https://fr.wikipedia.org/wiki/Transducteur) est un dispositif convertissant un signal physique en un autre, par exemple un signal lumineux en signal électrique (photorécepteur). Il y a de nombreux types de transducteurs : électroacoustique (haut-parleur, microphone, cristal piézoélectrique, ...), électromécanique (sonde à effet Hall, capteur inductif), magnétoélectrique, magnéto-optique, optoélectronique, thermoélectrique (thermocouple, thermorésistance), utrasons, ...

> [!NOTE]
> Un capteur est distinct d'un transducteur : il est au minimum constitué d'un transducteur.

On distingue trois types de sortie :

- **analogique** : la sortie est une **grandeur électrique** dont la valeur (une infinité de valeurs continues) est une fonction de la grandeur physique mesurée par le capteur
  - tension
  - courant
- **numérique** : la sortie est une **séquence d'états logiques** `1` ou `0`
  - train d'impulsions ([PWM](https://fr.wikipedia.org/wiki/Modulation_de_largeur_d%27impulsion), ...) ;
  - code numérique binaire ([CAN](https://fr.wikipedia.org/wiki/Convertisseur_analogique-num%C3%A9rique), ...);
  - bus de terrain : bus [I2C](https://fr.wikipedia.org/wiki/I2C) (_Inter-Integrated Circuit_) ou TWI (_Two Wire Interface_), [SPI](https://fr.wikipedia.org/wiki/Serial_Peripheral_Interface) (_Serial Peripheral Interface_), [bus CAN](https://fr.wikipedia.org/wiki/Bus_de_donn%C3%A9es_CAN), [1-Wire](https://fr.wikipedia.org/wiki/1-Wire) (_OneWire_), [Modbus](https://fr.wikipedia.org/wiki/Modbus), [RS-485](https://fr.wikipedia.org/wiki/EIA-485), [RS-232](https://fr.wikipedia.org/wiki/RS-232), ...
- **logique** ([TOR](https://fr.wikipedia.org/wiki/Tout_ou_rien)) : la sortie est un **état logique** `1` ou `0`.

Quelques grandeurs physiques mesurées : Angle, contrainte, courant, champ magnétique, débit, déplacement, distance, force, gaz, inertiels (accéléromètre, inclinomètre, gyromètre, gyroscope), lumière, niveau, position, pression, son, température, etc.

Un capteur est caractérisé principalement par :

- sa grandeur physique observée ;
- son étendue de mesure (gamme de mesure) ;
- sa résolution ;
- sa sensibilité ;
- sa précision ;
- sa reproductibilité ;
- sa linéarité ;
- son temps de réponse ;
- sa bande passante ;
- etc.

> [!IMPORTANT]
> Pour utiliser un capteur dans les meilleures conditions, il est souvent indispensable d'effectuer un **étalonnage**.

Les capteurs sont les éléments de base des **systèmes d'acquisition de données**.

> [!TIP]
> Ces dernières années ont vu apparaître le concept de capteurs intelligents. En plus de leur faculté de mesurer une grandeur physique, ils possèdent d'autres fonctionnalités, par exemple : fonctions de configuration, fonctions d'auto-test et d'auto-contrôle, étalonnage automatique et évidemment sortie sur des bus de terrain, notamment sans-fils.

Les capteurs sont souvent interfacés avec un [microcontrôleur](https://fr.wikipedia.org/wiki/Microcontr%C3%B4leur).

> [!NOTE]
> Un microcontrôleur (µc ou MCU en anglais) est un [circuit intégré](https://fr.wikipedia.org/wiki/Circuit_int%C3%A9gr%C3%A9) qui rassemble les éléments essentiels d'un ordinateur : processeur, mémoires (mémoire morte et mémoire vive), unités périphériques et interfaces d'entrées-sorties. Les microcontrôleurs sont fréquemment utilisés dans les [systèmes embarqués](https://fr.wikipedia.org/wiki/Syst%C3%A8me_embarqu%C3%A9), comme les automobiles, les télécommandes, les appareils de bureau, l'électroménager, les jouets, la téléphonie mobile, les [objets connectés IoT](https://fr.wikipedia.org/wiki/Internet_des_objets) etc.

Un microcontrôleur intègre généralement :

- un processeur (CPU) 8, 16, 32 ou 64 bits et éventuellement son nombre de coeurs ([_core_](https://fr.wikipedia.org/wiki/Microprocesseur_multi-c%C5%93ur));
- de la mémoire vive (RAM) pour stocker les données et variables ;
- de la mémoire morte (ROM) pour stocker le programme, actuellement le plus souvent de la mémoire flash ;
- souvent un oscillateur pour le cadencement de l'horloge ;
- les [chiens de garde](https://fr.wikipedia.org/wiki/Chien_de_garde_(informatique)) (_watchdog_),
- des **périphériques d'entrées/sorties** :
  - les convertisseurs analogiques-numériques (CAN) (donnent un nombre binaire à partir d'une tension électrique),
  - les convertisseurs numériques-analogiques (CNA) (effectuent l'opération inverse),
  - les générateurs de signaux à modulation de largeur d'impulsion PWM (_Pulse Width Modulation_),
  - les timers/compteurs (compteurs d'impulsions d'horloge interne ou d'événements externes),
  - les contrôleurs de bus de communication (UART, I2C, SPI, CAN, USB, etc.).

> Les microcontrôleurs peuvent généralement se placer dans un état de sommeil (_sleep_), dans lequel ils présentent une très faible consommation électrique. Un signal envoyé par l'un de leurs périphériques (timer, broche d'entrée-sortie, _watchdog_, etc.) permet de les faire sortir de cet état de sommeil (_wake up_).

Les ports [GPIO](https://fr.wikipedia.org/wiki/General_Purpose_Input/Output) (_General Purpose Input/Output_) sont des **ports d'entrées-sorties** très utilisés dans le monde des microcontrôleurs. Ils permettent d'interfacer des composants électroniques et circuits externes, dont les capteurs.

---
&#x1f12f; BTS LaSalle Avignon - 2025 - <<thierry.vaira@gmail.com>>
