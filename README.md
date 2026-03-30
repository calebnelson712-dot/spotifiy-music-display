# Spotify Display
In starter projects I found this one most appealing to me. Cause it looks really cool. Honestly, guide is a bit confusing. 
The project is based on an ESP32 with an ST7735 TFT LCD. I made this project because its a cool way to control music, but also to learn about spi and display control.
<img width="810" height="598" alt="image" src="https://github.com/user-attachments/assets/76fb007c-bee8-4ae9-8c32-edf821f77c9f" />
<img width="812" height="549" alt="image" src="https://github.com/user-attachments/assets/a7512c3e-2fb2-4e51-b5c6-bc0b4b1feaa6" />

# CAD

The CAD is pretty simple, its basically just two parts that click together using a small lip on the back cover. The front cover has a cutout for the screen, keys and encoder, as well as a notch to hold the esp32 in place. The back cover has a cutout for power.
<img width="909" height="662" alt="image" src="https://github.com/user-attachments/assets/2ccf7bc1-a4d1-48fe-a5e1-fe123c198a2e" />

<img width="916" height="605" alt="image" src="https://github.com/user-attachments/assets/8112ca2e-7230-4dad-946e-956815eb4c3f" />

# Electronics
The wiring requires the TFT to be connected via SPI. The pushbuttons and encoder can be attached to any input pins (just need to update the firmware if they are changed) and GND.
<img width="680" height="747" alt="image" src="https://github.com/user-attachments/assets/5b3d7ddb-404e-4e18-8cc1-3cdc527eccd2" />


# Firmware
The firmware using the ESP32spotify library.

# BOM
**Printed Parts**
|Name| Quantity| Picture|
|--|--|--|
|Case| 1| <img width="909" height="662" alt="image" src="https://github.com/user-attachments/assets/fc91b9d5-ec68-47b3-a3d2-8751bf4e03db" /> |
| Back plate| 1| <img width="916" height="605" alt="image" src="https://github.com/user-attachments/assets/81f9969a-eb25-453b-bed4-cc8b0be54698" /> |

**For ease of print, these are combined into one .step file in the repo

**Electronics**
|Name| Quantity| Description| Cost (USD)| Link|
|--|--|--|--|--|
| LCD | 1| LCD to display the tracks | $9.95 |
|jumper wires|1|to connect stuff |7|
|switches |3|keys for buttons|29.97|
|Rotary Encoder (with knob)|Used for volume or menu control|1|$8.89|
|ESP32 Development Board|Main microcontroller used to run the project|2|$10.00|

I require one rotary encoder, three keycaps, and one ESP32, but I already have those at home, so I don't need to purchase them. 
