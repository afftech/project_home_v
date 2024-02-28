#include "HardwareSerial.h"
class Button {
public:
  Button(char pin, int BtnMode) {
    _pin = pin;
    _BtnMode = BtnMode;
    pinMode(_pin, INPUT);
  }
  void check() {
    int dataBtn = analogRead(_pin);
    if (dataBtn <= 20) {
      _flag = true;
      //Serial.println("_flag = true;");
    } else if (dataBtn >= 21) {
      _flag = false;
      //Serial.println("_flag = false;");
    }
  }
  bool click() {
    if (_BtnMode) {
      if (!holdStop && _flag && !BtnState && millis() - TimerClick1 >= BtnGroupTime1) {
        BtnState = true;
        TimerClick1 = millis();
        holdOn = true;
      }
      if (!holdStop && _flag && BtnState && millis() - TimerClick1 >= BtnGroupTime3) {
        TimerClick1 = millis();
        holdClick2 = true;
        return false;
      }
      if (!_flag && BtnState) {
        if (holdOn && millis() - TimerClick1 < BtnGroupTime2) {
          holdOn = false;
          BtnState = false;
          return true;
        }
        if (holdOn && millis() - TimerClick1 >= BtnGroupTime2) {
          holdClick1 = true;
          BtnState = false;
          return false;
        }
        if (!_flag) {
          holdStop = false;
        }
        BtnState = false;
        TimerClick1 = millis();
        return false;
      }
      return false;
    } else {
      if (_flag) {
        return true;
      }
      return false;
    }
  }
  bool hold1() {
    if (holdClick1) {
      holdClick1 = false;
      holdOn = false;
      return true;
    }
    return false;
  }
  bool hold2() {
    if (holdClick2 && !holdStop) {
      holdStop = true;
      holdClick2 = false;
      holdOn = false;
      return true;
    }
    return false;
  }

  bool stateBtn() {
    if (_flag) {
      return true;
    }
    return false;
  }
private:
  bool holdOn, holdClick1, holdClick2, holdStop;
  bool _flag, BtnState;
  int _BtnMode;
  char _pin;
  unsigned long TimerClick1;
};