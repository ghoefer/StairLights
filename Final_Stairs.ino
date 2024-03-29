///////////////////////////////////////////////////////////////////////////////////////////
//
// This is for a project I did for my HCD For Robots course at Brown University. 
// It manipulates an LED strip with a distance sensor and an online web page.
//
// This code was mashed from a few different places:
//
// Serial port commands:  http://yaab-arduino.blogspot.com/p/ala-example-rgbstripserial.html
// Fading in and out: https://create.arduino.cc/projecthub/t3chflicks/motion-sensing-under-bed-lights-afe384
// 
//
///////////////////////////////////////////////////////////////////////////////////////////

#include <AlaLedRgb.h>
#include <stdlib.h>
#include "FastLED.h"

#define WS2811_PIN 9    // WS2811 control connected to pin 6
#define NUM_PIXELS 60   // number of leds in the LED strip
#define CMDBUFSIZE 16   // buffer size for receiving serial commands
#define NUM_LEDS 60
CRGB leds[NUM_PIXELS];


//proximity sensor
const int trigPin = 10;
const int echoPin = 11;
long durationDist;
int distance;
int led = 3;
int fadeTimeDiff = 60;

AlaLedRgb rgbStrip;
char cmdBuffer[CMDBUFSIZE];

// global settings and initial values
int animation = ALA_OFF;
AlaColor color = 0xdddddd;
AlaColor white = 0xffffff;
AlaPalette palette = alaPalNull;
int paletteId=0;
float brightness = 0.3;
long duration = 5000;


void setup()
{
  rgbStrip.initWS2812(NUM_PIXELS, WS2811_PIN);
  rgbStrip.setBrightness(color.scale(brightness));
  rgbStrip.setAnimation(animation, duration, color);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  FastLED.addLeds<WS2811, WS2811_PIN, BRG>(leds, NUM_PIXELS); //from t3chs code, sets strip for distance sensor
  
  Serial.begin(9600);

  Serial.println("Welcome to ALA RgbStripSerial example");
  Serial.println("A=[animation code] Set the animation. See https://github.com/bportaluri/ALA/blob/master/src/AlaLed.h");
  Serial.println("B=[brightness]     Set the brightness [0-100]");
  Serial.println("D=[duration]       Set the duration in milliseconds of the animation cycle");
  Serial.println("C=[color]          Set the color (hexadecimal RGB representation ex. 0xE8A240)");
  Serial.println("P=[palette]        Set the palette.");
}

void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  durationDist = pulseIn(echoPin, HIGH);
  distance = (durationDist/2) / 29.1;

  if (distance < 100) { 
  fadeIn();
  Serial.println(distance);
  fadeOut();
    
  }

  else {

  }

  Serial.println(distance);

  
  if (Serial.available())
  {
    int charsRead;
    charsRead = Serial.readBytesUntil('\n', cmdBuffer, sizeof(cmdBuffer) - 1);  //read entire line
    cmdBuffer[charsRead] = '\0';       // Make it a C string
    Serial.print(">"); Serial.println(cmdBuffer);
    
    if(cmdBuffer[1] != '=' || strlen(cmdBuffer)<3)
    {
      Serial.println("KO");
    }
    else
    {
      switch(toupper(cmdBuffer[0]))
      {
      case 'A':
        animation = atoi(&cmdBuffer[2]);
        Serial.println("OK");
        break;
      case 'B':
        brightness = atoi(&cmdBuffer[2]);
        rgbStrip.setBrightness(white.scale((float)brightness / 100));
        Serial.println("OK");
        break;
      case 'C':
        color = strtol(&cmdBuffer[2], 0, 16);
        palette=alaPalNull;
        Serial.println("OK");
        break;
      case 'D':
        duration = atol(&cmdBuffer[2]);
        Serial.println("OK");
        break;
      case 'P':
        paletteId = atoi(&cmdBuffer[2]);
        switch(paletteId)
        {
        case 0:
          palette=alaPalNull;
          break;
        case 1:
          palette=alaPalRgb;
          break;
        case 2:
          palette=alaPalRainbow;
          break;
        case 3:
          palette=alaPalParty;
          break;
        case 4:
          palette=alaPalHeat;
          break;
        case 5:
          palette=alaPalFire;
          break;
        case 6:
          palette=alaPalCool;
          break;
        }
        break;
      
      default:
        Serial.println("KO");
      }
      
      if(palette==alaPalNull)
        rgbStrip.setAnimation(animation, duration, color);
      else
        rgbStrip.setAnimation(animation, duration, palette);
    }
  }

  rgbStrip.runAnimation();
}

  void fadeIn() {
  for (int led = 0; led < NUM_LEDS; led++) {
    leds[led] = CRGB( 150, 60, 15);
  }
  for (int b = 0; b < 255; b += 2) {
    FastLED.setBrightness(b);
    FastLED.show();
    delay(fadeTimeDiff);
  }
}

void fadeOut() {
  for (int led = 0; led < NUM_LEDS; led++) {
    leds[led] = CRGB( 150, 60, 15);
  }
  for (int b = 255; b > 0; b -= 2) {
    FastLED.setBrightness(b);
    FastLED.show();
  }
  for (int led = 0; led < NUM_LEDS; led++) {
    leds[led] = CRGB::Black;
  }
  FastLED.show();
}
