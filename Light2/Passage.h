#include "Arduino.h"
#include "HardwareSerial.h"
class Passage {
#include "TimerOff.h"
  Timer Light1T;
  
public:
  Passage(char pin) {
    _pin = pin;
    pinMode(pin, OUTPUT);
  }
  void run() {
    Light1T.run();
    if (Light1) {
      digitalWrite(_pin, 1);
    } else {
      if (Light1T.resp()) {
        digitalWrite(_pin, 0);
      }
    }
  }
  void On(bool i) {
    if (OldLight1T != i) {
      if (i) {
        Light1 = true;
      } else {
        Light1 = false;
        Light1T.on();
        OldLight1T = i;
      }
      OldLight1T = Light1;
    }
  }
private:
  bool Light1, OldLight1T;
  char _pin;
};