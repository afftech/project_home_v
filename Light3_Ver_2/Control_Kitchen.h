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
      //Control_BalconyRL.On_or_Off_BalconyR(0);SERIAL будет всю кухню выключать
      SendData(0x1B2, 0x0101);
    } else {
      //Control_BalconyRL.On_or_Off_BalconyR(1);SERIAL будет всю кухню включать
      OnApron = true;
      SendData(0x1B2, 0x0102);
    }
    //Serial.println(" Off");
  }
  void OffKitchenfrom_Hallway_Passage() {
    OnApron = false;
    //Control_BalconyRL.On_or_Off_BalconyR(0);SERIAL будет всю кухню выключать
  }
  void clickApron() {
    OnApron = !OnApron;
  }
private:
  bool OnApron;
};