# 🌿 MINI PROJET 2026 : SERRE AUTONOME & ADAPTATIVE (AGRITECH)

## PlatformIO (ESP32)

Pour programmer le microcontrôleur ESP32, il faut : 

- Ouvrir un projet [PlatformIO](https://platformio.org/).

> Un projet PlatformIO est un répertoire qui contient un fichier `platformio.ini`. Annexe : [Niveau 4](../../activites/annexes/PlatformIO.md)

- Relier l'ESP32 sur un port USB d'un PC.

- Vérifier la détection de l'interface USB de l'ESP32 :

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

Ici, le fichier de périphérique est `/dev/ttyUSB0`.

> Il faut aussi vérifier les droits d'accès au fichier de périphérique `/dev/ttyUSB*` où `*` est un numéro. cf. https://docs.platformio.org/en/latest/core/installation/udev-rules.html

- Renseigner le fichier de projet `platformio.ini` pour les champs `upload_port` et `monitor_port` :

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
build_flags = -DDEBUG
upload_port = /dev/ttyUSB0
monitor_port = /dev/ttyUSB0
monitor_speed = 115200
```

- Réaliser un _build_ puis un _upload_

- Démarrer le moniteur série

- Faire un _reset_ de l'ESP32

---
BTS LaSalle Avignon 2026
