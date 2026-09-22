# Zarmatik: D&D Dice Roller

<img width="2448" height="918" alt="ZarmatikCover" src="https://github.com/user-attachments/assets/1bd65dda-4f41-46a4-9a70-56aa2e3d9bfb" />

**Zarmatik** is a small DIY electronic dice roller designed for tabletop RPGs such as Dungeons & Dragons.

It can roll the standard D&D dice:

**d4 · d6 · d8 · d10 · d12 · d20**

Dice rolls are displayed on a 240×240 IPS screen, with a custom animation for each type of die.

The project was designed to be simple to build, compact, and easy to reproduce. The source code and 3D-printable enclosure files are included in this repository.

## Features

- Custom dice-roll animations
- Powered by ESP32
- Built on a simple perfboard
- Compact 3D-printable enclosure
- Designed with easily obtainable components
- Fully open source

## Hardware

- ESP32-WROOM-32U
- 1.3 inch Oled TFT LCD screen
- 3x Push Button
- Perfboard

Sources used for the project: 
- [LCD Screen Wiring](https://arduino-er.blogspot.com/2020/07/esp32-13-inch-240x240-ips-lcd-st7789.html)
- [LCD Screen Library](https://doc-tft-espi.readthedocs.io/)
- [Button Wiring](https://esp32io.com/tutorials/esp32-button)
- [Vertex Coordinates for Dice Shapes](https://en.wikipedia.org/wiki/Platonic_solid)

## Perfboard Design

<img width="2448" height="917" alt="Circuit" src="https://github.com/user-attachments/assets/bcc51ac1-d224-4649-b612-08b84418249b" />

## 3D Printed Enclosure

<img width="2552" height="1914" alt="IMG_6544" src="https://github.com/user-attachments/assets/cd207863-0437-45c3-8151-751531cbfa22" />

## Controls

The three buttons are used to navigate the interface and roll dice.

| Button | Function |
|--------|----------|
| Left   | Previous / Menu |
| Center | Select / Roll |
| Right  | Next |
