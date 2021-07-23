#include <Arduino.h>
#include <dumbconfig.h>
#include <Myriad_BT.h>

void basic(){
  static byte huep;
  EVERY_N_MILLIS(4){
    FastLED.clear();
    //for(int i = 0; i < NUM_LEDS; i++){
    //  leds[i] = CHSV(hue + i*5, 255, 255);
    //}
    
    for(int x = 0; x < NUM_STRIPS; x++){
      for (int y = 0 ; y < NUM_LEDS_PER_STRIP; y++){
        //leds[x*NUM_LEDS_PER_STRIP + y] = CHSV(0,0,0);
        leds[x*NUM_LEDS_PER_STRIP + y] = CHSV(huep+y*5,255,255);
      }
      for(int i = 0; i < x; i++){
          //leds[x*NUM_LEDS_PER_STRIP + i] = CHSV(hue+i*5,255,255);
      }
    }
    
    huep++;
    //long lastHandle = __clock_cycles();
    FastLED.show();
    //long lasthandle2=__clock_cycles();
    //Serial.printf("FPS: %f \n", (float) 240000000L/(lasthandle2 - lastHandle));
    EVERY_N_MILLIS(500){
      Serial.print("FPS: ");
      Serial.print(LEDS.getFPS());
      Serial.print(" POWER: ");
      Serial.println(calculate_unscaled_power_mW(leds, NUM_LEDS)/5/100);
    }
  }
}/*

void snake(){
  
  fill_solid(leds, NUM_LEDS, CRGB(15,15,15));
  for(int i=0;i<NUM_STRIPS;i++){      // Snake
      int offset=i*NUM_LEDS_PER_STRIP;   //this is the offset of the strip number i
      for(int k=0;k<i+1;k++){
          leds[(start+k)%NUM_LEDS_PER_STRIP+offset]=CHSV(i*255/NUM_STRIPS,255,255);
      }
  }
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
*/
void setup() {
    Serial.begin(115200);
    //FastLED.setDither(0);
    FastLED.addLeds<VIRTUAL_DRIVER,Pins,CLOCK_PIN, LATCH_PIN>(leds,NUM_LEDS_PER_STRIP);
    FastLED.setBrightness(25);
    //Bluetooth.begin("Starshroud");
}

void loop() {
  EVERY_N_MILLIS(4){
    basic();
    //Tropic(newP);
    FastLED.show();
  }
  //basic();
  //snake();
}