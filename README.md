# Subhub by Bath Spa University Students
Subhub is an LED Display that indicates the schedule / session conducted in a room. 

Subhub is built with an ESP8266 board, 2 WS2812B 8x82 LED Matrix and 1 DS1302 rtc module.

This code is for a project in Physical Computing, Creative Computing.

## How to run project: 
1. Install the latest version of the Arduino IDE
2. Install the necessary add-ons of the ESP8266 board to the IDE
    - [Follow the instructions in this website](https://randomnerdtutorials.com/how-to-install-esp8266-board-arduino-ide/) (except for the code part)
3. Install the usb drivers to accommodate board
    - [Download Here](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)
4. Install all the following libraries: (either through Arduino IDE Library Manager or manually installing)
    - RTCLib by NeiroN
    - Adafruit Neopixel
    - Adafruit Neomatrix
    - Adafruit GFX
5. Setup Arduino IDE > Tools > Board > "NodeMCU 1.0 (ESP-12E Module)"
6. Upload the code to the board

## Notes: 
- make sure you are using a wire that has dIn and dOut. A normal charging wire will not upload the code to the board.

## Errors: 
> DS1302 rtc() does not name a type
- Required Library was not installed, or incorrectly installed.

### Credits: 
- Jaycee Buarao
- Allelee Flores
- Akilah Lapure
- Kimberly Diaz
- Sjunsei Awal
- Shayne Fajardo
- David Francisco
