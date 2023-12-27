#ifndef __DAISY_CHAIN_H__
#define __DAISY_CHAIN_H__

#include <Arduino.h>

#define daisy Serial2

String txData;
String rxData;

typedef struct
{
  uint16_t posTarget[6];
  uint16_t sensorFeedback[6];
} Data_t;

Data_t data;

void uartTask(void *pvParameters)
{
  daisy.begin(115200);
  String buffer;
  char chunk;
  byte marker;

  
  uint16_t counter = 0;

  while (true)
  {
    #if BOARD_ID==0
    counter++;
    if (counter == 99) counter = 0;

    for (byte i = 0; i < 6; i++) 
    {
      data.posTarget[i] = i*100 + counter;
      Serial.print(data.posTarget[i]);
      Serial.print(" | ");
    }
    Serial.println("");
    daisy.write(255);
    daisy.write( (byte*)&data, sizeof data );
    delay(50);

    #else
    marker = 0;
    while (daisy.available())
    {
      marker = daisy.read();
      if (marker = 255)
      {
        daisy.readBytes((byte *)&data, sizeof data); // grab the data
        delay(1);

        data.sensorFeedback[BOARD_ID-1] = random(255); // update data
        daisy.write(255);
        daisy.write((byte*)&data, sizeof data);
        
        // show the data
        for (byte i = 0; i < 6; i++) 
        {
          Serial.print(data.posTarget[i]);
          Serial.print(" | ");
        }
        Serial.println("");
      }
      
      if (daisy.available()) chunk = daisy.read(); // just for clearing buffer
    }
    delay(10);
    #endif
  }
}

#endif // __DAISY_CHAIN_H__