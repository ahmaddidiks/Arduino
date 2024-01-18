/**
 * Modbus slave example 2:
 * The purpose of this example is to link the Arduino digital and analog
 * pins to an external device.
 *
 * Recommended Modbus Master: QModbus
 * http://qmodbus.sourceforge.net/
 *
 * Translated to Spanish by LuxARTS
 */

// Include the Modbus protocol library
#include <ModbusRtu.h>
#define ID   1

// Create an instance
Modbus slave(ID, Serial2, 5); // Node ID. 0 for master, 1-247 for slave
                              // Serial port (0 = TX: 1 - RX: 0)
                              // Serial protocol. 0 for RS-232 + USB (default), any pin greater than 1 for RS-485
boolean led;
int8_t state = 0;
unsigned long tempus;

uint16_t au16data[9]; // Table of registers to be shared over the network


/*********************************************************
 Program Configuration
 *********************************************************/
void setup() {

  Serial.begin(9600); // Open communication as a slave
  Serial2.begin( 9600, SERIAL_8N1, 16, 17 ); // baud-rate at 19200
  slave.start();
  tempus = millis() + 100; // Save current time + 100ms
  digitalWrite(13, HIGH); // Turn on the LED on pin 13 (on the board)
}

/*********************************************************
 Program Start
 *********************************************************/
void loop() {
  // Check the input buffer
  state = slave.poll(au16data, 1); // Parameters: Table of registers for data exchange
                                    //             Size of the register table
                                    // Returns 0 if there is no data request
                                    // Returns 1 to 4 if there was a communication error
                                    // Returns more than 4 if the request was processed correctly
  Serial.println(au16data[0]);

  // if (state > 4) { // If it is greater than 4 = the request was correct
  //   tempus = millis() + 50; // Current time + 50ms
  //   digitalWrite(13, HIGH); // Turn on the LED
  // }
  // if (millis() > tempus) digitalWrite(13, LOW); // Turn off the LED 50ms later

  // // Update Arduino pins with Modbus table
  // io_poll();
}