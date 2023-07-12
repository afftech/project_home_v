#include "HardwareSerial.h"

class Fun {
public:
  Fun(int pinSpeed1, int pinSpeed2, int pinSpeed3, int pinSpeed4, int Time1, int Time2) {  //если есть свет это Time1 = 5, если нет Time2 =10
    _pinSpeed1 = pinSpeed1;
    _pinSpeed2 - pinSpeed2;
    _pinSpeed3 = pinSpeed3;
    _pinSpeed4 = pinSpeed4;
    _Time1 = Time1;
    _Time2 = Time2;
    pinMode(pinSpeed1, OUTPUT);
    pinMode(pinSpeed2, OUTPUT);
    pinMode(pinSpeed3, OUTPUT);
    pinMode(pinSpeed4, OUTPUT);
  }
  int Speed(int speed) {
    bool light;
    Serial.println(speed);
    Serial.println(OldSpeed);
    if (speed != OldSpeed) {
      digitalWrite(_pinSpeed1, false);
      digitalWrite(_pinSpeed2, false);
      digitalWrite(_pinSpeed3, false);
      digitalWrite(_pinSpeed4, false);
      Timer1 = millis();
    }
    if (speed != 0) {  //сбрасываем таймер
      i = 0;
    }
    if (speed == 1) {
      digitalWrite(_pinSpeed1, true);
      OldSpeed = speed;
      return speed;
    } else if (speed == 2) {
      digitalWrite(_pinSpeed2, true);
      OldSpeed = speed;
      return speed;
    } else if (speed == 3) {
      digitalWrite(_pinSpeed3, true);
      OldSpeed = speed;
      return speed;
    } else if (speed == 4) {
      digitalWrite(_pinSpeed4, true);
      OldSpeed = speed;
      return speed;
    } else if (speed == 0) {
      if (light) {
        if (timer_switch(_Time1)) {  // если есть свет
          digitalWrite(_pinSpeed1, false);
          digitalWrite(_pinSpeed2, false);
          digitalWrite(_pinSpeed3, false);
          digitalWrite(_pinSpeed4, false);
        }
      } else {
        if (timer_switch(_Time2)) {
          digitalWrite(_pinSpeed1, false);
          digitalWrite(_pinSpeed2, false);
          digitalWrite(_pinSpeed3, false);
          digitalWrite(_pinSpeed4, false);
        }
      }
      OldSpeed = speed;
      return speed;
    }
  }
private:
  unsigned long Timer, Timer1;
  int _pinSpeed1, _pinSpeed2, _pinSpeed3, _pinSpeed4, OldSpeed;
  int _Time1, _Time2;
  int i;
  bool timer_switch(int v) {
    if (millis() - Timer >= 1000) {
      i++;
      Timer = millis();
      if (i >= v * 60) {
        i = 0;
        return true;
      } else {
        return false;
      }
    }
  }
};