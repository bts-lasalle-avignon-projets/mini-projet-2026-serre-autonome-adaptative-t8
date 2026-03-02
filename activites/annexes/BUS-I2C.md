# Bus I2C

- [Bus I2C](#bus-i2c)
  - [Présentation](#présentation)
  - [Communication](#communication)
  - [Documentation](#documentation)
  - [Programmation](#programmation)
    - [Arduino (C++)](#arduino-c)
    - [Raspberry Pi Pico W (MicroPython)](#raspberry-pi-pico-w-micropython)

---

## Présentation

[I2C](https://fr.wikipedia.org/wiki/I2C) (_Inter-Integrated Circuit_) est un **bus série synchrone bidirectionnel _half-duplex_**, où plusieurs équipements, maîtres ou esclaves, peuvent être connectés au bus (2 signaux + la masse).

> [!NOTE]
> La norme I2C a été développée par **Philips** en 1982. Depuis elle est maintenue par NXP (ex-division semiconducteurs de Philips). Ce bus porte parfois le nom de **TWI** (_Two Wire Interface_) ou TWSI (_Two Wire Serial Interface_) chez certains constructeurs. Conçu par Philips pour les applications de domotique et d’électronique domestique, il permet de relier facilement un microprocesseur et différents circuits, notamment ceux d’un téléviseur moderne : récepteur de la télécommande, réglages des amplificateurs basses fréquences, tuner, horloge, gestion de la prise péritel, etc.

Il existe d’innombrables périphériques exploitant ce bus, il est même implémentable par logiciel dans n’importe quel microcontrôleur. Le poids de l’industrie de l’électronique grand public a permis des prix très bas grâce à la production de masse.

Exemple d'architecture type d’un bus I2C :

![](./images/i2c-architecture-example.svg)

Ce bus fonctionne en mode **Maître/Esclave**. Ceci signifie que c’est toujours le maître qui initie la communication et les esclaves ne peuvent communiquer directement entre eux.

Les données transitent sur 2 lignes :

- **SDA** (_Serial DAta_) : signal bidirectionnel généré par le maître ou l’esclave qui va coder les données
- **SCL** (_Serial CLock_) : signal d’horloge généré par le maître qui va cadencer les échanges de données

On distingue 5 classes de périphériques (vitesses de transmission) en fonction des fréquences max. supportées pour SCL :

- « _Standard mode_ (Sm) » ≤ 100 kbit/s,
- « _Fast mode_ (Fm) » ≤ 400 kbit/s,
- « _Fast plus mode_ (Fm+) » ≤ 1 Mbit/s,
- « _High-speed mode_ (Hs-mode) » ≤ 3,4 Mbit/s,
- « _Ultra-fast mode_ (UFm) » ≤ 5 Mbit/s, unidirectionnel uniquement.

Le nombre maximum d'équipements est limité par le nombre d'adresses disponibles, **7 bits d'adressage** et un **bit R/W** (lecture ou écriture), soit **128 périphériques**. Chacun des esclaves possède une adresse fixe dans une plage de valeurs figée par construction (il faut consulter la _datasheet_ du composant pour l’obtenir).

> [!IMPORTANT]
> Mais cela dépend également de la capacité du bus (dont dépend la vitesse maximale du bus). Il faut savoir que des adresses sont réservées pour diffuser des messages en _broadcast_ et que de nombreuses adresses sont déjà attribuées par les fabricants ce qui limite grandement le nombre d'équipements (une variante d'adressage sur 10 bits existe également).

Le codage des bits de données sur la ligne **SDA** doit être maintenu stable pendant le niveau « _HIGH_ » sur la ligne **SCL** pour la lecture du bit (« _HIGH_ » `1` ou « _LOW_ » `0`) :

![](https://upload.wikimedia.org/wikipedia/commons/1/16/I2C_Encodage.svg?uselang=fr)

## Communication

La communication sur le bus est orchestrée de la manière suivante :

- Le maître initie le transfert par une combinaision spéciale des signaux **SDA** et **SCL** (la condition de _start_).

![](https://upload.wikimedia.org/wikipedia/commons/e/e8/I2C_START.svg?uselang=fr)

- Le maître envoie sur le bus l’adresse du composant avec qui il souhaite communiquer et indique en même temps l’opération qu’il désire effectuer (`0` pour une écriture ou `1` pour une lecture).

- L’esclave qui reconnaît son adresse répond à son tour par un signal de confirmation **ACK** (_Acknowledge_), accusé de réception

![](https://upload.wikimedia.org/wikipedia/commons/d/d8/I2C_ACK.svg)

- Le maître continue la procédure de communication (écriture ou lecture) avec l’esclave. La communication I2C est orientée **octet** (8 bits). Chaque octet doit être acquitté par le récepteur (**ACK** si transfert OK, **NACK** dans le cas contraire).

- Le maître met fin à la communication par une combinaison spéciale des signaux **SDA** et **SCL** (la condition de stop).

![](https://upload.wikimedia.org/wikipedia/commons/b/b9/I2C_STOP.svg?uselang=fr)

L’octet contenant les 7 bits d’adresse et le bit R/W est transmis de la manière suivante :

![](./images/codage-adresse.svg)

avec :

- A6...​A0 : adresse de l’esclave sur 7 bits
- R/W : sens du transfert initié par le maitre
  - R/W = 0 → le maître veut transmettre des données
  - R/W = 1 → le maitre veut lire des données

## Documentation

- [www.i2c-bus.org](http://www.i2c-bus.org/) : [I2C Bus specification](http://www.i2c-bus.org/fileadmin/ftp/i2c_bus_specification_1995.pdf)

## Programmation

- [ESP32](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/i2c.html) : https://docs.espressif.com/projects/arduino-esp32/en/latest/api/i2c.html
- [Arduino I2C](https://docs.arduino.cc/learn/communication/wire/) : https://docs.arduino.cc/learn/communication/wire/
- [API Arduino Wire](https://docs.arduino.cc/language-reference/en/functions/communication/wire/) : https://docs.arduino.cc/language-reference/en/functions/communication/wire/

### Arduino (C++)

![arduino_i2c_master](https://docs.espressif.com/projects/arduino-esp32/en/latest/_images/arduino_i2c_master.png)

Exemple en mode maître I2C :

```cpp
#include "Wire.h"

#define I2C_DEV_ADDR 0x55

uint32_t i = 0;

void setup()
{
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  // Initializes the Wire library and join the I2C bus as a controller or a peripheral
  // Start the peripheral using the default configuration
  Wire.begin(); // cf. bool begin(int sdaPin, int sclPin, uint32_t frequency);
}

void loop()
{
  delay(5000);

  // Write message to the slave
  Wire.beginTransmission(I2C_DEV_ADDR);
  Wire.printf("Hello World! %lu", i++);
  uint8_t error = Wire.endTransmission(true);
  Serial.printf("endTransmission: %u\n", error);

  // Read 16 bytes from the slave
  uint8_t bytesReceived = Wire.requestFrom(I2C_DEV_ADDR, 16);
  Serial.printf("requestFrom: %u\n", bytesReceived);
  // If received more than zero bytes
  if ((bool)bytesReceived)
  {
    uint8_t temp[bytesReceived];
    Wire.readBytes(temp, bytesReceived);
    log_print_buf(temp, bytesReceived);
  }
}
```

### Raspberry Pi Pico W (MicroPython)

- [Raspberry Pi Pico W](https://docs.micropython.org/en/latest/rp2/quickref.html#software-i2c-bus) Software and Hardware I2C bus : https://docs.micropython.org/en/latest/rp2/quickref.html#software-i2c-bus

Exemple en mode maître I2C :

```python
from machine import Pin, I2C

i2c = I2C(0)   # default assignment: scl=Pin(9), sda=Pin(8)
#i2c = I2C(0, scl=Pin(9), sda=Pin(8), freq=100000)
# Display device address and configuration
i2c.scan()
print("I2C Address: " + hex(i2c.scan()[0]).upper())
print("I2C Configuration: "+str(i2c))

i2c.writeto(76, b'123')
i2c.readfrom(76, 4)

i2c = I2C(1, scl=Pin(7), sda=Pin(6), freq=100000)
i2c.scan()
i2c.writeto_mem(76, 6, b'456')
i2c.readfrom_mem(76, 6, 4)
```

![](./images/pico-default-i2c.png)

---
&#x1f12f; BTS LaSalle Avignon - 2025 - <<thierry.vaira@gmail.com>>
