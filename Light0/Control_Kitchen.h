#include "Arduino.h"
#include "HardwareSerial.h"

class Control_Kitchen {
public:
  void run() {

    {  //раб зона
      if (OnWorking_area) {
        digitalWrite(Working_area, 1);
      } else {
        digitalWrite(Working_area, 0);
      }
    }
    {  //Люстра
      if (OnLamp) {
        digitalWrite(Lamp, 1);
      } else {
        digitalWrite(Lamp, 0);
      }
    }
    {
      if (OnBar) {
        digitalWrite(Bar, 1);
      } else {
        digitalWrite(Bar, 0);
      }
    }
    {
      if (OnRibbon) {
        digitalWrite(Ribbon, 1);
      } else {
        digitalWrite(Ribbon, 0);
      }
    }
    {
      if (OnApron) {
        digitalWrite(Apron, 1);
      } else {
        digitalWrite(Apron, 0);
      }
    }
    if (StopTime && OldTimeMainKitchen + TimeDoubleClick <= millis()) {
      if (OldTimeMainKitchen < TimeMainKitchen) {  // один клик
        Serial.println("Two clicks.");
        OnStateLamp();
      } else if (OldTimeMainKitchen == TimeMainKitchen) {  //два клика
        Serial.println("One Click");
        OnStateWorking_area();
      }
      StopTime = false;
    }
  }
  void clickMainKitchen() {
    if (StopTime) {
      Serial.println(" clicks.");
      TimeMainKitchen = millis();
    }
    if (!StopTime) {
      OldTimeMainKitchen = millis();
      TimeMainKitchen = OldTimeMainKitchen;
      StopTime = true;
    }
  }

  void OnStateLamp() {
    OnLamp = !OnLamp;
  }
  void OnStateWorking_area() {
    OnWorking_area = !OnWorking_area;
  }
  void clickLamp() {
    OnStateLamp();
  }
  void OffKitchen() {  //выкл всю кухню
    OnWorking_area = false;
    OnLamp = false;
    OnBar = false;
    OnRibbon = false;
    OnApron = false;
    //Serial.println(" Off");
  }
  void clickBar() {
    OnBar = !OnBar;
  }
  void clickRibbon() {
    OnRibbon = !OnRibbon;
  }
  void clickApron() {
    OnApron = !OnApron;
  }

private:
  bool OnWorking_area, OnLamp, OnBar, OnRibbon, OnApron, StopTime;
  long OldTimeMainKitchen, TimeMainKitchen;
};