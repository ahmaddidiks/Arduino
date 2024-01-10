#include <Arduino.h>

#define ACTIVATE_PIN 4
#define RX2_PIN 16
#define TX2_PIN 17

void setup(void)
{
  pinMode(ACTIVATE_PIN, OUTPUT);
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RX2_PIN, TX2_PIN);
}

void loop()
{
  digitalWrite(ACTIVATE_PIN, LOW);
  Serial.println("Test");
  Serial2.println("Test");
  delay(1000);
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