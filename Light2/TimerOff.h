#include "Arduino.h"
#include "HardwareSerial.h"

class Timer {
public:
  void run() {
    if (start) {
      if (millis() - Time >= 1000) {
        i++;
        if (i >= 10) {
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
  int i;
};