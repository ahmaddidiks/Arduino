#ifndef __DAISY_CHAIN_H__
#define __DAISY_CHAIN_H__

#include <Arduino.h>

#define daisy Serial2

String txData;
String rxData;

void uartTask(void *pvParameters)
{
  daisy.begin(115200);
  String buffer;
  char chunk;
  
  uint16_t counter = 0;

  while (true)
  {
    #if BOARD_ID==0
    counter++;
    txData = String(counter);
    daisy.println(txData);
    Serial.println(txData);
    delay(1000);

    #else
    while (daisy.available())
    {
      buffer = daisy.readString();
      if (daisy.available()) chunk = daisy.read(); // just for clearing buffer

      rxData = buffer;
      txData = rxData;
      
      delay(1);
      daisy.println(txData);
      Serial.println(txData);
    }
    delay(10);
    #endif
  }
}

#endif // __DAISY_CHAIN_H__