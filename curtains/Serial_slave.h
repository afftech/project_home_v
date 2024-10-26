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
    /*Serial.print(control);
    Serial.print(data);*/
  }
  bool getData;
  void Listner() {
    int a = available();
    if (a == 4) {
      char key1 = response[0];
      int key2 = digit_to_int(response[1]);
      int key3 = response[2];
      controlDevice(key1, key2, key3, 0);
    } else if (a == 5) {
      char key1 = response[0];
      int key2 = digit_to_int(response[1]);
      int key3 = response[2];
      int value = digit_to_int(response[3]);
      Serial.println(value);
      controlDevice(key1, key2, key3, value);
    }
  }
  int available() {
    int size = 0;
    if (millis() - T >= 100) {
      T = millis();
      while (Serial.available() > 0) {
        char buf;
        buf = Serial.read();
        //Serial.println(buf);
        response[size++] = buf;
      }
    }
    if (size != 0) {
      //Serial.println(size);
      return size;
    }
    return 0;
  }
private:
  uint32_t T;
  byte response[30] = {};
  void controlDevice(char key1, int key2, char key3, int value) {  //a12a22a32a42a52 //a13a23a33a43a53
    switch (key1) {                                                // s - stop u - open d - закр b - изм направл
      case 'a': //a2u
        Curtains.send(1, key3, 0);
        Curtains.send(2, key3, 0);
        Curtains.send(3, key3, 0);
        Curtains.send(4, key3, 0);
        Curtains.send(5, key3, 0);
      case 'b':  //c2a
        //Serial.println("Err2");
        Curtains.send(key2, key3, 0);
        break;
      case 'c':  //с_N_b_v c2b1 c2a
        Curtains.send(key2, key3, value);
        break;
      default:
        break;
    }
  }
  int digit_to_int(char d) {
    char str[2];
    str[0] = d;
    str[1] = '\0';
    return (int)strtol(str, NULL, 10);
  }
};
