#include "HardwareSerial.h"

class Control_BalconyRL {
public:
  void run() {
    {
      if (OnBalconyR) {
        digitalWrite(BalconyR, 1);
      } else {
        digitalWrite(BalconyR, 0);
      }
    }
    {
      if (OnBalconyL) {
        digitalWrite(BalconyL, 1);
      } else {
        digitalWrite(BalconyL, 0);
      }
    }
    if (!StateBalconyR) {
      TimeClickMainBalconyR = millis();
    }
    if (!StateBalconyL) {
      TimeClickMainBalconyL = millis();
    }
  }
  void clickMainBalconyR() {
    if (millis() - TimeClickMainBalconyR <= 3000) {
      if (StateBalconyR == 0) {
        StateBalconyR = 1;
        OnBalconyR = true;
      } else if (StateBalconyR == 1) {
        StateBalconyR = 2;
        OnBalconyL = true;
      } else {
        StateBalconyR = 0;
        OnBalconyR = false;
        OnBalconyL = false;
      }
    } else {
      StateBalconyR = 0;
      OnBalconyR = false;
      OnBalconyL = false;
    }
    TimeClickMainBalconyR = millis();
  }
  void OffBalconyLR() {
    OnBalconyR = false;
    OnBalconyL = false;
    StateBalconyR = false;
    StateBalconyL = false;
  }
  void clickMainBalconyL() {
    if (millis() - TimeClickMainBalconyL <= 3000) {
      if (StateBalconyL == 0) {
        StateBalconyL = 1;
        OnBalconyL = true;
      } else if (StateBalconyL == 1) {
        StateBalconyL = 2;
        OnBalconyR = true;
      } else {
        StateBalconyL = 0;
        OnBalconyR = false;
        OnBalconyL = false;
      }
    } else {
      StateBalconyL = 0;
      OnBalconyR = false;
      OnBalconyL = false;
    }
    TimeClickMainBalconyL = millis();
  }

private:
  bool OnBalconyR, OnBalconyL;
  int StateBalconyR, StateBalconyL;
  long TimeClickMainBalconyR, TimeClickMainBalconyL;
};