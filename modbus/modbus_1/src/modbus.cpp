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

bool compareStruct(data_t structA, data_t structB)
{
  bool isSame = true;
  for(byte i=0; i<5; i++)
  {
    isSame &= structA.sensor[i] == structB.sensor[i];
    if (!isSame) return false;
  }
  return isSame;
}

void sendData(data_t data)
{
  digitalWrite(ACTIVATE_PIN, HIGH);
  Serial2.write(HEADER);
  Serial2.write((byte*)&data, sizeof data);
  delayMicroseconds(120);
  // digitalWrite(ACTIVATE_PIN, LOW);
}
void initSystem(void)
{
  pinMode(ACTIVATE_PIN, OUTPUT);
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RX2_PIN, TX2_PIN);
}
void systemLoop(void)
{
  static data_t sensorData;
  static data_t sensorDataRecv;
  static uint16_t counter = 0;
  counter++;

  if (counter > 99) counter = 1;
  for(byte i=0; i<5; i++)
  {
    sensorData.sensor[i] = i*100 + counter;
    sensorDataRecv.sensor[i] = i*100 + counter;
    Serial.print(sensorDataRecv.sensor[i]);
    Serial.print(" | ");
  }
  Serial.print(" ||| ");

  sendData(sensorData);
  delay(1);

  // recv data
  digitalWrite(ACTIVATE_PIN, LOW);
  if(Serial2.available())
  {
    byte header = Serial2.read();
    if (header == HEADER)
    {
      Serial2.readBytes((byte*)&sensorDataRecv, sizeof sensorDataRecv);
      while (Serial2.available()) char chunk = Serial2.read();
      for(byte i=0; i<5; i++)
      {
        Serial.print(sensorDataRecv.sensor[i]);
        Serial.print(" | ");
      }
      Serial.println();
    }
  }
}