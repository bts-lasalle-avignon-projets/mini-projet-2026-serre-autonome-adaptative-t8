# Microcontrôleur

- [Microcontrôleur](#microcontrôleur)
  - [Notions de base](#notions-de-base)
  - [ESP32](#esp32)
  - [Raspberry Pi Pico W](#raspberry-pi-pico-w)
  - [Bac à sable : simulateurs ESP32 et Raspberry Pi Pico](#bac-à-sable--simulateurs-esp32-et-raspberry-pi-pico)

---

## Notions de base

Un [microcontrôleur](https://fr.wikipedia.org/wiki/Microcontr%C3%B4leur) (µc ou MCU en anglais) est un [circuit intégré](https://fr.wikipedia.org/wiki/Circuit_int%C3%A9gr%C3%A9) qui rassemble les éléments essentiels d'un ordinateur : processeur, mémoires (mémoire morte et mémoire vive), unités périphériques et interfaces d'entrées-sorties.

Les microcontrôleurs se caractérisent par par rapport aux microprocesseurs polyvalents utilisés dans les ordinateurs personnels :

- un plus haut degré d'intégration (taille plus petite),
- une plus faible consommation électrique,
- une vitesse de fonctionnement plus faible (de quelques mégahertz jusqu'à plus d'un gigahertz) et
- un coût réduit

Les microcontrôleurs sont fréquemment utilisés dans les [systèmes embarqués](https://fr.wikipedia.org/wiki/Syst%C3%A8me_embarqu%C3%A9), comme les automobiles, les télécommandes, les appareils de bureau, l'électroménager, les jouets, la téléphonie mobile, les [objets connectés IoT](https://fr.wikipedia.org/wiki/Internet_des_objets) etc.

> Les microcontrôleurs représentent la plus grosse partie des ventes dans le marché des microprocesseurs.

Les systèmes embarqués se démarquent des systèmes informatiques traditionnels selon plusieurs aspects :

- soumis à des contraintes de taille (intégration), de consommation électrique (autonomie) et de coût importants (grande série) ;
- affectés à une tâche bien précise. La taille des programmes et la quantité de mémoire (vive et morte), dont ils disposent, sont modestes (face à un micro-ordinateur) ;
- gérés des dispositifs d'entrées-sorties (IO) : boutons, relais, résistances variables, optocoupleurs, moteurs électriques, LED, circuits intégrés logiques, etc. ;
- disposés d'aucun dispositif d'interface homme-machine : ni clavier, ni écran, ni disque, ni imprimante, etc.

> Un microcontrôleur peut effectuer la plupart des instructions machine habituelles, avec certaines restrictions liées à son caractère embarqué (taille restreinte des mots machine, petite taille disponible, etc.). Les capacités mathématiques sont en général particulièrement limitées.

Un microcontrôleur intègre généralement :

- un processeur (CPU) 8, 16, 32 ou 64 bits et éventuellement son nombre de coeurs ([_core_](https://fr.wikipedia.org/wiki/Microprocesseur_multi-c%C5%93ur));
- de la mémoire vive (RAM) pour stocker les données et variables ;
- de la mémoire morte (ROM) pour stocker le programme, actuellement le plus souvent de la mémoire flash ;
- souvent un oscillateur pour le cadencement de l'horloge ;
- les [chiens de garde](https://fr.wikipedia.org/wiki/Chien_de_garde_(informatique)) (_watchdog_),
- des périphériques d'entrées/sorties :
  - les convertisseurs analogiques-numériques (CAN) (donnent un nombre binaire à partir d'une tension électrique),
  - les convertisseurs numériques-analogiques (CNA) (effectuent l'opération inverse),
  - les générateurs de signaux à modulation de largeur d'impulsion PWM (_Pulse Width Modulation_),
  - les timers/compteurs (compteurs d'impulsions d'horloge interne ou d'événements externes),
  - les contrôleurs de bus de communication (UART, I2C, SPI, CAN, USB, etc.).

> Les microcontrôleurs peuvent généralement se placer dans un état de sommeil (_sleep_), dans lequel ils présentent une très faible consommation électrique. Un signal envoyé par l'un de leurs périphériques (timer, broche d'entrée-sortie, _watchdog_, etc.) permet de les faire sortir de cet état de sommeil (_wake up_).

Quelques microcontrôleurs :

- La plateforme [Arduino](https://fr.wikipedia.org/wiki/Arduino) pour notamment les microcontrôleurs [Atmel AVR](https://fr.wikipedia.org/wiki/Atmel_AVR)

![](https://upload.wikimedia.org/wikipedia/commons/3/38/Arduino_Uno_-_R3.jpg)

- [ESP32](https://fr.wikipedia.org/wiki/ESP32) : une série de microcontrôleurs de type système sur une puce ([SoC](https://fr.wikipedia.org/wiki/Syst%C3%A8me_sur_une_puce))

![](https://upload.wikimedia.org/wikipedia/commons/3/33/Espressif_ESP-WROOM-32_Wi-Fi_%26_Bluetooth_Module.jpg?uselang=fr)

- [Raspberry Pi Pico](https://fr.wikipedia.org/wiki/Raspberry_Pi_Pico) : un microcontrôleur d'architecture [ARM](https://fr.wikipedia.org/wiki/Architecture_ARM)

![](https://upload.wikimedia.org/wikipedia/commons/f/fe/Pico-1s.png?uselang=fr)

Le programme d'un microcontrôleur est généralement appelé [micrologiciel](https://fr.wikipedia.org/wiki/Firmware) (_firmware_). C'est un programme intégré dans un appareil informatique (ordinateur, photocopieur, automate (API, APS), disque dur, routeur, appareil photo numérique, etc.) pour qu'il puisse fonctionner.

À l'origine, les microcontrôleurs se programmaient en [assembleur](https://fr.wikipedia.org/wiki/Assembleur).

Désormais, on utilise de plus en plus des langages de haut niveau, notamment le langage **C/C++**, capable de faciliter la programmation de microcontrôleurs toujours plus puissants. On peut citer aussi [MicroPython](https://fr.wikipedia.org/wiki/MicroPython), BASIC Stamp, ...

Il existe aussi des systèmes d'exploitation spécifiques pour certains microcontrôleurs :

- [FreeRTOS](https://fr.wikipedia.org/wiki/FreeRTOS) : https://www.freertos.org/
- [Zephyr](https://fr.wikipedia.org/wiki/Zephyr_(syst%C3%A8me_d%27exploitation)) : https://www.zephyrproject.org/
- Mongoose OS : https://mongoose-os.com/
- ...

## ESP32

Exemple de module : https://www.az-delivery.de/fr/products/esp32-developmentboard

L'[AZ-Delivery Dev Kit C](https://www.az-delivery.de/fr/products/esp32-developmentboard) (ESP32 NODEMCU) a été conçu par [Espressif](https://www.espressif.com/) pour programmer le microcontrôleur [ESP32](https://www.espressif.com/en/products/socs/esp32).

![esp32-nodemcu-wroom](images/esp32-nodemcu-wroom.png)

L'ESP32 utilisé possède une unité centrale composée de 2 cœurs Tensilica LX6 32 bits à 240 MHz.

Quelques caractéristiques :

|||
|---|---|
|RAM|512 kB (520 kB pour l'ESP32-D0WDQ6)|
|Mémoire flash externe|4 MB|
|GPIOs|34|
|Interfaces|SPI, I2C, I2S, CAN, UART|
|WiFi|802.11 b/g/n, 802.11n (2.4 GHz) up to 150 Mbps|
|Bluetooth|V4.2 - BLE et Bluetooth classique|
|Antenne sans fil|PCB|
|Pont USB/UART|CP2102|

![](images/esp32-functional-block-diagram.png)

> Sur ce module, la Led intégrée est sur la broche 1.

Détection sous GNU/Linux (cf. https://docs.platformio.org/en/latest/core/installation/udev-rules.html) :

```bash
$ sudo dmesg
...
[1973869.449241] usb 1-2: New USB device found, idVendor=10c4, idProduct=ea60, bcdDevice= 1.00
[1973869.449245] usb 1-2: New USB device strings: Mfr=1, Product=2, SerialNumber=3
[1973869.449247] usb 1-2: Product: CP2102 USB to UART Bridge Controller
[1973869.449249] usb 1-2: Manufacturer: Silicon Labs
[1973869.449250] usb 1-2: SerialNumber: 0001
[1973869.458370] cp210x 1-2:1.0: cp210x converter detected
[1973869.459262] usb 1-2: cp210x converter now attached to ttyUSB0

$ lsusb
...
Bus 001 Device 030: ID 10c4:ea60 Silicon Labs CP210x UART Bridge
...
```

> L'ESP32 s'interface via un pont USB/UART [CP2102](https://www.silabs.com/interface/usb-bridges/classic/device.cp2102?tab=specs)

## Raspberry Pi Pico W

> Pour aller plus loin : [https://github.com/bts-lasalle-avignon-ressources/raspberry-pico-w](https://github.com/bts-lasalle-avignon-ressources/raspberry-pico-w)

[Raspberry Pi Pico W](https://datasheets.raspberrypi.com/picow/pico-w-datasheet.pdf) est une carte basée sur le microcontrôleur [RP2040](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf) auquel a été ajoutée des interfaces sans fil WiFi 2,4 GHz (802.11n) et Bluetooth LE.

![](images/rp2-pico-w.jpg)

Présentation : https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html

La série [Pico](https://www.raspberrypi.com/documentation/microcontrollers/pico-series.html)

> Livre : [Get Started with MicroPython on Raspberry Pi Pico](https://store.rpipress.cc/collections/latest-bookazines/products/get-started-with-micropython-on-raspberry-pi-pico)

Le Raspberry Pi Pico W utilisé possède une unité centrale composée de 2 cœurs ARM Cortex M0+ à 133 MHz.

Quelques caractéristiques :

|||
|---|---|
|SRAM|264kB|
|Mémoire flash externe|2 MB|
|GPIOs|26|
|Interfaces|2 × SPI, 2 × I2C, 2 × UART, 3 × 12-bit ADC, 16 × canaux PWM|
|WiFi|802.11n (2.4 GHz)|
|Bluetooth|V5.2|

Brochage : https://datasheets.raspberrypi.com/picow/PicoW-A4-Pinout.pdf

![](images/picow-pinout.svg)

> Un _shield_ pour la Raspberry Pi Pico : https://wiki.keyestudio.com/KS3017_Keyestudio_Raspberry_Pico_IO_Shield

Ressources :

- [Raspberry Pi Pico W](https://datasheets.raspberrypi.com/picow/pico-w-datasheet.pdf)
- [RP2040](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf)
- [C/C++ SDK (PDF)](https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf) et [C/C++ SDK (HTML)](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html)
- [Python (PDF)](https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-python-sdk.pdf) et [Python (HTML)](https://www.raspberrypi.com/documentation/microcontrollers/micropython.html)

Démarrage :

Maintenir l'appui sur le bouton `BOOTSEL` puis brancher la [Raspberry Pi Pico W](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html)

Accès au support de stockage de la carte :

```bash
$ ls -l /media/tv/RPI-RP2
total 8
-r--r--r-- 1 tv tv 241 sept.  5  2008 INDEX.HTM
-r--r--r-- 1 tv tv  62 sept.  5  2008 INFO_UF2.TXT
```

Informations sur la carte :

```bash
$ cat /media/tv/RPI-RP2/INFO_UF2.TXT
UF2 Bootloader v3.0
Model: Raspberry Pi RP2
Board-ID: RPI-RP2
```

```bash
$ bat /media/tv/RPI-RP2/INFO_UF2.TXT
───────┬───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
       │ File: /media/tv/RPI-RP2/INFO_UF2.TXT
───────┼───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
   1   │ UF2 Bootloader v3.0
   2   │ Model: Raspberry Pi RP2
   3   │ Board-ID: RPI-RP2
───────┴───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
```

```bash
$ cat /media/tv/RPI-RP2/INDEX.HTM
<html><head><meta http-equiv="refresh" content="0;URL='https://raspberrypi.com/device/RP2?version=E0C9125B0D9B'"/></head><body>Redirecting to <a href='https://raspberrypi.com/device/RP2?version=E0C9125B0D9B'>raspberrypi.com</a></body></html>
```

Installation du _firmware_ MicroPython :

- Télécharger le dernier _firmware_ :

> Voir aussi : https://micropython.org/download/RPI_PICO_W/

```bash
$ wget -c https://micropython.org/download/rp2-pico-w/rp2-pico-w-latest.uf2
--2023-12-15 18:21:03--  https://micropython.org/download/rp2-pico-w/rp2-pico-w-latest.uf2
Résolution de micropython.org (micropython.org)… 176.58.119.26
Connexion à micropython.org (micropython.org)|176.58.119.26|:443… connecté.
requête HTTP transmise, en attente de la réponse… 302 Found
Emplacement : /download/RPI_PICO_W/RPI_PICO_W-latest.uf2 [suivant]
--2023-12-15 18:21:03--  https://micropython.org/download/RPI_PICO_W/RPI_PICO_W-latest.uf2
Réutilisation de la connexion existante à micropython.org:443.
requête HTTP transmise, en attente de la réponse… 200 OK
Taille : 1604608 (1,5M) [application/force-download]
Enregistre : ‘rp2-pico-w-latest.uf2’

rp2-pico-w-latest.uf2                           100%[======================================================================================================>]   1,53M  --.-KB/s    ds 0,1s

2023-12-15 18:21:03 (10,4 MB/s) - ‘rp2-pico-w-latest.uf2’ enregistré [1604608/1604608]

$ file rp2-pico-w-latest.uf2
rp2-pico-w-latest.uf2: UF2 firmware image, family Raspberry Pi RP2040, address 0x10000000, 3134 total blocks
```

- Copier le dernier _firmware_ sur la carte :

```bash
$ cp rp2-pico-w-latest.uf2 /media/tv/RPI-RP2/
```

- Supprimer le _firmware_ téléchargé :

```bash
$ rm rp2-pico-w-latest.uf2
```

- Détection de la carte :

```bash
$ sudo dmesg
...
[3406470.011433] usb 1-6.4: new full-speed USB device number 25 using xhci_hcd
[3406470.125260] usb 1-6.4: New USB device found, idVendor=2e8a, idProduct=0005, bcdDevice= 1.00
[3406470.125264] usb 1-6.4: New USB device strings: Mfr=1, Product=2, SerialNumber=3
[3406470.125265] usb 1-6.4: Product: Board in FS mode
[3406470.125267] usb 1-6.4: Manufacturer: MicroPython
[3406470.125268] usb 1-6.4: SerialNumber: e66141040318442f
[3406470.133057] cdc_acm 1-6.4:1.0: ttyACM0: USB ACM device

$ lsusb
...
Bus 001 Device 025: ID 2e8a:0005 MicroPython Board in FS mode
...
```

- Le fichier de périphérique d'accès à la carte :

```bash
$ ls -l /dev/ttyACM0
crw-rw---- 1 root dialout 166, 0 déc.  15 18:21 /dev/ttyACM0
```

- Vérification pour l'accès :

> Il faut être membre du groupe `dialout`

```bash
$ echo ${USER}
tv
$ id
uid=1026(tv) gid=65536(tv) groupes=65536(tv),4(adm),20(dialout),24(cdrom),27(sudo),30(dip),46(plugdev),122(lpadmin),134(lxd),135(sambashare),140(wireshark),141(ubridge),142(libvirt)
$ cat /etc/group | grep dialout
dialout:x:20:tv
$ getent group dialout
dialout:x:20:tv
```

> Sinon :
>```bash
>$ sudo usermod -aG dialout ${USER}
>```
>

Ressources :

- [minicom](https://github.com/bts-lasalle-avignon-ressources/raspberry-pico-w?tab=readme-ov-file#minicom)
- [mpremote](https://github.com/bts-lasalle-avignon-ressources/raspberry-pico-w?tab=readme-ov-file#mpremote)

## Bac à sable : simulateurs ESP32 et Raspberry Pi Pico

Il est souvent nécessaire de passer par un "bac à sable".

> En informatique, le bac à sable (sandbox) est une zone d'essai permettant d'exécuter des programmes en phase de test ou dans lesquels la confiance est incertaine. C'est notamment très utilisé en sécurité informatique pour sa notion d'isolation.

Il existe de nombreux sites web qui fournissent des EDI (Environnement de Développement Intégré) en ligne pour tester du code ou des services : un espace d'apprentissage séparé. Ils permettent aussi d'échanger des exemples.

Simulateur ESP32 :

- [[wokwi](https://wokwi.com/)](https://wokwi.com/)
- https://github.com/bts-lasalle-avignon-ressources/wokwi-vscode

---
&#x1f12f; BTS LaSalle Avignon - 2025 - <<thierry.vaira@gmail.com>>
