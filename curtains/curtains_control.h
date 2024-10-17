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
  SEND_DATA,
  WAIT_CHANGE,
};

//byte* command;
class CurtainsObj {
public:
  CurtainsObj(byte i) {  //номер/адрес двигателя
    command[2] = i;
  }
  void loop() {  //здесь гоняем время до следующей команды
                 /* if (state == PARSING_DATA) {
      PARSING(size_data);
      state = WAIT_CHANGE;
    }*/
    /*if (state == WAIT_CHANGE) {
      if (counter != Old_counter) {
      }
    }*/
  }
  int State() {
    bool status;
    if (state != WAIT_CHANGE) {
      status = 1;
    } else {
      Time_Next_Command = millis();
      status = 0;
    }
    return status;
  }
  void send_and_receiv() {
    switch (state) {
      case SEND_DATA:
        if (millis() - Time_Next_Command >= 30) {//30
          Time_Next_Command = millis();
          Time_Wait_Data = Time_Next_Command;
          sendDataToUART();
          state = WAIT_DATA;
        }
        break;
      case WAIT_DATA:
        if (millis() - Time_Wait_Data >= 60) {//60
          Time_Wait_Data = millis();
          size_data = available();
          state = PARSING_DATA;
        }
        break;
      case PARSING_DATA:
        PARSING(size_data);
        if (New_Command) {
          state = SEND_DATA;
          New_Command = 0;
          Time_Next_Command = millis();
          Serial.println("SEND_DATA2_ok");
        } else {
          state = WAIT_CHANGE;
        }
        break;
    }
  }
  void Stop() {
    if (state == WAIT_CHANGE) {
      state = SEND_DATA;
    } else {
      New_Command = 1;
    }
    Time_Next_Command = millis();
    state = SEND_DATA;
    command[3] = CONTROL;
    command[4] = STOP;
    //Serial.print(command[4], HEX);
  }
  void setterBlinds(byte level) {
    if (state == WAIT_CHANGE) {
      state = SEND_DATA;
    } else {
      New_Command = 1;
    }

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
  uint32_t counter;  //4 294 967 295
  uint32_t Time_Next_Command, Time_Wait_Data;
  int New_Command;
  byte state = WAIT_CHANGE;
  ////////////////////////////////////
  byte command[8] = { 0x55, 0x01, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00 };
  byte command1[8] = { 0x55, 0x01, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00 };

  int size_data;
  byte response[30] = {};
  //ModBus Command1;
  void sendDataToUART() {
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
    Serial.print("request: ");
    for (byte i = 0; i < len; i++) {
      Serial.print(" ");
      Serial.print(command[i], HEX);
      Serial2.write(command[i]);
    }
    Serial.println();
  }
  int available() {
    int size = 0;
    while (Serial2.available() > 0) {
      uint8_t buf;
      buf = Serial2.read();
      //Serial.print(test, HEX);
      response[size++] = buf;
    }
    if (size != 0) {
      return size;
    }
    return 0;
  }

  void PARSING(int size) {
    word crc = modbus_crc16(response, size - 2);
    if ((lowByte(crc) == response[size - 2]) && (highByte(crc) == response[size - 1])) {  //проверка сообщения
      Serial.print("response:");
      for (byte i = 0; i < size; i++) {
        Serial.print(" ");
        Serial.print(response[i], HEX);
      }
      Serial.println();
    }
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