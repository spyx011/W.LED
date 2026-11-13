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
<img width="546" height="267" alt="Screenshot 2026-11-12 232018" src="https://github.com/user-attachments/assets/937c5b25-1ed3-4e88-9f21-7a4a12fbd90d" />

## Board

- 4 layers, 1.6mm, black solder mask
- Made in KiCad 10
- LEDs on the front, everything else on the back
<img width="710" height="422" alt="Screenshot 2026-11-13 085147" src="https://github.com/user-attachments/assets/851041fe-ec88-47a0-a287-1c1849d7431f" />

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
<img width="1269" height="780" alt="image" src="https://github.com/user-attachments/assets/be7b7fe5-e40b-43a4-b5da-a6692a670bb8" />
