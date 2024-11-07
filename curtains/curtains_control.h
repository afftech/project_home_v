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
#define PROCENT 0x02
#define SET_direction 0x03
#define PERCENTAGE 0x04
//4 и 5 наоборот
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
    command2_AutoReq[0][2] = i;
    Number = i;
  }
  void loop() {  //здесь гоняем время до следующей команды
    if (state == WAIT_CHANGE) {
      if (!Silent) {
        AutoRequest();
      }
    }
    message();
  }
  void install_Mod(bool data) {
    Silent = data;
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
        for (int i = 0; i < 3; i++) {
          if (waiting_send[i]) {
            state = SEND_DATA;  //если были получены команды
            point = i;
            break;
          }
        }
        if (millis() - Time_Next_Command >= 30) {  //30
          Time_Next_Command = millis();
          Time_Wait_Data = Time_Next_Command;
          if (waiting_send[point]) {
            if (point == 0) {
              sendDataToUART(true);  //auto
            } else {
              sendDataToUART(false);  //manual
            }
          }
          state = WAIT_DATA;
        }
        break;
      case WAIT_DATA:
        if (millis() - Time_Wait_Data >= 60) {  //60
          Time_Wait_Data = millis();
          size_data = available();
          state = PARSING_DATA;
        }
        break;
      case PARSING_DATA:
        if (point == 0) {
          PARSING(size_data, true);  // запись в рег
          waiting_send[point] = 0;
          WAIT_AutoReq = millis();
        } else if (point == 1) {
          PARSING(size_data, false);
          waiting_send[point] = 0;
        } else if (point == 2) {
          PARSING(size_data, false);
          waiting_send[point] = 0;
        }
        for (int i = 0; i < 3; i++) {
          if (waiting_send[i]) {
            state = SEND_DATA;  //если были получены команды
            break;
          } else {
            state = WAIT_CHANGE;
          }
        }
        point++;
        if (point == 3) {
          point = 0;
        }
        break;
    }
  }
  void Stop() {
    check_state();
    //Serial.println("St");
    state = SEND_DATA;
    command[3] = CONTROL;
    command[4] = STOP;
    //Serial.print(command[4], HEX);
    //go = 0;
  }
  void Procent() {
    check_state();
    state = SEND_DATA;
    command[3] = WRITE;
    command[4] = PROCENT;
    command[5] = READ;
  }
  void set_direction(bool direction) {
    check_state();
    command[3] = WRITE;
    command[4] = SET_direction;
    command[5] = 0x01;
    command[6] = 0x01;
    if (direction) {
      command[6] = 0x01;
    } else {
      command[6] = 0x00;
    }
  }
  void AutoRequest() {
    if (millis() - WAIT_AutoReq >= 400) {
      state = SEND_DATA;
      waiting_send[0] = 1;
    }
  }
  void setterBlinds(byte level) {
    if (!Silent) {
      if (go) {
        Stop();
      } else {
        check_state();
        command[3] = CONTROL;
        go = 1;
        if (level == 0) {
          command[4] = DOWN;
        } else if (level == 99 || level == 255) {
          command[4] = UP;
        } else {
          command[4] = PERCENTAGE;
          command[5] = level;
        }
      }
    } else {
      installM();
    }
  }
  void installM() {
    check_state();
    command1[7] = Number;
    byte len = 10;
    word crc = modbus_crc16(command1, 8);
    command1[8] = lowByte(crc);
    command1[9] = highByte(crc);
    // put your setup code here, to run once:
    Serial.print("Install:");
    for (byte i = 0; i < len; i++) {
      Serial2.write(command1[i]);
    }
    for (byte i = 0; i < len; i++) {
      Serial.print(" ");
      Serial.print(command1[i], HEX);
    }
    Serial.println();
  }
