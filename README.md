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

