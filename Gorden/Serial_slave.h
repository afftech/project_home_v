

class SerialSlave {
public:
  /* SerialSlave() {
    // SerialPort.begin(115200);
    // SerialPort.setTimeout(10);
  }*/
  void send(char control[], int data) {
    char convert[3] = "";
    itoa(data, convert, DEC);
    Serial.print(control);
    Serial.print(data);

    //Serial.print("\0");
    //Serial.print(control);
    //Serial.println(data);
  }
  bool getData;
  void Listner() {  // пример 55 00 00 02 00 02 01 01 9D 58
    if (Serial.available() > 0) {
      char key = Serial.read();
      if (String(key, BIN) != ("100000") && String(key, BIN) != ("1010")) {
        Serial.println(String(key, BIN));
      }
    }
  }
private:
  char message[21];
  void controlDevice(char key, int data) {
    switch (key) {
      case 'a':
        StationState = !StationState;
        break;
      default:
        break;
    }
  }
};