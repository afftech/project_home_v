


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
        } else if ((_condition2 - 5) < dataBtn && dataBtn < (_condition2 + 5) && millis() - TimerCondition >= 10) {
          CheckCondition = false;
          _flag1 = false;
          _flag2 = true;
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
        hold1On = true;
      }
      if (_flag1 && Btn1State && millis() - TimerClick1 >= 1000) {
        TimerClick1 = millis();
        holdClick1_2 = true;
        return false;
      }
      if (!_flag1 && Btn1State) {
        if (hold1On && millis() - TimerClick1 < 500) {
          hold1On = false;
          Btn1State = false;
          return true;
        }
        if (hold1On && millis() - TimerClick1 >= 500) {
          holdClick1_1 = true;
          Btn1State = false;
          return false;
        }
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
  bool hold1_1() {
    if (holdClick1_1) {
      holdClick1_1 = false;
      hold1On = false;
      return true;
    }
    return false;
  }
  bool hold1_2() {
    if (holdClick1_2) {
      holdClick1_2 = false;
      hold1On = false;
      return true;
    }
    return false;
  }
  bool click2() {
    if (_BtnMode2) {
      if (_flag2 && !Btn2State && millis() - TimerClick2 >= 200) {
        Btn2State = true;
        TimerClick2 = millis();
        hold2On = true;
      }
      if (_flag2 && Btn2State && millis() - TimerClick2 >= 1000) {
        TimerClick2 = millis();
        holdClick2_2 = true;
        return false;
      }
      if (!_flag2 && Btn2State) {
        if (hold2On && millis() - TimerClick2 < 500) {
          Btn2State = false;
          hold1On = false;
          return true;
        }
        if (hold2On && millis() - TimerClick2 >= 500) {
          Btn2State = false;
          holdClick2_1 = true;
          return false;
        }
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
  bool hold2_1() {
    if (holdClick2_1) {
      holdClick2_1 = false;
      hold2On = false;
      return true;
    }
    return false;
  }
  bool hold2_2() {
    if (holdClick2_2) {
      holdClick2_2 = false;
      hold2On = false;
      return true;
    }
    return false;
  }
  bool stateAnyBtn() {
    if (_flag1 || _flag2) {
      return true;
    }
    return false;
  }
private:
  bool holdClick2, hold2On, hold1On, holdClick1_1, holdClick1_2, holdClick2_1, holdClick2_2;
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