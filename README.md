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

To power the matrix panel, I used the alligator clips with pig tails to pull power directly from the USB Micro-B wall adapter off of the SparkFun ESP32. However, you can use the following materials instead to power the matrix panel directly with the power cable included with the panel:

* [Wall Adapter Power Supply - 5V DC 2A (Barrel Jack)](https://www.sparkfun.com/products/12889)
* [DC Barrel Jack Adapter - Female](https://www.sparkfun.com/products/10288)

## Hardware Assembly

Below is a table of the pin connections used between the matrix panel and SparkFun's ESP32.

## Software:
You will need to install the Arduino IDE to your desktop and have a Spotify account.

### Spotify
With your Spotify account, you will need to register for a developer account on their <a href="https://developer.spotify.com/dashboard/">website</a>. Don't worry, it is free... so <a href="https://developer.spotify.com/dashboard/">log in here</a>.

[Image]

Once you have logged in, you will need to agree to the terms of service.

[Image]


You will be sent over to the **DASHBOARD**. *Click* either the Create App box or **CREATE A CLIENT ID** button.

[Image]

Name your app, add a description, and select "*what you are building*".

Agree to the terms again.

Now that you have setup your App, you will need to do 2 things. Set the redirect URI and retrieve the Client ID and Client Secret for the API.

#### Redireect URI

To set the redirect URI, select *click* the **EDIT SETTINGS** button. Find the entry for *Redirect URIs* and enter `http://esp32.local/callback`.

#### Redireect URI

To grab the Client Secret, *click* the **SHOW CLIENT SECRET**. You will need this information for the settings header file `settings.h` in the Arduino sketch.

### Arduino IDE

You can [download the Arduino IDE](http://arduino.cc/en/Main/Software) from their website. They have [installation instructions](https://www.arduino.cc/en/Guide/HomePage)

<b>Note:</b> This section assumes you are using the latest stable version of the Arduino IDE on your desktop. If this is your first time using Arduino, please review our tutorial on <a href="https://learn.sparkfun.com/tutorials/installing-arduino-ide">installing the Arduino IDE.</a> If you have not previously installed an Arduino library, please check out our <a href="https://learn.sparkfun.com/tutorials/installing-an-arduino-library">installation guide.</a>

<ul>
  
  #### Adding ESP 32 to Board Manager
  
  Espressif has made it simple to install the ESP32 core into the Arduino IDE. You can find instructions on their <a href="https://github.com/espressif/arduino-esp32">GitHub page</a>. Otherwise, you can also find instructions on <a href="https://learn.sparkfun.com/tutorials/esp32-thing-hookup-guide#installing-via-arduino-ide-boards-manager"> SparkFun's ESP32 Thing Hookup Guide</a>.
  
  #### Required Libraries
  This code requires several libraries to run. Please make sure to install the folowing libraries through the library manager:
  
  * [JSON Streaming Parser](https://github.com/squix78/json-streaming-parser)
  * [JPEGDecoder](https://github.com/Bodmer/JPEGDecoder)
  * [PxMatrix](https://github.com/2dom/PxMatrix)
  * [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library)

  * [FastLED](https://github.com/FastLED/FastLED) ????

</ul>

#### Copy the Code

This should be obvious, but download/copy the code from this repository. All 4 files should be in the same folder.

#### Settings.h

You will need to modify the settings header file `settings.h` to set the board up for your WiFi and your Spotify API.
Enter in the credentials for your WiFi network. If you are on a corporate or school network, you may need to contact your IT administrator.

#### Uploading
Select the SparkFun ESP32 Thing as your board. Select the port for your board; then upload to the ESP32.

It may take a few minutes for the Arduino IDE to compile the sketch.

#### Get IP Address

Once you have finished uplaoding the sketch, you need to open the Serial Monitor. Remember to set the baudrate to 115200 bps; otherwise, you will see nothing or a bunch of jibberish. You should see the board connecting to your network. Once the ESP32 has connected to your WiFI network, it will display the IP Adress in the Serial Monitor. (_To keep the Serial Monitor from scolling, uncheck the **Autoscroll** box on the lower lefthand corner of the Serial Monitor._)

If you miss this you can reset the board with the **RST** button.




