#include <Arduino.h>
/*
the lines above  needs to be declared before #include "FastLed.h"
NBIS2SERIALPINS represents the number of pins used by the esp value, it ranges from 1->15
NUM_LEDS_PER_STRIP the length of your strip if you have different strips size put here the longest strip
for each pin you would be able to drive 8 virtuals pins
linked the 74hc595 with the strips
Q0/PIN 15 => VIRTUAL PIN 8
Q1/PIN 1  => VIRTUAL PIN 7
Q2/PIN 2  => VIRTUAL PIN 6
Q3/PIN 3  => VIRTUAL PIN 5
Q4/PIN 4  => VIRTUAL PIN 4
Q5/PIN 5  => VIRTUAL PIN 3
Q6/PIN 6  => VIRTUAL PIN 2
Q7/PIN 7  => VIRTUAL PIN 1
*/
#define ESP32_VIRTUAL_DRIVER true //To enable virtual pin driver for esp32
#define ESP_VIRTUAL_DRIVER_8 1 //to use the 8:1 ratio
#define NBIS2SERIALPINS 4 // you will be able to drive up to 32 strips the number of strips will be always a multiple of 8
#define NUM_LEDS_PER_STRIP 60 //the length of your strip if you have different strips size put here the longuest strip

#include "FastLED.h"
#define CLOCK_PIN 25 //for a reason I don't know, the CLOCK_PIN needs to be >=16
#define LATCH_PIN 27

#define NUM_STRIPS 28
#define NUM_LEDS NUM_LEDS_PER_STRIP * NUM_STRIPS
CRGB leds[NUM_LEDS];
byte hue;
int start;

int Pins[NBIS2SERIALPINS]={22,14,26,32}; //example pins
/*
* Define the esp pins you are using
* pin 12 will drive strip 1->8
* pin 14 will drive strip 9->16
* pin 26 will drive strip 17->24
* pin 25 will drive strip 25->32 but you need only 25->28
*/

void basic(){
  EVERY_N_MILLIS(8){
    //FastLED.clear();
    for(int i = 0; i < NUM_LEDS; i++){
      leds[i] = CHSV(hue + i*5, 255, 255);
    }
    hue++;
    long lastHandle = __clock_cycles();
    FastLED.show();
    long lasthandle2=__clock_cycles();
    Serial.printf("FPS: %f \n", (float) 240000000L/(lasthandle2 - lastHandle));
    //start++;
  }
  //delay(30);
}

void snake(){
  /*
  fill_solid(leds, NUM_LEDS, CRGB(15,15,15));
  for(int i=0;i<NUM_STRIPS;i++){      // Snake
      int offset=i*NUM_LEDS_PER_STRIP;   //this is the offset of the strip number i
      for(int k=0;k<i+1;k++){
          leds[(start+k)%NUM_LEDS_PER_STRIP+offset]=CHSV(i*255/NUM_STRIPS,255,255);
      }
  }*/
  for(int i = 0; i < NUM_LEDS; i++){
      leds[i] = CHSV(hue + i*5, 255, 255);
    }
    hue++;
  random8();
  long lastHandle = __clock_cycles();
  FastLED.show();
  long lasthandle2=__clock_cycles();
  Serial.printf("FPS fastled: %f \n", (float) 240000000L/(lasthandle2 - lastHandle));
  start++;
  delay(30);
}
void setup() {
    Serial.begin(115200);
    //FastLED.setDither(0);
    FastLED.addLeds<VIRTUAL_DRIVER,Pins,CLOCK_PIN, LATCH_PIN>(leds,NUM_LEDS_PER_STRIP);
    FastLED.setBrightness(44);
}

void loop() {
  basic();
  //snake();
}