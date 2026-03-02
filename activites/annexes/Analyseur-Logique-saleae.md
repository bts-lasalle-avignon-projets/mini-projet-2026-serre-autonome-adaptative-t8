# Analyseur logique saleae

On peut utiliser l'analyseur logique [saleae](https://www.saleae.com/) sur le port série n°1 (`Serial1`) pour relever les trames séries échangées.

Liens :

- [Download for Ubuntu](https://www.saleae.com/pages/downloads)
- [Install for Ubuntu](https://support.saleae.com/logic-software/sw-installation)

Détection de l'analyseur logique [saleae](https://www.saleae.com/) :

```sh
$ sudo dmesg
...
[440675.289998] usb 1-6.4: new high-speed USB device number 10 using xhci_hcd
[440675.379124] usb 1-6.4: New USB device found, idVendor=0925, idProduct=3881, bcdDevice= 0.01
[440675.379130] usb 1-6.4: New USB device strings: Mfr=0, Product=0, SerialNumber=0
[440703.518017] usb 1-6.4: USB disconnect, device number 10
[440704.984577] usb 1-6.4: new high-speed USB device number 11 using xhci_hcd
[440705.073125] usb 1-6.4: New USB device found, idVendor=0925, idProduct=3881, bcdDevice= 0.00
[440705.073130] usb 1-6.4: New USB device strings: Mfr=1, Product=2, SerialNumber=0
[440705.073132] usb 1-6.4: Product: Logic
[440705.073133] usb 1-6.4: Manufacturer: Saleae LLC
...

$ lsusb
...
Bus 001 Device 011: ID 0925:3881 Lakeview Research Saleae Logic
...
```

Exemple de capture :

![](../images/capture-saleae.png)


---
&#x1f12f; BTS LaSalle Avignon - 2025 - <<thierry.vaira@gmail.com>>
