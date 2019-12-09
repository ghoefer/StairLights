# StairLights
A project to prevent elderly people from falling down the stairs using Arduino and Raspberry Pi.


## Controlling from the Serial Monitor
Turn on the power supply and plug the arduino into your computer. Here are some example commands from [Bruno](https://www.hackster.io/bportaluri/web-controlled-led-animations-with-raspberry-pi-and-arduino-112025)

A=101 - turn on the leds<br/>
A=251 - run a ‘larson scanner’ animation<br/>
P=2 - sets a rainbow palette<br/>
A=242 - another animation<br/>

You can experiment the different commands and combinations following this short reference:

A=[animation code] - Set the animation. Available animation codes are listed in the AlaLed.h header file.<br/>
B=[brightness] - Set the brightness. It must be in the [0-100] range.<br/>
D=[duration] - Set the duration in milliseconds of the animation cycle. Standard values are between 500 and 5000.<br/>
C=[color] - Set the color. It must be an hexadecimal RGB representation like E8A240.<br/>
P=[palette] - Set the palette. It must be in the [0-5] range.<br/>

## Controlling with Web Browser
With help from from [Bruno.](https://www.hackster.io/bportaluri/web-controlled-led-animations-with-raspberry-pi-and-arduino-112025) </br>

In order to connect with Alexa, you'll need to make sure your Raspberry Pi is hosting a server. </br>
1. Navigate to your directory. ***cd /home/pi/AlaWeb/AlaWeb-master*** </br>
2. ***sudo python3 AlaWeb.py /dev/ttyACM0*** </br>
3. The terminal window will now say the current IP address. Navigate there on any web browser and you'll be able to control your the lights! </br>

## Controlling with Alexa
To control with Alexa, I first built an Alexa skill by following [this tutorial](https://www.hackster.io/bportaluri/animated-smart-light-with-alexa-and-arduino-101b4b#comments). For it to work, everything has to be plugged in and on the same wifi. The skill has to be connected to the Alexa device, and the raspberry pi connected to the internet. The raspberry pi must be hosting a server (same server as controlling with Web Browser).

1. Open an a second terminal window and navigate to: **cd /home/pi/LightStrip/LightStrip-master/pi** </br>
2. Then type: **sudo python3 lightstrip.py**
3. Then type: **sudo python3 lightstrip.py /dev/ttyACM0** to connect to the Arduino.
