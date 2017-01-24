# HM-10/11 BLE Manager
Simple utility to configure and manage the HM-10 and HM-11 BLE modules developed by Huamao technology by providing a minimal console interface.

## Hardware
- [Teensy](https://www.pjrc.com/teensy/) microcontroller
- HM-10/11 module (also available from multiple vendors like [Seed Studio])

## Wiring

| Teensy     | HM-10/11  |
|------------|-----------|
| Pin 0/ RX1 | Pin 2/ TX |
| Pin 1/ TX1 | Pin 4/ RX |
| 3.3V       | VCC       |
| GND        | GND       |

## Usage
A simple console interface is available after connecting to the Teensy over USB Serial:
```
# help
Commands:
info           Show info
reboot         Reboot
factory        Perform factory reset
beacon         Configure as beacon
slave          Configure as peripheral device
master [addr]  Configure as central device and connect to addr
console        Serial console
```

## References
- [HM-10/11 Datasheet](http://fab.cba.mit.edu/classes/863.15/doc/tutorials/programming/bluetooth/bluetooth40_en.pdf)
- [HM-10/11 as peripheral](http://blog.blecentral.com/2015/05/05/hm-10-peripheral)
- [HM-10/11 as ibeacon](http://www.blueluminance.com/HM-10-as-iBeacon.pdf)
- [HM-10/11 overview/tutorial](http://fab.cba.mit.edu/classes/863.15/doc/tutorials/programming/bluetooth.html)
- [BLE Interfacing in OSX/Linux](http://forum.rfduino.com/index.php?topic=73.0)

[Seed Studio]: https://www.seeedstudio.com/Bluetooth-V4.0-HM-11-BLE-Module-p-1803.html
