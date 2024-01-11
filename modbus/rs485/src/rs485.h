#ifndef __RS485_H__
#define __RS485_H__
#include <Arduino.h>

#define rs485 Serial2
#define ACTIVATE_PIN 5
#define RX2_PIN 16
#define TX2_PIN 17
#define HEADER 255

typedef struct
{
  uint16_t sensor;
} data_t;

data_t data;
data_t dataRecv;

void systemInit(void);
void systemLoop(void);
void master(void);
void slave();
#endif // __RS485_H__