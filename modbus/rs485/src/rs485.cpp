#include "rs485.h"

void systemInit(void)
{
  Serial.begin(9600); // for debugging
  rs485.begin(9600, SERIAL_8N1, RX2_PIN, TX2_PIN);
  pinMode(ACTIVATE_PIN, OUTPUT);
}
void systemLoop(void)
{
  #if BOARD_ID == 0 // master
    master();
  #else
    slave();
  #endif
}

void master(void)
{
  byte header;
  byte boardID;
  digitalWrite(ACTIVATE_PIN, LOW); // recv mode

  if (rs485.available())
  {
    header = rs485.read();

    if (header == HEADER)
    {
      boardID = rs485.read();
      rs485.readBytes((byte*)&dataRecv, sizeof dataRecv);
      while (rs485.available()) char chunk = rs485.read(); // rm the buffer
    
      Serial.print("boardID: ");
      Serial.print(boardID);
      Serial.print(" | data: ");
      Serial.println(dataRecv.sensor);
    }
  }
  delay(1);
}

void slave()
{
  byte header;
  byte boardID;
  bool needSend  = false;
  digitalWrite(ACTIVATE_PIN, LOW); // recv mode

  if (rs485.available())
  {
    header = rs485.read();
    if (header == HEADER)
    {
      boardID = rs485.read();
      rs485.readBytes((byte*)&data, sizeof data);
      while (rs485.available()) char chunk = rs485.read(); // rm the buffer

      needSend =  (BOARD_ID == 1 && boardID==DEVICES_COUNT) ||
                  (BOARD_ID == boardID+1);
      if (needSend)
      {
        delay(1);
        digitalWrite(ACTIVATE_PIN, HIGH); // write mode
        rs485.write(HEADER);
        rs485.write(BOARD_ID);
        rs485.write((byte*)&data, sizeof data);
      }
    }
  }
  delay(1);
}