
class SerialSlave {
public:
  void send(char control[], int data) {
    char convert[3] = "";
    itoa(data, convert, DEC);
    Serial.print(control);
    Serial.print(data);
  }
  bool getData;
  void Listner() {
    if (Serial.available() > 0) {
      char key = Serial.read();
      int data = Serial.parseInt();
      if (key != ' ') {
        controlDevice(key, data);
      }
    }
  }
private:
  void controlDevice(char key, int data) {
    switch (key) {
      case 'a':
        if (data == 1) {
          digitalWrite(D9, 0);
        } else if (data == 2) {
          digitalWrite(D9, 1);
        }
        break;
      case 'b':
        if (data == 1) {
          DOWN_Start();
          break;
          default:
            break;
        }
    }
    void install(byte Number) {
      Serial.println();
      //command[6] = Number;
      Serial.begin(9600);
      Serial2.begin(9600);
      byte len = 10;
      word crc = modbus_crc16(command, 8);
      command[8] = lowByte(crc);
      command[9] = highByte(crc);
      // put your setup code here, to run once:
      Serial.print("OUTPUT:");
      for (byte i = 0; i < len; i++) {
        Serial.print(command[i], HEX);
        Serial2.write(command[i]);
      }
      Serial.println();
    }
    void DOWN_Start() {
      Serial.println();
      state = !state;
      if (state) {
        command[4] = UP;
      } else {
        command[4] = DOWN;
      }
      //command[6] = Number;
      Serial.begin(9600);
      Serial2.begin(9600);
      byte len = 8;
      word crc = modbus_crc16(command1, 6);
      command1[6] = lowByte(crc);
      command1[7] = highByte(crc);
      // put your setup code here, to run once:
      Serial.print("OUTPUT:");
      for (byte i = 0; i < len; i++) {
        Serial.println();
        Serial.print(command1[i], HEX);
        Serial2.write(command1[i]);
      }
      Serial.println();
    }
  };