#include "Arduino.h"
#include "HardwareSerial.h"

class Bathroom {
public:
  void run() {
    if (OnBathroomLight) {
      digitalWrite(BathroomLight, 1);
    } else {
      digitalWrite(BathroomLight, 0);
    }
    if (OnBathMirorLight) {
      digitalWrite(BathMirorLight, 1);
    } else {
      digitalWrite(BathMirorLight, 0);
    }

    if (!StateBathroomLight) {
      TimeClickBathroom = millis();
    }

    if (!StateBathMirorLight) {
      TimeClickMirror = millis();
    }
  }
  void clickMirror() {
    if (millis() - TimeClickMirror <= 3000) {
      if (StateBathMirorLight == 0) {
        StateBathMirorLight = 1;
        OnBathMirorLight = true;
      } else {
        StateBathMirorLight = 0;
        OnBathMirorLight = false;
      }
    } else {
      StateBathMirorLight = 0;
      OnBathMirorLight = false;
    }
    TimeClickMirror = millis();
  }
  void clickBathroom() {
    if (millis() - TimeClickBathroom <= 3000) {
      if (StateBathroomLight == 0) {
        StateBathroomLight = 1;
        OnBathroomLight = true;
      } else {
        StateBathroomLight = 0;
        OnBathroomLight = false;
      }
    } else {
      StateBathroomLight = 0;
      OnBathroomLight = false;
    }
    TimeClickBathroom = millis();
  }
  void OffRoom() {
    OnBathroomLight = false;   //4
    OnBathMirorLight = false;  //7

    StateBathroomLight = 0;
    StateBathMirorLight = 0;
  }
private:
  bool OnBathroomLight, OnBathMirorLight;
  int StateBathroomLight, StateBathMirorLight;
  long TimeClickBathroom, TimeClickMirror;
};