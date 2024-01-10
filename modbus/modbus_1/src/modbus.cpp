#include "modbus.h"

void modbusTask(void *pvParameters)
{
  Serial.begin(9600);

  for(;;)
  {
    if (Serial.available()) 
    {
      while (Serial.available()) char x = Serial.read();
      // Serial.write(6);
      Serial.write(5); // address

      Serial.write(5); // function
      
      Serial.write(10); // data
      
      Serial.write(2); // crc
      Serial.write(5); // crc
    }
  }
}
