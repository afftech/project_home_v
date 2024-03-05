#include "Arduino.h"
#include "HardwareSerial.h"

class Toilet {
public:
  void run() {
    if (OnToilet) {
      digitalWrite(ToiletLight, 1);
    } else {
      digitalWrite(ToiletLight, 0);
    }
    if (!StateToilet) {
      TimeToilet = millis();
    }
  }
  void clickToilet() {
    if (millis() - TimeToilet <= 3000) {
      if (StateToilet == 0) {
        StateToilet = 1;
        OnToilet = true;
      } else {
        StateToilet = 0;
        OnToilet = false;
      }
    } else {
      StateToilet = 0;
      OnToilet = false;
    }
    TimeToilet = millis();
  }
  void Off_or_ONRoom() {
    if (OnToilet) {
      OnToilet = false;  //4
      StateToilet = 0;
    } else {
      OnToilet = true;  //4
      StateToilet = 1;
    }
  }
  void OffRoom() {
    OnToilet = false;  //4
    StateToilet = 0;
  }
private:
  bool OnToilet;
  int StateToilet;
  long TimeToilet;
};