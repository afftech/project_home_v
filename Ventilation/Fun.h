#include "HardwareSerial.h"

class Fun {
public:
  Fun(int pinSpeed1, int pinSpeed2, int pinSpeed3, int pinSpeed4, int Time1, int Time2, int Time3) {  //если свет включен Time1 = 5, если свет выключен Time2 =10, если свет включен дольше  то тоже выкд.чаемTime3 =30
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
    //Serial.println(modManual);
    if (!FunOff) {   //скорость изменена
      if (!Check) {  //проверка света и скорости
        if (Light) {
          LightState = true;
          Serial.println("Light On");
        } else {
          LightState = false;
          Serial.println("Light Off");
        }
        Serial.println("waiting");
        Check = true;
      }
    }
    if (Check) {  //если свет долго включен ждем 30 мин и вырубаем вытяку
      if (Light) {
        //Serial.println("on");
        if (!LightState) {
          LightState = true;
        }
        if (timer_switch(_Time3)) {
          digitalWrite(_pinSpeed1, false);
          digitalWrite(_pinSpeed2, false);
          digitalWrite(_pinSpeed3, false);
          digitalWrite(_pinSpeed4, false);
          FunOff = true;
          Check = false;
          modManual = false;
          resetOn = true;
          Serial.println("resetOn");  //срабатывает какогото фига
        }
      } else {
        if (!LightState) {  //если свет не был включен ждем 5 мин и вырубаем вытяжку
          //Serial.println("off 1");
          if (timer_switch(_Time1)) {
            digitalWrite(_pinSpeed1, false);
            digitalWrite(_pinSpeed2, false);
            digitalWrite(_pinSpeed3, false);
            digitalWrite(_pinSpeed4, false);
            FunOff = true;
            Check = false;
            modManual = false;
            resetOn = true;
          }
        }
        if (LightState) {  //если свет  был включен ждем 10 мин и вырубаем вытякжу
          //Serial.println("off 2");
          if (timer_switch(_Time2)) {
            digitalWrite(_pinSpeed1, false);
            digitalWrite(_pinSpeed2, false);
            digitalWrite(_pinSpeed3, false);
            digitalWrite(_pinSpeed4, false);
            FunOff = true;
            Check = false;
            modManual = false;
            resetOn = true;
          }
        }
      }
    }
  }
  int Speed(int speed, bool Auto) {
    Serial.println(speed);
    if (Auto) {
      if (!modAuto) {  //если ручной режим был вкл раньше, то берём установленную скорость, а после откл режима авто возвращаем на нее
        if (OldSpeed != 0) {
          OldSpeedManual = OldSpeed;
        } /*как вариант*/
      }
      if (speed == 0) {
        modAuto = false;
        if (!modManual) {  //если ручн. режим выключен то обычная остановка, если вкл. то остановка по времени
          Change(0);
        } else {
          //Serial.println(OldSpeedManual);
          Change(OldSpeedManual);  //ставим скорость ручного режима который был задействован до автоматического
          //Serial.println(OldSpeed);
          FunOff = false;  //обнуляем флаг остановки и останавливаем как в ручном режиме
        }
      } else {
        modAuto = true;
        FunOff = true;  //если был включен ручной режим рвньше чем авто то сбрасываем его
        Check = false;
        Change(speed);
      }
    } else {
      if (modAuto) {
        if (speed == 0) {
          modManual = false;
        } else {
          Change(speed);
          modManual = true;
        }

      } else {
        FunOff = false;  //обнуляем флаг остановки
        modManual = true;
        Change(speed);
      }
    }
  }
  int Change(int speed) {
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
      digitalWrite(_pinSpeed1, false);
      digitalWrite(_pinSpeed2, false);
      digitalWrite(_pinSpeed3, false);
      digitalWrite(_pinSpeed4, false);
      FunOff = true;  //обнуляем флаг остановки
      Check = false;
      OldSpeed = speed;
      modManual = false;
      return speed;
    }
  }
  bool reset() {
    if (resetOn) {
      resetOn = false;
      return true;
    } else {
      return false;
    }
  }
private:
  unsigned long Timer, Timer1;
  int _pinSpeed1, _pinSpeed2, _pinSpeed3, _pinSpeed4, OldSpeed, OldSpeedManual;
  int _Time1, _Time2, _Time3;
  bool LightState, lightOn, FunOff = true, Check, modAuto, modManual;
  int i;
  bool resetOn;
  bool timer_switch(long v) {
    if (v == 0) {
      return true;
    }
    if (millis() - Timer >= 1000) {
      i++;
      //Serial.println(i);
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