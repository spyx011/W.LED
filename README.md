# W LED Keychain

A keychain PCB with 13 blue LEDs in the shape of a W. It runs on a small LiPo battery and charges over USB-C.

## What's on it

- 13 blue 5mm LEDs in a W (front side)
- ATtiny1616 chip
- 2x 74HC595 and 2x ULN2003A to drive the LEDs
- LiPo battery on a JST connector, charged by USB-C
- Boost converter for 5V
- Slide switch and a push button
- My logo on the back

## Board

- 4 layers, 1.6mm, black solder mask
- Made in KiCad 10
- LEDs on the front, everything else on the back
- 
## How the LEDs work

The ATtiny sends data to the two 74HC595 chips. They feed the ULN2003A chips, and those turn the LEDs on and off.

| ATtiny pin | Goes to |
|---|---|
| PA0 | UPDI header |
| PA1 | 595 data in |
| PA3 | 595 shift clock |
| PA4 | 595 latch |
| PB0 | 595 output enable (brightness) |
| PA6 | Push button |

## Programming

Turn the switch off, take the battery out, and connect a UPDI programmer to the 3 pin header (UPDI, 5V, GND).

## Files

- `hardware` - KiCad files
- `manufacturing` - Gerbers and BOM
- `docs` - pictures

Open `w.led.kicad_pro` in KiCad to see the design.

## Ordering

Pick 4 layers, 1.6mm, black solder mask. Use a LiPo with a protection board, because the charger chip doesn't protect the battery.
