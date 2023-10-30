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
    if (StopTime && OldTimeMainKitchen + 300 <= millis()) {
      if (OldTimeMainKitchen < TimeMainKitchen) {
        Serial.println("Two click");
        OnStateLamp();
      } else if (OldTimeMainKitchen == TimeMainKitchen) {
        Serial.println("One Click");
        OnStateWorking_area();
      }
      StopTime = false;
    }

    if (StopTimeLamp && OldTimeLamp + 300 <= millis()) {
      if (OldTimeLamp < TimeLamp) {
        Serial.println("Two click");
        if (Control_BalconyRL.Global_StateBalconyR()) {
          Control_BalconyRL.On_or_Off_BalconyR(0);
        } else {
          Control_BalconyRL.On_or_Off_BalconyR(1);
        }
      } else if (OldTimeLamp == TimeLamp) {
        Serial.println("One Click");
        OnLamp = !OnLamp;
      }
      StopTimeLamp = false;
    }
  }
  void clickMainKitchen() {
    if (StopTime) {
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
    if (OnLamp) {
      Control_BalconyRL.On_or_Off_BalconyR(1);
    } else {
      Control_BalconyRL.On_or_Off_BalconyR(0);
    }
  }
  void OnStateWorking_area() {
    OnWorking_area = !OnWorking_area;
  }
  void clickLamp() {  //двойной клик добавить и вторым дергать балкон R
    if (StopTimeLamp) {
      TimeLamp = millis();
    }
    if (!StopTimeLamp) {
      OldTimeLamp = millis();
      TimeLamp = OldTimeLamp;
      StopTimeLamp = true;
    }
    //OnStateLamp();
  }
  void OffKitchen() {  //выкл всю кухню
    if (OnWorking_area || OnLamp || OnBar || OnRibbon || OnApron) {
      OnWorking_area = false;
      OnLamp = false;
      OnBar = false;
      OnRibbon = false;
      OnApron = false;
      Control_BalconyRL.On_or_Off_BalconyR(0);
    } else {
      Control_BalconyRL.On_or_Off_BalconyR(1);
      OnWorking_area = true;
      OnLamp = true;
      OnBar = true;
      OnRibbon = true;
      OnApron = true;
    }
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
  bool OnWorking_area, OnLamp, OnBar, OnRibbon, OnApron, StopTime, StopTimeLamp;
  long OldTimeMainKitchen, TimeMainKitchen, TimeLamp, OldTimeLamp;
};