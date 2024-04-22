#include "HardwareSerial.h"
#include "Arduino.h"

class onPrevention2 {
public:
  onPrevention2() {
  }
protected:
  int pin_Open, pin_Close;
  int waiting_time;
  void run() {
    if (on) {
      if (!open) {
        digitalWrite(pin_Open, true);
        /*Serial.print("Open:");
        Serial.println(pin_Open);*/
        if (time1()) {
          open = true;
          digitalWrite(pin_Open, false);
        }
      }
      if (open) {  //теперь закрываем
        /*Serial.print("Close:");
        Serial.println(pin_Close);
        Serial.println("Close");*/
        digitalWrite(pin_Close, true);


        if (time1()) {
          open = false;
          on = false;
          digitalWrite(pin_Close, false);
        }
      }
    }
  }
  void start() {
    on = true;
    Timer = millis();
  }
private:
  bool on, open;
  unsigned long Timer;
  int i;
  bool time1() {
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
  }
};