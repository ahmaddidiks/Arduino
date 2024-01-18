#include <Arduino.h>
#include <ModbusMaster.h>

ModbusMaster node;

void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, 16, 17);
  node.begin(10, Serial2);
}

void loop()
{
  static uint32_t i;
  uint8_t j, result;
  uint16_t data;
  
  i++;

  // set word 0 of TX buffer to least-significant word of counter (bits 15..0)
  node.setTransmitBuffer(0, lowWord(i));
  
  // set word 1 of TX buffer to most-significant word of counter (bits 31..16)
  node.setTransmitBuffer(1, highWord(i));

  result = node.readInputRegisters(0, 1);
  // do something with data if read is successful
  if (result == node.ku8MBSuccess)
  {
    data = node.getResponseBuffer(0);
    Serial.printf("input: %d |", data);
  }

  result = node.readHoldingRegisters(0, 1);
  // do something with data if read is successful
  if (result == node.ku8MBSuccess)
  {
    data = node.getResponseBuffer(0);
    Serial.printf(" | holding 1: %d", data);
  }

  //  result = node.readHoldingRegisters(3, 1);
  // // do something with data if read is successful
  // if (result == node.ku8MBSuccess)
  // {
  //   data = node.getResponseBuffer(0);
  //   Serial.printf(" | holding 3: %d", data);
  // }

  result = node.readDiscreteInputs(0, 1);
  // do something with data if read is successful
  if (result == node.ku8MBSuccess)
  {
    data = node.getResponseBuffer(0);
    Serial.printf(" | status: %d\n", data);
  }
}