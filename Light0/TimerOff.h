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
        if (i >= _DelayTimeS) {
          start = false;
          respOn = true;
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
    if (respOn) {
      respOn = false;
      return true;
    }
    return false;
  }
  void stop() {
    start = false;
    i = 0;
  }
private:
  long Time;
  bool start, respOn;
  int i, _DelayTimeS;
};