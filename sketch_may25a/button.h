
class button {
public:
  button(char pin) {
    _pin = pin;
    pinMode(_pin, INPUT);
  }
  bool click() {
    int btnState = analogRead(_pin);
    if (btnState <= 20 && !_flag && time1(true)) {
      _flag = true;
      _tmr = millis();
      return true;
    }
    if (btnState <= 20 && _flag && time1(true)) {
      _tmr = millis();
      return true;
    }
    if (btnState >= 21 && _flag) {
      _flag = false;
      _tmr = millis();
      time1(false);
    }
    return false;
  }
private:
  char _pin;
  uint32_t _tmr;
  bool _flag;
  unsigned long Timer;
  int i;
  bool time1(bool v) {
    if (v) {
      if (millis() - Timer >= 1000) {
        i++;
        Timer = millis();
        if (i >= 2) {
          return true;
        } else {
          return false;
        }
      }
      return false;
    } else {
      i = 0;
      return false;
    }
  }
};