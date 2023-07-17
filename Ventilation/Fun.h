#include "HardwareSerial.h"

class Fun {
public:
  Fun(int pinSpeed1, int pinSpeed2, int pinSpeed3, int pinSpeed4, int Time1, int Time2, int Time3) {  //если есть свет это Time1 = 5, если нет Time2 =10
    _pinSpeed1 = pinSpeed1;
    _pinSpeed2 = pinSpeed2;
    _pinSpeed3 = pinSpeed3;
    _pinSpeed4 = pinSpeed4;
    _Time1 = Time1;
    _Time2 = Time2;
    _Time3 = Time3;
    pinMode(pinSpeed1, OUTPUT);
    pinMode(pinSpeed2, OUTPUT);
    pinMode(pinSpeed3, OUTPUT);
    pinMode(pinSpeed4, OUTPUT);
  }
  void run(bool Light) {
    if (!FunOff) {
      if (!OldSpeed) {  // получили сигнал 0 скорости
        //Serial.println("!OldSpeed");
        if (LightState && !Light) {  //если свет был включен потом выключен ждем 10 мин и вырубаем вытяку
          Serial.println("On and off");
          if (timer_switch(_Time2)) {
            digitalWrite(_pinSpeed1, false);
            digitalWrite(_pinSpeed2, false);
            digitalWrite(_pinSpeed3, false);
            digitalWrite(_pinSpeed4, false);
            FunOff = true;
          }
        }
        if (!LightState && !Light) {  //если свет не был включен ждем 5 мин и вырубаем вытяку
          Serial.println("off");
          if (timer_switch(_Time1)) {
            digitalWrite(_pinSpeed1, false);
            digitalWrite(_pinSpeed2, false);
            digitalWrite(_pinSpeed3, false);
            digitalWrite(_pinSpeed4, false);
            FunOff = true;
          }
        }
      } else {
        if (Light && !LightState) {
          LightState = true;
          Serial.println("LightState");
        }
        if (LightState && Light) {  //если свет долго включен ждем 30 мин и вырубаем вытяку
          Serial.println("on");
          if (timer_switch(_Time3)) {
            digitalWrite(_pinSpeed1, false);
            digitalWrite(_pinSpeed2, false);
            digitalWrite(_pinSpeed3, false);
            digitalWrite(_pinSpeed4, false);
            FunOff = true;
          }
        }
      }
    }
  }
  int Speed(int speed) {
    FunOff = false;  //обнуляем флаг остановки
    if (speed != 0) {
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
      }
    } else {
      OldSpeed = speed;
      return speed;
    }
  }
private:
  unsigned long Timer, Timer1;
  int _pinSpeed1, _pinSpeed2, _pinSpeed3, _pinSpeed4, OldSpeed;
  int _Time1, _Time2, _Time3;
  bool lightOn, FunOff = true, LightState;
  int i;
  bool timer_switch(int v) {
    if (v == 0) {
      return true;
    }
    if (millis() - Timer >= 1000) {
      i++;
      Serial.println(i);
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