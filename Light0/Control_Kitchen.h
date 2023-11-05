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
      if (OnBra) {
        digitalWrite(Bra, 1);
      } else {
        digitalWrite(Bra, 0);
      }
    }
    {
      if (OnRibbon) {
        digitalWrite(Ribbon, 1);
      } else {
        digitalWrite(Ribbon, 0);
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

    if (StopTimeBra && OldTimeBra + 300 <= millis()) {
      if (OldTimeBra < TimeBra) {
        Serial.println("Two click");
        if (OnLamp || OnRibbon || OnBra || OnRibbon) {
          OnWorking_area = !OnWorking_area;
        } else {
          OnBra = !OnBra;
        }
      } else if (OldTimeBra == TimeBra) {
        Serial.println("One Click");
        if (OnLamp || OnRibbon || OnBra || OnRibbon) {
          OnBra = !OnBra;
        } else {
          OnWorking_area = !OnWorking_area;
        }
      }
      StopTimeBra = false;
    }
    if (StopTimeRibbon && OldTimeRibbon + 300 <= millis()) {
      if (OldTimeRibbon < TimeRibbon) {
        Serial.println("Two click");
        if (OnLamp || OnRibbon || OnBra || OnRibbon) {
          OnWorking_area = !OnWorking_area;
        } else {
          OnRibbon = !OnRibbon;
        }
      } else if (OldTimeRibbon == TimeRibbon) {
        Serial.println("One Click");
        if (OnLamp || OnRibbon || OnBra || OnRibbon) {
          OnRibbon = !OnRibbon;
        } else {
          OnWorking_area = !OnWorking_area;
        }
      }
      StopTimeRibbon = false;
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
    if (OnWorking_area || OnLamp || OnBra || OnRibbon) {
      OnWorking_area = false;
      OnLamp = false;
      OnBra = false;
      OnRibbon = false;
      Control_BalconyRL.On_or_Off_BalconyR(0);
    } else {
      Control_BalconyRL.On_or_Off_BalconyR(1);
      OnWorking_area = true;
      OnLamp = true;
      OnBra = true;
      OnRibbon = true;
    }
    //Serial.println(" Off");
  }
  void OffKitchenfrom_Hallway_Passage() {
    OnWorking_area = false;
    OnLamp = false;
    OnBra = false;
    OnRibbon = false;
    Control_BalconyRL.On_or_Off_BalconyR(0);
  }
  void clickBra() {  //если что то на кухне горит то включаем/выключаем бру одним кликом, а двойным управляем
    if (StopTimeBra) {
      TimeBra = millis();
    }
    if (!StopTimeBra) {
      OldTimeBra = millis();
      TimeBra = OldTimeBra;
      StopTimeBra = true;
    }
  }
  void clickRibbon() {  //аналогично с брой
                        //OnRibbon = !OnRibbon;
    if (StopTimeRibbon) {
      TimeRibbon = millis();
    }
    if (!StopTimeRibbon) {
      OldTimeRibbon = millis();
      TimeRibbon = OldTimeRibbon;
      StopTimeRibbon = true;
    }
  }



private:
  bool OnWorking_area, OnLamp, OnBra, OnRibbon, StopTime, StopTimeLamp, StopTimeBra, StopTimeRibbon;
  long OldTimeMainKitchen, TimeMainKitchen, TimeLamp, OldTimeLamp, OldTimeBra, TimeBra, TimeRibbon, OldTimeRibbon;
};