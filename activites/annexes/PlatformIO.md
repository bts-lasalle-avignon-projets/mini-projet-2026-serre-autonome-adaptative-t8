# PlatformIO

> Pour aller plus loin : [https://github.com/bts-lasalle-avignon-ressources/PlatformIO](https://github.com/bts-lasalle-avignon-ressources/PlatformIO)

## Présentation

**[PlatformIO](https://platformio.org/)** est un écosystème _open source_ dédié au développement [IoT](https://fr.wikipedia.org/wiki/Internet_des_objets) qui va faciliter le développement embarqué professionnel.

> [!NOTE]
> En juin 20204, il prend en charge plus de 1500 cartes de développement des principaux micro-contrôleurs (Atmel, ESP8266 et ESP32, STM32, etc ...), 40 plateformes et plus de 20 _frameworks_ regroupant plus de 130000 bibliothèques.

![](https://cdn.platformio.org/images/platformio-logo.17fdc3bc.png)

Site : [platformio.org](https://platformio.org/)

Documentations :

- https://docs.platformio.org/en/latest/
- https://docs.platformio.org/en/latest/what-is-platformio.html

[PlatformIO IDE](https://platformio.org/platformio-ide) est l'environnement de développement C/C++ pour les systèmes embarqués supportés. Il est multi-plateformes (Windows, Mac et GNU/Linux) et il fournit une [extension](https://platformio.org/install/ide?install=vscode) à [VSCode](https://code.visualstudio.com/).

> [!NOTE]
> [VSCode](https://code.visualstudio.com/) (ou [Visual Studio Code](https://code.visualstudio.com/)) est un éditeur de code source extensible et disponible pour Windows, macOS et Linux.

Documentation : https://docs.platformio.org/en/latest/integration/ide/vscode.html#quick-start

## Installation

Liens :

- [Download VSCode](https://code.visualstudio.com/Download)
- [Installing VSCode on Linux](https://code.visualstudio.com/docs/setup/linux)
- [Installing PlatformIO IDE for VSCode](https://platformio.org/install/ide?install=vscode)

Installation sous Debian/Ubuntu :

- Pré-requis

```sh
$ sudo apt-get install wget gpg
$ sudo apt-get install apt-transport-https
```

- Installer VSCode si besoin

```sh
$ wget -qO- https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > packages.microsoft.gpg
$ sudo install -D -o root -g root -m 644 packages.microsoft.gpg /etc/apt/keyrings/packages.microsoft.gpg
$ echo "deb [arch=amd64,arm64,armhf signed-by=/etc/apt/keyrings/packages.microsoft.gpg] https://packages.microsoft.com/repos/code stable main" |sudo tee /etc/apt/sources.list.d/vscode.list > /dev/null
$ rm -f packages.microsoft.gpg

$ sudo apt-get update
$ sudo apt-get install code
```

- Installer PlatformIO

Démarrer VSCode

Aller dans File &rarr; Preferences &rarr; Extensions

Rechercher le _package_ `platformio-ide` et l'installer

## platformio.ini

[platformio.ini](https://docs.platformio.org/en/latest/projectconf/index.html) est le fichier de configuration d'un projet PlatformIO.

> [!NOTE]
> Un [fichier INI](https://fr.wikipedia.org/wiki/Fichier_INI) est un **fichier de configuration** dans un format de données introduit par les systèmes d’exploitation Windows en 1985. Par convention les noms de ces fichiers portent l’extension `.ini`.
> 
> Les fichiers INI sont des **fichiers texte** : ils peuvent donc être manipulés avec un éditeur de texte (`vim`, `emacs`, etc.). Les fichiers sont divisés en **sections**. Chaque section comporte un certain nombre de **paramètres de configuration**. Chaque section commence par un titre placé entre crochets `[` et `]`.
> 
> La valeur de chaque paramètre de configuration est indiquée par une formule : `paramètre = valeur`. Les fichiers peuvent contenir des **commentaires**. Les commentaires sont souvent utilisés pour décrire les paramètres et les valeurs à introduire. Ils sont précédés d’un point-virgule `;` ou plus rarement d’un dièse `#`.

Le fichier [platformio.ini](https://docs.platformio.org/en/latest/projectconf/index.html) peut contenir plusieurs sections notamment la (ou les) section(s) `[env]` qui permet de déclarer un environnement de configuration définissant les tâches pour la construction, la programmation, le débogage, les tests unitaires, la surveillance des périphériques, les dépendances de bibliothèque, etc.

> Chaque projet peut avoir plusieurs environnements de configuration. Dans ce cas, on doit lui donner un **nom** (`[env:nom]`). Le nom peut être alors utilisé en option `-e` (ou `--environment`) des commandes `pio` de PlatformIO. Le nom peut aussi être récupéré dans la variable `$PIOENV`.

Exemple de fichier [platformio.ini](https://docs.platformio.org/en/latest/projectconf/index.html) :

```ini
[env]
platform = espressif32
board = esp32dev
framework = arduino
lib_deps =
    bblanchon/ArduinoJson @ ^6.21.2
monitor_port = /dev/ttyUSB0
monitor_speed = 115200
```

Un environnement (`[env]`) est défini par au moins trois paramètres :

- la plateforme (_platform_) qui permet l'intégration des cartes spécifiques d'un fabricant (kits de développement, MCU), de _frameworks_ et de SDK.
- la carte (_board_) qui dispose de paramètres préconfigurés pour les tâches de fabrication, programmation, débogage, etc.
- le _framework_ de développement

Dans PlatformIO, une plateforme (_platform_) de développement est une architecture particulière de microcontrôleur sur laquelle les projets peuvent être compilés pour s'exécuter.

Pour chaque plateforme de développement, PlatformIO définit :

- les scripts de construction pour les frameworks et SDK pris en charge
- des préréglages
- les chaînes d'outils pour la ou les architectures

Chaque projet doit spécifier le **nom** de la plateforme à l'aide de l'option `platform` dans le fichier de configuration du projet `platformio.ini`.

Pour les micro-contrôleurs ESP32, la plateforme est `espressif32`.

Recherche des cartes ESP32 :

```bash
$ pio boards esp32

Platform: espressif32
===============================================================================================================================================================================================
ID                                   MCU      Frequency    Flash    RAM     Name
-----------------------------------  -------  -----------  -------  ------  ---------------------------------------------------
...
esp32dev                             ESP32    240MHz       4MB      320KB   Espressif ESP32 Dev Module
...
nodemcu-32s                          ESP32    240MHz       4MB      320KB   NodeMCU-32S
...
lolin32                              ESP32    240MHz       4MB      320KB   WEMOS LOLIN32
...
```

> PlatformIO prend en charge plus de [1500 cartes](https://docs.platformio.org/en/latest/boards/index.html#boards).

Sachant que ce module d'[AZ-Delivery](https://www.az-delivery.de/fr/) ne possède pas de définition dans PlatormIO, on peut choisir un des trois IDs : [lolin32](https://docs.platformio.org/en/latest/boards/espressif32/lolin32.html), [esp32dev](https://docs.platformio.org/en/latest/boards/espressif32/esp32dev.html) ou [nodemcu-32s](https://docs.platformio.org/en/latest/boards/espressif32/nodemcu-32s.html).

La plateforme [espressif32](https://docs.platformio.org/en/latest/platforms/espressif32.html#platform-espressif32) supporte deux _frameworks_ :

- [arduino](https://docs.platformio.org/en/latest/frameworks/arduino.html) : un portage du _framework_ [Arduino pour ESP32](https://github.com/espressif/arduino-esp32)
- [espidf](https://docs.platformio.org/en/latest/frameworks/espidf.html#framework-espidf) : le _framework_ officiel d'[Espressif](https://github.com/espressif/esp-idf)

On utilisera le _framework_ **Arduino**.

Lien : https://docs.platformio.org/en/latest/frameworks/arduino.html

Pour ajouter des bibliothèques de la communauté au projet, il suffit d'ajouter leur nom (ou leur ID) dans la variable `lib_deps` du fichier `platformio.ini`.

> PlatformIO fournit un outil de recherche de bibliothèques. Il est aussi possible d'indiquer la version de la bibliothèque désirée en respectant les règles syntaxique définies [ici](https://docs.platformio.org/en/latest/userguide/lib/cmd_install.html#description).

Exemple de fichier `platformio.ini` pour une [Arduino Uno](https://fr.wikipedia.org/wiki/Arduino_Uno) :

```ini
[env:uno]
platform = atmelavr
board = uno
framework = arduino
```

![](https://upload.wikimedia.org/wikipedia/commons/3/38/Arduino_Uno_-_R3.jpg)

## Utilisation

Dans VSCode :

![](./images/platformio-home.png)

Il faut "Ouvrir un projet" (_Open Project_).

> Dans PlatformIO, cela signifie un répertoire contenant un fichier `platformio.ini`.

![](./images/open-project-exemple.png)

Architecture du projet [exemple](./exemples/arduino-esp32/) :

```txt
/exemples/arduino-esp32
  ├── include/
  ├── lib/
  ├── src/main.cpp (Code source)
  ├── test/
  ├── platformio.ini (Fichier décrivant le projet)
```

> Le répertoire `include` est destiné aux fichiers d'en-tête du projet. Un fichier d'en-tête est un fichier contenant des déclarations. cf. [README](./src/sonde-esp32/include/README).
> 
> Le répertoire `lib` est destiné aux bibliothèques privées spécifiques au projet. PlatformIO les compilera en bibliothèques statiques et les liera au fichier exécutable. Le code source de chaque bibliothèque doit être placé dans un répertoire distinct. cf. [README](./src/sonde-esp32/lib/README)

Dans PlatformIO, on peut accéder aux fonctionnalités de base pour programmer des systèmes embarqués Arduino UNO, ESP32, etc. (fabrication, téléversage, moniteur, ...) par la barre d'outils en bas de VS Code. Il est aussi possible d'utiliser un mode CLI (_Command Line Interface_) avec l'utilitaire `platformio` (ou son alias `pio`).

Dans VSCode, il possible de démarrer un terminal et utiliser cet utilitaire :

![](./images/open-terminal-exemple.png)

```sh
$ platformio --version
PlatformIO Core, version 6.1.4

$ pio --version
PlatformIO Core, version 6.1.4

$ platformio --help
$ pio --help
Usage: platformio [OPTIONS] COMMAND [ARGS]...

Options:
  --version          Show the version and exit.
  -f, --force        DEPRECATE
  -c, --caller TEXT  Caller ID (service)
  --no-ansi          Do not print ANSI control characters
  -h, --help         Show this message and exit.

Commands:
  account   Manage PIO Account
  boards    Embedded Board Explorer
  check     Run a static analysis tool on code
  ci        Continuous Integration
  debug     PIO Unified Debugger
  device    Monitor device or list existing
  home      PIO Home
  lib       Library Manager
  platform  Platform Manager
  project   Project Manager
  remote    PIO Remote
  run       Process project environments
  settings  Manage PlatformIO settings
  test      Unit Testing
  update    Update installed platforms, packages and libraries
  upgrade   Upgrade PlatformIO to the latest version
```

> [!TIP]
> Pour y accéder à partir d'un terminal, on peut ajouter ces lignes à la fin du fichier `~/.bashrc` :
> ```sh
> # plaformio
> export PLATFORMIO_INSTALL="$HOME/.platformio"
> export PATH=$PLATFORMIO_INSTALL/penv/bin:$PLATFORMIO_INSTALL/packages/tool-esptoolpy/:$PATH
> ```

- Fabriquer un projet (_build_)

```sh
$ pio run -v
```

Les fichiers générés pendant la fabrication sont stockés dans un répertoire `.pio`.

> [!IMPORTANT]
> Ces fichiers ne doivent jamais être conservés dans un dépôt `git`.

![](./images/platformio-build.png)

- Programmer le système embarqué (_upload_)

```sh
$ pio run --target upload -v
```

> [!NOTE]
> On peut lister les cibles disponibles avec `pio run --list-targets`

![](./images/platformio-upload.png)

> [!TIP]
> Les fichiers générés à la fabrication peuvent être supprimés avec la commande suivante :
> ```sh
> $ pio run --target clean
> ```

- Monitorer

> Tous les affichages envoyés sur la liaison série (`Serial.print()` par exemple) seront affichés dans le moniteur.

Les options disponibles sont :

```sh
$ platformio device monitor --help
Usage: platformio device monitor [OPTIONS]

Options:
  -p, --port TEXT       Port, a number or a device name
  -b, --baud INTEGER    Set baud rate, default=9600
  --parity [N|E|O|S|M]  Set parity, default=N
  --rtscts              Enable RTS/CTS flow control, default=Off
  --xonxoff             Enable software flow control, default=Off
  --rts [0|1]           Set initial RTS line state, default=0
  --dtr [0|1]           Set initial DTR line state, default=0
  --echo                Enable local echo, default=Off
  --encoding TEXT       Set the encoding for the serial port (e.g. hexlify,
                        Latin1, UTF-8), default: UTF-8
  -f, --filter TEXT     Add filters / text transformation
  --eol [CR|LF|CRLF]    End of line mode, default=CRLF
  --raw                 Do not apply any encodings/transformations
  --exit-char INTEGER   ASCII code of special character that is used to exit
                        the application, default=29 (DEC)
  --menu-char INTEGER   ASCII code of special character that is used to
                        control miniterm (menu), default=20 (DEC)
  --quiet               Diagnostics: suppress non-error messages, default=Off
  -h, --help            Show this message and exit.
```

Liste des ports disponibles :

```sh
$ platformio device list
...
/dev/ttyUSB0
------------
Hardware ID: USB VID:PID=10C4:EA60 SER=0001 LOCATION=1-2
Description: CP2102 USB to UART Bridge Controller - CP2102 USB to UART Bridge Controller
```

Les options peuvent être placées directement dans le fichier `plaftform.ini`, par exemple :

```ini
...
monitor_port = /dev/ttyUSB0
monitor_speed = 115200
```

Exemples :

```sh
$ platformio device monitor -p /dev/ttyUSB0
...

$ platformio device monitor -p /dev/ttyUSB0 --encoding hexlify
...
--- Miniterm on /dev/ttyUSB0  115200,8,N,1 ---
--- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
53 74 61 72 74 20 53 54 4D 33 32 4C 34 37 35 0A
```

![](./images/platformio-monitor.png)

## Exemple

Ouvrir le projet [exemples/arduino-esp32/](./exemples/arduino-esp32/) :

![](./images/open-project-exemple.png)

Puis ouvrir un terminal :

![](./images/open-terminal-exemple.png)

- Le fichier `platformio.ini` :

```sh
$ cd exemples/arduino-esp32
$ cat platformio.ini
[env:esp32dev_debug]
platform = espressif32
board = esp32dev
framework = arduino
build_flags = -DDEBUG
monitor_port = /dev/ttyUSB0
monitor_speed = 115200
```

- Fabriquer et téléverser le _firmware_ dans l'ESP32 :

```sh
$ pio run --environment esp32dev_debug --target upload -v
```

- Monitorer l'exécution (puis appuyer sur le bouton **RST** de l'ESP32):

```sh
$ pio device monitor -p /dev/ttyUSB0
--- Terminal on /dev/ttyUSB0 | 115200 8-N-1
--- Available filters and text transformations: colorize, debug, default, direct, esp32_exception_decoder, hexlify, log2file, nocontrol, printable, send_on_enter, time
--- More details at https://bit.ly/pio-monitor-filters
--- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H
rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:2
load:0x3fff0030,len:1184
load:0x40078000,len:13232
load:0x40080400,len:3028
entry 0x400805e4
Setup done
CPU freq : 240 MHz
CPU cores : 2
Flash size : 4 MB
Free RAM : 351484 bytes
Hello world!
Hello world!
...
```

> Ctrl-C pour quitter

- Obtenir des informations sur le microcontrôleur (adresse MAC, taille mémoire, etc.) :

```sh
$ esptool.py --port /dev/ttyUSB0 --chip esp32 flash_id
esptool.py v4.5.1
Serial port /dev/ttyUSB0
Connecting....
Chip is ESP32-D0WDQ6 (revision v1.0)
Features: WiFi, BT, Dual Core, 240MHz, VRef calibration in efuse, Coding Scheme None
Crystal is 40MHz
MAC: 24:62:ab:f2:5a:18
Uploading stub...
Running stub...
Stub running...
Manufacturer: 68
Device: 4016
Detected flash size: 4MB
Hard resetting via RTS pin...
```

> [esptool.py](https://docs.espressif.com/projects/esptool/en/latest/esp32/esptool/index.html) est un utilitaire Python pour communiquer avec le chargeur de démarrage (_bootloader_) des puces Espressif. Il permet notamment de téléverser (_flasher_) un micrologiciel (_firmware_).

---
&#x1f12f; BTS LaSalle Avignon - 2025 - <<thierry.vaira@gmail.com>>
