//#include "USBAPI.h"
/*#include <SoftwareSerial.h>
SoftwareSerial SerialPort(10, 11);  // RX, TX*/
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
  void Listner() {
    if (Serial2.available() > 0) {
      char key = Serial2.read();
      int data = Serial2.parseInt();
      if (key != ' ') {
        controlDevice(key, data);
      }
    }
  }
private:
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