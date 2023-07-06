#include "Arduino.h"
class ButtonGroup {
public:
  ButtonGroup(char pin, int BtnMode1, int BtnMode2, int expectation, int condition1, int condition2, int condition3) {
    _pin = pin;
    _BtnMode1 = BtnMode1;
    _BtnMode2 = BtnMode2;
    _expectation = expectation;
    _condition1 = condition1;
    _condition2 = condition2;
    _condition3 = condition3;
    pinMode(_pin, INPUT);
  }
  void check() {
    int dataBtn = analogRead(_pin);
    if (dataBtn < (_expectation - 10)) {
      if (millis() - TimerExpectation >= 10) {
        if (!CheckCondition) {
          CheckCondition = true;
          TimerCondition = millis();
        }
        if ((_condition1 - 5) < dataBtn && dataBtn < (_condition1 + 5) && millis() - TimerCondition >= 10) {
          CheckCondition = false;
          _flag1 = true;
          _flag2 = false;
          //Serial.println("123");
        } else if ((_condition2 - 5) < dataBtn && dataBtn < (_condition2 + 5) && millis() - TimerCondition >= 10) {
          CheckCondition = false;
          _flag1 = false;
          _flag2 = true;
          //Serial.println("321");
        } else if ((_condition3 - 5) < dataBtn && dataBtn < (_condition3 + 5) && millis() - TimerCondition >= 10) {
          CheckCondition = false;
          _flag1 = true;
          _flag2 = true;
        }
      }
    } else {
      CheckCondition = false;
      _flag1 = false;
      _flag2 = false;
      TimerExpectation = millis();
    }
  }
  bool click1() {
    if (_BtnMode1) {
      if (_flag1 && !Btn1State && millis() - TimerClick1 >= 200) {
        Btn1State = true;
        TimerClick1 = millis();
        return true;
      }
      if (_flag1 && Btn1State && millis() - TimerClick1 >= 2000) {
        TimerClick1 = millis();
        return true;
      }
      if (!_flag1 && Btn1State) {
        Btn1State = false;
        TimerClick1 = millis();
        return false;
      }
      return false;
    } else {
      if (_flag1) {
        return true;
      }
      return false;
    }
  }
  bool click2() {
    if (_BtnMode2) {
      if (_flag2 && !Btn2State && millis() - TimerClick2 >= 200) {
        Btn2State = true;
        TimerClick2 = millis();
        return true;
      }
      if (_flag2 && Btn2State && millis() - TimerClick2 >= 2000) {
        TimerClick2 = millis();
        return true;
      }
      if (!_flag2 && Btn2State) {
        Btn2State = false;
        TimerClick2 = millis();
        return false;
      }
      return false;
    } else {
      if (_flag2) {
        return true;
      }
      return false;
    }
  }
private:

  bool _flag1, _flag2, CheckCondition, CheckClick1, CheckClick2, Btn1State, Btn2State;
  int _holdTimeclick1, _holdTimeclick2;
  int _expectation;
  int _condition1;
  int _condition2;
  int _condition3;
  int _BtnMode1, _BtnMode2;
  char _pin;
  uint32_t TimerExpectation, TimerCondition, TimerClick1, TimerClick2;
};