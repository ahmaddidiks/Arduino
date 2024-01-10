#include <Arduino.h>

#define ACTIVATE_PIN 5
#define RX2_PIN 16
#define TX2_PIN 17
#define HEADER 255

typedef struct
{
  uint16_t sensor[5];
} Data_t;

Data_t sensorData;

void setup(void)
{
  pinMode(ACTIVATE_PIN, OUTPUT);
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RX2_PIN, TX2_PIN);
}

void loop()
{
  digitalWrite(ACTIVATE_PIN, LOW);
  if (Serial2.available())
  {
    byte header = Serial2.read();
    if (header==HEADER)
    {
       Serial2.readBytes((byte*)&sensorData, sizeof sensorData);

      for(byte i=0; i<5; i++)
      {
        Serial.print(sensorData.sensor[i]);
        Serial.print(" | ");
      }
      Serial.println();
    }
    while (Serial2.available()) char chunk = Serial2.read();

    delay(1);
    digitalWrite(ACTIVATE_PIN, HIGH);
    Serial2.write(HEADER);
    Serial2.write((byte*)&sensorData, sizeof sensorData);
    delayMicroseconds(120);
  }
  delay(10);
}