#include <Arduino.h>
#include "modbus.h"

void setup()
{
  initSystem();
}

void loop()
{
  systemLoop();
  delay(100);
}