private:
  int point;
  bool go = 0, OldGo;
  uint32_t Time_Next_Command, Time_Wait_Data, WAIT_AutoReq;
  int Change_Command = 0, Number, Silent = 0;
  byte state = WAIT_CHANGE;
  ////////////////////////////////////
  //manual manual-new auto
  byte waiting_send[3] = { 0, 0, 0 };
  byte command[8] = { 0x55, 0x01, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00 };
  byte command1[10] = { 0x55, 0x00, 0x00, 0x02, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00 };
  byte command2_AutoReq[1][8] = { { 0x55, 0x01, 0xfe, 0x01, 0x05, 0x01, 0x00, 0x00 } };  //1 запрос сост движения
  byte command3[8] = { 0x55, 0x00, 0x00, 0x01, 0x02, 0x01, 0x00, 0x00 };
  int size_data;
  byte response[30] = {};

  //ModBus Command1;
  void sendDataToUART(int Auto) {
    byte len;
    byte buf_arr[8];
    if (Auto) {
      len = 8;
      for (int row = 0; row < waiting_send[0]; row++) {
        for (int col = 0; col < len; col++) {
          buf_arr[col] = command2_AutoReq[row][col];
        }
      }
      word crc = modbus_crc16(buf_arr, 6);
      buf_arr[6] = lowByte(crc);
      buf_arr[7] = highByte(crc);
    } else {
      if (command[4] == PERCENTAGE || command[3] == READ) {
        word crc = modbus_crc16(command, 6);
        command[6] = lowByte(crc);
        command[7] = highByte(crc);
        len = 8;
      } else if (command[3] == WRITE) {
        word crc = modbus_crc16(command, 7);
        command[7] = lowByte(crc);
        command[8] = highByte(crc);
        len = 9;
      } else {
        word crc = modbus_crc16(command, 5);
        command[5] = lowByte(crc);
        command[6] = highByte(crc);
        len = 7;
      }
    }
    //Serial.print("request: ");
    for (byte i = 0; i < len; i++) {
      if (Auto) {
        //Serial.print(" ");
        //Serial.print(buf_arr[i], HEX);
        Serial2.write(buf_arr[i]);
      } else {
        // Serial.print(" ");
        // Serial.print(command[i], HEX);
        Serial2.write(command[i]);
      }
    }
    //Serial.println();
  }
  int available() {
    int size = 0;
    while (Serial2.available() > 0) {
      uint8_t buf;
      buf = Serial2.read();
      //Serial.print(buf, HEX);
      response[size++] = buf;
    }
    if (size != 0) {
      return size;
    }
    return 0;
  }

  void PARSING(int size, bool save) {
    word crc = modbus_crc16(response, size - 2);
    if ((lowByte(crc) == response[size - 2]) && (highByte(crc) == response[size - 1])) {  //проверка сообщения
      if (save) {
        if (response[5]) {
          go = 1;
        } else {
          go = 0;
        }
      } else {
        Serial.print("response:");
        for (byte i = 0; i < size; i++) {
          Serial.print(" ");
          Serial.print(response[i], HEX);
        }
        Serial.println();
      }
    }
  }
  word
  modbus_crc16(byte* buf, int len) {
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
  void check_state() {
    Serial.print("It was:");
    if (state == WAIT_CHANGE) {
      state = SEND_DATA;  //2
      waiting_send[1] = 1;
      Serial.println("WAIT_CHANGE");
    } else {
      if (state == PARSING_DATA) {
        Serial.println("PARSING_DATA");
      } else if (state == WAIT_DATA) {
        Serial.println("WAIT_DATA");
      } else if (state == SEND_DATA) {
        Serial.println("SEND_DATA");
      }
      waiting_send[2] = 1;
      /*if (point == 1) {
        waiting_send[2] = 1;
      } else if (point == 2) {
        waiting_send[1] = 1;
      }*/
    }
    Time_Next_Command = millis();
  }
  void message() {
    if (go != OldGo) {
      OldGo = go;
      Serial.print(Number);
      Serial.print(" ");
      if (go) {
        Serial.print("Go ");
      } else {
        Serial.print("Stop ");
      }
      Serial.println();
    }
  }
};