#include "Arduino.h"
#include "HardwareSerial.h"

class Loggia {
public:
  void run() {
    if (OnLoggiaLight) {
      digitalWrite(LoggiaLight, 1);
    } else {
      digitalWrite(LoggiaLight, 0);
    }
    if (!StateLoggiaLight) {
      TimeLoggiaLight = millis();
    }
  }
  void clickLoggia() {
    if (millis() - TimeLoggiaLight <= 3000) {
      if (StateLoggiaLight == 0) {
        StateLoggiaLight = 1;
        OnLoggiaLight = true;
      } else {
        StateLoggiaLight = 0;
        OnLoggiaLight = false;
      }
    } else {
      StateLoggiaLight = 0;
      OnLoggiaLight = false;
    }
    TimeLoggiaLight = millis();
  }
  void Off_or_ONRoom() {
    OnLoggiaLight = !OnLoggiaLight;  //4
    StateLoggiaLight = 0;
  }
private:
  bool OnLoggiaLight;
  int StateLoggiaLight;
  long TimeLoggiaLight;
};