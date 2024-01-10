#ifndef __MODBUS_H__
#define __MODBUS_H__

#include <Arduino.h>

#define ACTIVATE_PIN 5
#define RX2_PIN 16
#define TX2_PIN 17
#define HEADER 255

typedef struct
{
  uint16_t sensor[5];
} data_t;

void modbusTask(void *pvParameters);
bool compareStruct(data_t structA, data_t structB);
void sendData(data_t data);
void initSystem(void);
void systemLoop(void);

#endif // __MODBUS_H__