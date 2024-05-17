#include "Print.h"

#define INCOMING_BYTES_COUNT 100

// Functions code
#define READ 0x01
#define WRITE 0x02
#define CONTROL 0x03

// Control commands
#define UP 0x01
#define DOWN 0x02
#define STOP 0x03

#define PERCENTAGE 0x04

enum States {
  WAIT_DATA,
  PARSING_DATA,
  SEND_DATA
};

//byte* command;
class CurtainsObj {
public:
  CurtainsObj(byte i) {  //номер/адрес двигателя
    command[2] = i;
  }
  void loop() {
    if (state == SEND_DATA) {
      sendDataToUART();
      //Serial.println("SEND_DATA");
      state = WAIT_DATA;
    }
  }
  void Stop() {
    state = SEND_DATA;
    command[3] = CONTROL;
    command[4] = STOP;
    //Serial.print(command[4], HEX);
  }
  void setterBlinds(byte level) {
    state = SEND_DATA;
    command[3] = CONTROL;
    if (level == 0) {
      command[4] = DOWN;
    } else if (level == 99 || level == 255) {
      command[4] = UP;
    } else {
      command[4] = PERCENTAGE;
      command[5] = level;
    }
    //Serial.print(command[4], HEX);
  }
private:
  byte state = WAIT_DATA;
  ////////////////////////////////////
  byte command[8] = { 0x55, 0x01, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00 };
  //ModBus Command1;
  void
  sendDataToUART() {
    byte len;
    if (command[4] == PERCENTAGE || command[3] == READ) {
      word crc = modbus_crc16(command, 6);
      command[6] = lowByte(crc);
      command[7] = highByte(crc);
      len = 8;
    } else {
      word crc = modbus_crc16(command, 5);
      command[5] = lowByte(crc);
      command[6] = highByte(crc);
      len = 7;
    }
    for (byte i = 0; i < len; i++) {
      Serial.print(command[i], HEX);
      Serial2.write(command[i]);
    }
    Serial.println();
  }
  word modbus_crc16(byte* buf, int len) {
    word crc = 0xFFFF;

    for (int pos = 0; pos < len; pos++) {
      crc ^= (word)buf[pos];  // XOR byte into least sig. byte of crc

      for (int i = 8; i != 0; i--) {  // Loop over each bit
        if ((crc & 0x0001) != 0) {    // If the LSB is set
          crc >>= 1;                  // Shift right and XOR 0xA001
          crc ^= 0xA001;
        } else        // Else LSB is not set
          crc >>= 1;  // Just shift right
      }
    }
    // Note, this number has low and high bytes swapped, so use it accordingly (or swap bytes)
    return crc;
  }
};