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
    i = 0;
  }
  bool resp() {
    if (start) {
      return false;
    } else {
      return true;
    }
  }
  void stop() {
    start = false;
    i = 0;
  }
private:
  long Time;
  bool start;
  int i, _DelayTimeS;
};