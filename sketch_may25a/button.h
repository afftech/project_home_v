#include "HardwareSerial.h"
#include "Arduino.h"

class button {
public:
  button(char pin,int waiting_time) {
    _pin = pin;
    _waiting_time=waiting_time;
    pinMode(_pin, INPUT);
  }
  bool click() {

    int btnState = analogRead(_pin);
    if (btnState <= 20 && !_flag && time1(true)) {
      _flag = true;
      _tmr = millis();
      on = false;
      return true;
    }
    if (btnState <= 20 && _flag && time1(true)) {
      _tmr = millis();
      on = false;
      return true;
    }
    if (btnState >= 21 && _flag) {
      _flag = false;
      _tmr = millis();
      time1(false);
    }
    if (btnState >= 21) {
      Timer = millis();
      i = 0;
    }
    return false;
  }
private:
  bool on;
  char _pin;
  uint32_t _tmr;
  bool _flag;
  unsigned long Timer;
  int i;
  int _waiting_time;
  bool time1(bool v) {
    if (v) {
      if (millis() - Timer >= 1000) {
        i++;
        Timer = millis();
        Serial.println(i);
        if (i >= _waiting_time) {
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