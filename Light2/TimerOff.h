#include "Arduino.h"
#include "HardwareSerial.h"

class Timer {
public:
  void run() {
    if (start) {
      if (millis() - Time >= 1000) {
        i++;
        if (i >= DelayTimeS) {
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
    i = 0;
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
  int i;
};