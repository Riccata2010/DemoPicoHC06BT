# DemoPicoHC06BT
Demo for Raspberry pi **PICO** with bluetooth **HC06**.

This demo uses the **PI Pico microcontroller** and the **HC06 Bluetooth** module to turn LEDs on and off.
The source for the Pico is written in C. While to test the demo you can use the **QT/C++** client present in the client folder.
It is possible to obtain the identification of the BT with the command:

### sudo hcitool scan

To connect, use the command:

### fcomm connect hci0 <BT_ID>

To turn on led 1, use the command:

### echo 1 | sudo picocom -qri /dev/rfcomm0

Useful links list:

https://datasheets.raspberrypi.org/pico/pico-datasheet.pdf

https://www.raspberrypi.org/documentation/rp2040/getting-started/

https://www.raspberrypi-spy.co.uk/2021/01/pi-pico-pinout-and-power-pins/




