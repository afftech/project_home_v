#include "HardwareSerial.h"
#include "Arduino.h"

class onPrevention {
public:
  onPrevention(int pin_Open1, int pin_Open2, int pin_Close1, int pin_Close2, int waiting_time) {
    this->waiting_time = waiting_time;
    this->pin_Open1 = pin_Open1;
    this->pin_Close1 = pin_Close1;
    this->pin_Open2 = pin_Open2;
    this->pin_Close2 = pin_Close2;
  }
  bool run() {
    if (on) {
      if (!close) {
        digitalWrite(pin_Close1, true);
        digitalWrite(pin_Close2, true);
        if (time1(1)) {
          close = true;
          digitalWrite(pin_Close1, false);
          digitalWrite(pin_Close2, false);
        }
      }
      if (close && !open) {
        digitalWrite(pin_Open2, true);
        digitalWrite(pin_Open1, true);
        if (time1(1)) {
          open = true;
          on = false;
          digitalWrite(pin_Open2, false);
          digitalWrite(pin_Open1, false);
        }
      }
    }
  }

  void start() {
    on = true;
    Timer = millis();
  }
private:
  int pin_Open1, pin_Open2, pin_Close1, pin_Close2;
  bool on, open, close;
  unsigned long Timer;
  int i;
  int waiting_time;
  bool time1(bool v) {
    if (v) {
      if (millis() - Timer >= 1000) {
        i++;
        Timer = millis();
        Serial.println(i);
        if (i >= waiting_time) {
          i = 0;
          return true;
        } else {
          return false;
        }
      }
      return false;
    } else {
      i = 0;
      return false;
    }
  }
};