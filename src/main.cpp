#include <Arduino.h>
static TaskHandle_t FastLEDshowTaskHandle = 0;
static TaskHandle_t userTaskHandle = 0;
#include <dumbconfig.h>
//#include <dumbbt.h>
#include <BluetoothSerial.h>
BluetoothSerial Bluetooth;

void FastLEDshowESP32()
{
    if (userTaskHandle == 0) {
        const TickType_t xMaxBlockTime = pdMS_TO_TICKS( 200 );
        // -- Store the handle of the current task, so that the show task can
        //    notify it when it's done
       // noInterrupts();
        userTaskHandle = xTaskGetCurrentTaskHandle();
        
        // -- Trigger the show task
        xTaskNotifyGive(FastLEDshowTaskHandle);

        // -- Wait to be notified that it's done
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        //delay(100);
        //interrupts();
        userTaskHandle = 0;
    }
}

void FastLEDshowTask(void *pvParameters)
{
    const TickType_t xMaxBlockTime = pdMS_TO_TICKS( 500 );
    // -- Run forever...
    for(;;) {
        // -- Wait for the trigger
        ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
        
     // time3=ESP.getCycleCount();
    
         //controller.showPixels(); /
     FastLED.show();
       // Serial.printf("FPS:%f\n",(float)(240000000/(ESP.getCycleCount()-time3)));

    
        xTaskNotifyGive(userTaskHandle);
    }
}

void basic(){
  static byte huep;
  EVERY_N_MILLIS(4){
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
    FastLEDshowESP32();
    //long lasthandle2=__clock_cycles();
    //Serial.printf("FPS: %f \n", (float) 240000000L/(lasthandle2 - lastHandle));
    EVERY_N_MILLIS(500){
      Serial.print("FPS: ");
      Serial.print(LEDS.getFPS());
      Serial.print(" POWER: ");
      Serial.println(calculate_unscaled_power_mW(leds, NUM_LEDS)/5/100);
    }
  }
}

void setup() {
  Bluetooth.begin("blooth");
  Serial.begin(115200);
  //FastLED.setDither(0);
  FastLED.addLeds<VIRTUAL_DRIVER,Pins,CLOCK_PIN, LATCH_PIN>(leds,NUM_LEDS_PER_STRIP);
  FastLED.setBrightness(25);
  xTaskCreatePinnedToCore(FastLEDshowTask, "FastLEDshowTask", 2000, NULL,2, &FastLEDshowTaskHandle, 0);
// now use FastLEDshowESP32() instead of fastled.show()
}

void loop() {
    basic();
    //BTproc();
}