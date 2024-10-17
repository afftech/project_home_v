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
  }
  bool getData;
  void Listner() {
    if (Serial.available() > 0) {
      char key = Serial.read();
      int data = Serial.parseInt();
      if (key != ' ' || key != '\n') {
        controlDevice(key, data);
      }
    }
  }
private:
  void controlDevice(char key1, int data) {  //a12a22a32a42a52 //a13a23a33a43a53
    int key2 = data / 10;
    int key3 = data - (key2 * 10);
    char message;
    if (key3 == 1) {
      message = 's';
    } else if (key3 == 2) {
      message = 'u';
    } else if (key3 == 3) {
      message = 'd';
    } else {
      //message = 'e';
    }
    switch (key1) {
      case 'a':
        Curtains.send(key2, message);
      case 'b':
        Curtains.send(1, message);
        Curtains.send(2, message);
        Curtains.send(3, message);
        Curtains.send(4, message);
        Curtains.send(5, message);
        break;
      case 'c':  //вкл откл ручн реж

        break;
      default:
        break;
    }
  }
};