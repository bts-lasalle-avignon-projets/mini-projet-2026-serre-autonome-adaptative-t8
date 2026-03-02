# Adaptateur RS232 TTL / USB

Exemple de produit : [Pl2303TA Adaptateur de Câble USB vers TTL RS-232](https://www.amazon.fr/gp/product/B0F16GYCDG)

![](../images/usb-to-serial-pl2303.jpg)

| Couleur | Fonction |
| :-----: | :------: |
|  Rouge  |   VCC    |
|  Blanc  |    RX    |
|  Vert   |    TX    |
|  Noir   |   GND    |

> [!CAUTION]
> Ne surtout pas relier le fil rouge d'alimentation de l'adaptateur RS232 TTL / USB au microcontrôleur ESP32 !

Détection de l'adaptateur RS232 TTL / USB :

```sh
$ sudo dmesg
...
[442947.388666] usb 1-6.4: New USB device found, idVendor=067b, idProduct=2303, bcdDevice= 3.00
[442947.388670] usb 1-6.4: New USB device strings: Mfr=1, Product=2, SerialNumber=0
[442947.388672] usb 1-6.4: Product: USB-Serial Controller
[442947.388674] usb 1-6.4: Manufacturer: Prolific Technology Inc.
[442947.396053] pl2303 1-6.4:1.0: pl2303 converter detected
[442947.397281] usb 1-6.4: pl2303 converter now attached to ttyUSB1
...

$ lsusb
...
Bus 001 Device 013: ID 067b:2303 Prolific Technology, Inc. PL2303 Serial Port / Mobile Action MA-8910P
...
```

Liens :

- [Le port série](http://tvaira.free.fr/projets/activites/activite-port-serie.html)
- [Mise en oeuvre d’un périphérique USB sous Linux](http://tvaira.free.fr/projets/activites/activite-peripherique-usb.html)
- [Prise en charge d’un périphérique USB sous Linux](http://tvaira.free.fr/projets/activites/peripherique-usb.html)

Annexe :

- [TRANSMISSION_DE_DONNEES.md](./TRANSMISSION_DE_DONNEES.md)

---
&#x1f12f; BTS LaSalle Avignon - 2025 - <<thierry.vaira@gmail.com>>
