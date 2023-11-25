#include "Arduino.h"
#include "HardwareSerial.h"

class Timer {
public:
  Timer(int timeStop) {
    _timeStop = timeStop;
  }
  void run() {
    if (start) {
      if (millis() - Time >= 1000) {
        i++;
        if (i >= _timeStop) {
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
  void stop() {
    start = false;
    i = 0;
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
  int _timeStop;
};