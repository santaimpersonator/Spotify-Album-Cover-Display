# Spotify-Album-Cover-Display
Spotify Album Cover Display using SparkFun ESP32 and 64x64 RGB LED Matrix Panel.

_This code is based off the <a href="https://github.com/ThingPulse/esp8266-spotify-remote/">ESP8266 Spotify Remote</a>, written by Thing Pulse._

## Introduction

This code sets up your ESP32 as a webpage server and loads a 64x64 pixel image from the
Spotify Client API. The ESP32 then decodes the jpg image into an 8-bit color array that
gets displayed on the matrix panel.

## Required Hardware

This code is written for the SparkFun ESP32 Thing and the 64x64 RGB LED Matrix Panel. Below is a list of all the materials used in this project. If you enjoy this project, please support SparkFun!

* [SparkFun ESP32 Thing](https://www.sparkfun.com/products/13907)
* [ESP32 Thing Stackable Header Set](https://www.sparkfun.com/products/14311)
* [RGB LED Matrix Panel - 64x64](https://www.sparkfun.com/products/14824)
* [Jumper Wires Premium 6" M/M Pack of 10](https://www.sparkfun.com/products/8431)
* [Jumper Wires Premium 12" M/F Pack of 10](https://www.sparkfun.com/products/9385)
* [Wall Adapter Power Supply - 5.1V DC 2.5A (USB Micro-B)](https://www.sparkfun.com/products/13831)
* [Alligator Clip with Pigtail (4 Pack)](https://www.sparkfun.com/products/13191)

If you wish to use other hardware, you may need to adapt the code to work with your setup.

### Optional Hardware

This project does require a small amount of soldering for the headers. If you do not have access to soldering equipment, you can find a starter kit here:

* [SparkFun Beginner Tool Kit](https://www.sparkfun.com/products/14681)

To power the matrix panel, I use the alligator clips with pig tails to pull power directly from the USB Micro-B wall adapter off of the SparkFun ESP32. However, you can use the following materials instead to power the matrix panel directly with the power cable included with the panel:

* [Wall Adapter Power Supply - 5V DC 2A (Barrel Jack)](https://www.sparkfun.com/products/12889)
* [DC Barrel Jack Adapter - Female](https://www.sparkfun.com/products/10288)

## Hardware Assembly

Below is a table of the pin connections used between the matrix panel and SparkFun's ESP32.

## Software: Arduino IDE

You can [download the Arduino IDE](http://arduino.cc/en/Main/Software) from their website. They have [installation instructions](https://www.arduino.cc/en/Guide/HomePage)

<b>Note:</b> This section assumes you are using the latest stable version of the Arduino IDE on your desktop. If this is your first time using Arduino, please review our tutorial on <a href="https://learn.sparkfun.com/tutorials/installing-arduino-ide">installing the Arduino IDE.</a> If you have not previously installed an Arduino library, please check out our <a href="https://learn.sparkfun.com/tutorials/installing-an-arduino-library">installation guide.</a>

### Adding ESP 32 to Board Manager

Espressif has made it simple to install the ESP32 core into the Arduino IDE. You can find instructions on their <a href="https://github.com/espressif/arduino-esp32">GitHub page</a>. Otherwise, you can also find instructions on <a href="https://learn.sparkfun.com/tutorials/esp32-thing-hookup-guide#installing-via-arduino-ide-boards-manager"> SparkFun's ESP32 Thing Hookup Guide</a>.

### Required Libraries
This code requires several libraries to run:

* [JPEGDecoder](https://github.com/Bodmer/JPEGDecoder)
* [PxMatrix](https://github.com/2dom/PxMatrix)
* [FastLED](https://github.com/FastLED/FastLED)
* [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library)
