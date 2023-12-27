/*********
  Arduino daisy chain
  Ahmad Didik Setiyadi
*********/
#include "daisy_chain.h"

TaskHandle_t daisyTask;
 
void setup()
{
  Serial.begin(115200);
  xTaskCreatePinnedToCore(
      uartTask, /* Function to implement the task */
      "Task1", /* Name of the task */
      10000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      1,  /* Priority of the task */
      &daisyTask,  /* Task handle. */
      1); /* Core where the task should run */
}
 
void loop() {}