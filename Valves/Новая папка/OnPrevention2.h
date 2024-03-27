#include "HardwareSerial.h"
#include "Arduino.h"

class onPrevention2 {
public:
  onPrevention2(int waiting_time, int* pin_Open, int* pin_Close) {
    _waiting_time = waiting_time;
    _pin_Open = pin_Open;
    _pin_Close = pin_Close;
  }
  bool run() {
    Serial.println(_pin_Close);
    if (on) {
      if (!open) {
        Serial.println(_pin_Open);
        digitalWrite(_pin_Open, true);
        if (time1()) {
          open = true;
          digitalWrite(_pin_Open, false);
        }
      }
      if (open) {  //теперь закрываем
        //Serial.println("Close");
        digitalWrite(_pin_Close, true);
        if (time1()) {
          open = false;
          on = false;
          digitalWrite(_pin_Close, false);
        }
      }
    }
  }
  void start() {
    on = true;
    Timer = millis();
  }
private:
  int _pin_Open;
  int _pin_Close;
  bool on, open;
  unsigned long Timer;
  int i;
  int _waiting_time;
  bool time1() {
    if (millis() - Timer >= 1000) {
      i++;
      Timer = millis();
      //Serial.println(i);
      if (i >= _waiting_time) {
        i = 0;
        return true;
      } else {
        return false;
      }
    }
    return false;
  }
};