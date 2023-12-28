#ifndef __SERIAL_H__
#define __SERIAL_H__

#include <Arduino.h>

#define HEADER 255

typedef struct 
{
  uint16_t posTarget[6];
  float sensorFeedback[6];
} Data_t;

void sendDataContinous(void)
{
  Data_t data;

  for (uint8_t i=0; i<100; i++)
  {
    for (uint8_t j=0; j<6; j++)
    {
      data.posTarget[j] = j*100 + i;
      data.sensorFeedback[j] = j*100 + i;
    }

    Serial.write(HEADER);
    Serial.write((byte*)&data, sizeof data);
    delay(100);
  }
}

void receiveContinous(void)
{
  Data_t recvData;
  if (Serial.available())
  {
    uint8_t header = Serial.read();

    if (header == HEADER) Serial.readBytes((byte*)&recvData, sizeof recvData); // read data
    while (Serial.available()) char chunk = Serial.read(); // clean the buffer
    delay(1); // give some time to mcu
    Serial.write(HEADER);
    delay(1); // give some time to mcu
    Serial.write((byte*)&recvData, sizeof recvData); // send back the data
  }
  delay(10);
}

void uartTask(void *pvParameters)
{
  Serial.begin(115200);
  while (true)
  {
    sendDataContinous();
    // receiveContinous();
  }
}

#endif // __SERIAL_H__