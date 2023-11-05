#include "Arduino.h"
#include "HardwareSerial.h"

class Control_Kitchen {
public:
  void run() {
    {
      if (OnApron) {
        digitalWrite(Apron, 1);
      } else {
        digitalWrite(Apron, 0);
      }
    }
  }
  void OffKitchen() {  //выкл всю кухню
    if (OnApron) {
      OnApron = false;
      //Control_BalconyRL.On_or_Off_BalconyR(0);SERIAL будет кухню выключать всю кухню
    } else {
      //Control_BalconyRL.On_or_Off_BalconyR(1);SERIAL будет кухню включать всю кухню
      OnApron = true;
    }
    //Serial.println(" Off");
  }
  void OffKitchenfrom_Hallway_Passage() {
    OnApron = false;
    //Control_BalconyRL.On_or_Off_BalconyR(0);SERIAL будет кухню выключать всю кухню
  }
  void clickApron() {
    OnApron = !OnApron;
  }

private:
  bool OnApron;
};