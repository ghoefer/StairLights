/*
   T3chFlicks - Motion Sensing Under Bed Lighting
   Free to use and distribute.
   Find the tutorial and parts list at https://t3chflicks.com/shop/kit/motion-sensing-under-bed-lights/
*/

#include "FastLED.h"
#define LED_DATA_PIN 9
#define NUM_LEDS 60
CRGB leds[NUM_LEDS];

int onTime = 3*1000; // 30 seconds
int motion_sensor_left = 10;
int motion_sensor_right = 11;
int motion_sensor_front = 12;
int fadeTimeDiff = 60;
int led = 3;

void setup() {
  FastLED.addLeds<WS2811, LED_DATA_PIN, BRG>(leds, NUM_LEDS);
  pinMode(motion_sensor_left, INPUT);
  pinMode(motion_sensor_right, INPUT);
  pinMode(motion_sensor_front, INPUT);
  Serial.begin(9600);
  pinMode(led, OUTPUT);

  delay(3000);
}

void loop() {
  Serial.println(digitalRead(motion_sensor_right));
  if (digitalRead(motion_sensor_left) == 1 || digitalRead(motion_sensor_right) == 1 || digitalRead(motion_sensor_front) == 1) {
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    fadeIn();
    delay(onTime);
    fadeOut();
    Serial.println("loop");
    digitalWrite(led, HIGH);    // turn the LED off by making the voltage LOW
  }
  else {
    Serial.println("no loop");
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  }
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
    delay(fadeTimeDiff);
  }
  for (int led = 0; led < NUM_LEDS; led++) {
    leds[led] = CRGB::Black;
  }
  FastLED.show();
}
