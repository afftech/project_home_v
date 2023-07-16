#include "HardwareSerial.h"

class Fun {
public:
  Fun(int pinSpeed1, int pinSpeed2, int pinSpeed3, int pinSpeed4, char light, int Time1, int Time2) {  //если есть свет это Time1 = 5, если нет Time2 =10
    _pinSpeed1 = pinSpeed1;
    _pinSpeed2 = pinSpeed2;
    _pinSpeed3 = pinSpeed3;
    _pinSpeed4 = pinSpeed4;
    if (light == '!') {
      _Time1 = 0;
      _Time2 = 0;
    } else {
      pinMode(light, OUTPUT);
      _Time1 = Time1;
      _Time2 = Time2;
      _light = light;
    }
    pinMode(pinSpeed1, OUTPUT);
    pinMode(pinSpeed2, OUTPUT);
    pinMode(pinSpeed3, OUTPUT);
    pinMode(pinSpeed4, OUTPUT);
  }
  void run() {
    if (!OldSpeed && !FunOff) {
      if (lightOn) {
        if (timer_switch(Time1)) {
          digitalWrite(_pinSpeed1, false);
          digitalWrite(_pinSpeed2, false);
          digitalWrite(_pinSpeed3, false);
          digitalWrite(_pinSpeed4, false);
          FunOff = true;
        }
      } else {
        if (timer_switch(Time2)) {
          digitalWrite(_pinSpeed1, false);
          digitalWrite(_pinSpeed2, false);
          digitalWrite(_pinSpeed3, false);
          digitalWrite(_pinSpeed4, false);
          FunOff = true;
        }
      }
    }
  }
  int Speed(int speed) {
    FunOff = false;             //обнуляем флаг остановки
    if (digitalRead(_light)) {  //проверка света в пом
      lightOn = true;
    } else {
      lightOn = false;
    }
    if (speed != OldSpeed) {
      digitalWrite(_pinSpeed1, false);
      digitalWrite(_pinSpeed2, false);
      digitalWrite(_pinSpeed3, false);
      digitalWrite(_pinSpeed4, false);
    }
    if (speed != 0) {  //сбрасываем таймер
      i = 0;
    }
    if (speed == 1) {
      digitalWrite(_pinSpeed1, true);
      OldSpeed = speed;
      return speed;
    } else if (speed == 2) {
      //Serial.println(_pinSpeed2);
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
      OldSpeed = speed;
      return speed;
    }
  }
private:
  unsigned long Timer, Timer1;
  int _pinSpeed1, _pinSpeed2, _pinSpeed3, _pinSpeed4, OldSpeed, _light;
  int _Time1, _Time2;
  bool lightOn;
  int i;
  bool timer_switch(int v) {
    if (v == 0) {
      return true;
    }
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