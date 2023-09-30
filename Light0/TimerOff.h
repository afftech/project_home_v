#include "Arduino.h"
#include "HardwareSerial.h"

class Timer {
public:
  Timer(int DelayTimeS) {
    _DelayTimeS = DelayTimeS;
  }
  void run() {
    if (start) {
      if (millis() - Time >= 60000) {
        i++;
        //Serial.println(i);
        if (i >= _DelayTimeS) {
          start = false;
          i = 0;
        } else {
          start = true;
          Time = millis();
        }
      }
    }
  }
  void on() {
    start = true;
    Time = millis();
  }
  bool resp() {
    if (start) {
      return false;
    } else {
      return true;
    }
  }
private:
  long Time;
  bool start;
  int i, _DelayTimeS;
};