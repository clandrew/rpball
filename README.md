# Simple Bouncing Ball Sample
This is a graphical demo which runs on:
* Raspberry Pi Pico 2W, with
* Waveshare 1.69" LCD display.

# How It Looks

<img src="https://raw.githubusercontent.com/clandrew/rpball/main/demo.png" width="300">

![Example image](https://raw.githubusercontent.com/clandrew/rpball/main/demo.gif "Example image")

# Setup
Use the following connections:

WaveShare LCD pin | Raspberry Pi Pico 2W semantic pin | Raspberry Pi Pico 2W global pin
--- | --- | --- 
VCC | 3v3 | Pin 39  
GND | GND | Pin 38
DIN | GP19, SPI0 TX | Pin 25
CLK | GP18, SPI0 SCK | Pin 24
CS | GP17, SPI0 CSn |  Pin 22
DC | GP22 |  Pin 29  
RST | GP13 (also SPI1CSn)  |  Pin 17
BL | GP21 |  Pin 27

# Build
The actual democode is all in one file, rpball.ino.

The code is in C++, with some boilerplate pulled in based off of Raspberry Pi and WaveShare samples.

The sketch is compiled and uploaded using Arduino IDE. Tested with Arduino 2.3.10.
