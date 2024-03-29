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
  void New_Init_State(bool New_State) {
    _New_State = New_State;
    if (_New_State) {
      if (!modAuto && !modManual && OldSpeed < 1) {
        digitalWrite(_pinSpeed1, true);
        _New_Init_State = true;
        Serial.println("New_Init_State 3");
      }
      if ((modManual || modAuto) && OldSpeed != 1) {
        digitalWrite(_pinSpeed1, false);
        _New_Init_State = false;
        Serial.println("New_Init_State 1");
      }
    } else {
      if (!modAuto && !modManual && OldSpeed < 1) {
        digitalWrite(_pinSpeed1, false);
        _New_Init_State = false;
        Serial.println("New_Init_State 2");
      }
    }
  }
  bool retNew_state() {
    return _New_Init_State;
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
          offAll();
          FunOff = true;
          Check = false;
          modManual = false;
          resetOn = true;
        }
      } else {
        if (!LightState) {  //если свет не был включен ждем 5 мин и вырубаем вытяжку
          //Serial.println("off 1");
          if (timer_switch(_Time1)) {
            offAll();
            FunOff = true;
            Check = false;
            modManual = false;
            resetOn = true;
          }
        }
        if (LightState) {  //если свет  был включен ждем 10 мин и вырубаем вытякжу
          //Serial.println("off 2");
          if (timer_switch(_Time2)) {
            offAll();
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
    if (Auto) {
      if (!modAuto) {  //если ручной режим был вкл раньше, то берём установленную скорость, а после откл режима авто возвращаем на нее
        if (OldSpeed != 0) {
          OldSpeedManual = OldSpeed;
        } /*как вариант*/
      }
      if (speed == 0) {  //если скорость режима авто 0
        modAuto = false;
        if (!modManual) {  //если ручн. режим выключен то обычная остановка, если вкл. то остановка по времени
          Change(0);
          OldSpeedManual = 0;
        } else {
          Change(OldSpeedManual);  //ставим скорость ручного режима который был задействован до автоматического
          OldSpeedManual = 0;
          FunOff = false;  //обнуляем флаг остановки и останавливаем как в ручном режиме
        }
      } else {  //ручной режим включен
        modAuto = true;
        FunOff = true;  //если был включен ручной режим рвньше чем авто то сбрасываем его
        Check = false;
        Change(speed);
      }
    } else {  //В ручном режиме
      if (modAuto) {
        if (speed == 0) {
          modManual = false;
          OldSpeedManual = 0;
        } else {
          Change(speed);
          if (speed == 4) {
            OldSpeedManual = 4;
          }
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
    /*Serial.print("Change");
    Serial.println(speed);*/
    if (speed != 0) {
      if (speed != OldSpeed) {
        offAll();
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
      offAll();
      FunOff = true;  //обнуляем флаг остановки
      Check = false;
      OldSpeed = speed;
      modManual = false;
      return speed;
    }
  }
  int reset(bool reset) {
    if (!reset) {
      if (resetOn) {
        Serial.println("resetOn");
        OldSpeed = 0;
        resetOn = false;
        return true;
      } else {
        return false;
      }
    } else {
      if (modManual) {
        if (OldSpeed == 4) {
          return OldSpeedManual;
        }
      } else {
        if (OldSpeed == 4) {
          return 0;
        }
      }
      return OldSpeed;
    }
  }
  int retSpeed() {
    return OldSpeed;
  }
  void offAll() {
    digitalWrite(_pinSpeed1, false);
    digitalWrite(_pinSpeed2, false);
    digitalWrite(_pinSpeed3, false);
    digitalWrite(_pinSpeed4, false);
  }
private:
  unsigned long Timer, Timer1;
  int _pinSpeed1, _pinSpeed2, _pinSpeed3, _pinSpeed4, OldSpeed, OldSpeedManual;
  int _Time1, _Time2, _Time3;
  bool LightState, lightOn, FunOff = true, Check, modAuto, modManual;
  bool _New_State, _New_Init_State;
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