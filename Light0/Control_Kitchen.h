#include "Arduino.h"
#include "HardwareSerial.h"

class Control_Kitchen {
public:
  void run() {
    {
      if (OnWorking_area) {
        digitalWrite(Working_area, 1);
      } else {
        digitalWrite(Working_area, 0);
      }
    }
    {
      if (OnLamp) {
        digitalWrite(Lamp, 1);
      } else {
        digitalWrite(Lamp, 0);
      }
    }

    if (StopTime && OldTimeMainKitchen + 500 <= millis()) {
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
private:
  bool OnWorking_area, OnLamp, StateclickMainKitchen, StopTime;
  long OldTimeMainKitchen, TimeMainKitchen;
};