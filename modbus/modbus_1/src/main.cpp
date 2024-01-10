#include <Arduino.h>

#define ACTIVATE_PIN 4
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
  static uint16_t counter = 0;
  counter++;
  if (counter > 99) counter = 1;
  for(byte i=0; i<5; i++)
  {
    sensorData.sensor[i] = i*100 + counter;
    Serial.print(sensorData.sensor[i]);
    Serial.print(" | ");
  }
  Serial.println();
  Serial2.write(HEADER);
  Serial2.write((byte*)&sensorData, sizeof sensorData);
  delay(100);
}



////////////////////////////////////

// #define RX2_PIN 16
// #define TX2_PIN 17

// void setup(void)
// {
//   pinMode(5, OUTPUT);
//   pinMode(18, OUTPUT);
//   Serial.begin(9600);
//   Serial2.begin(9600, SERIAL_8N1, RX2_PIN, TX2_PIN);
// }

// void loop()
// {
//   digitalWrite(5, LOW);
//   pinMode(18, OUTPUT);
//   if (Serial2.available())
//   {
//     char x = Serial.read();
//     Serial.print(x);
//     Serial.print(" ");
//   }
//   delay(10);
// }