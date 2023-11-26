#include "HardwareSerial.h"
class Control_Hallway_Passage {
public:
  void run() {
    {
      if (StateLightHallway == 1) {  //
        digitalWrite(SmallLightHallway, 1);
        digitalWrite(BigLightHallway, 0);
      } else if (StateLightHallway == 2) {
        digitalWrite(SmallLightHallway, 0);
        digitalWrite(BigLightHallway, 1);
      } else if (StateLightHallway == 0) {
        digitalWrite(SmallLightHallway, 0);
        digitalWrite(BigLightHallway, 0);
      }
    }
    {
      if (StateLightPassage == 1) {  //прихожая
        digitalWrite(SmallLightPassage, 1);
        digitalWrite(BigLightPassage, 0);
      } else if (StateLightPassage == 2) {
        digitalWrite(SmallLightPassage, 0);
        digitalWrite(BigLightPassage, 1);
      } else if (StateLightPassage == 0) {
        digitalWrite(SmallLightPassage, 0);
        digitalWrite(BigLightPassage, 0);
      }
    }
    /*таймер гл выкл*/
    if (!StateLightHallway) {
      TimeClickMainHallway = millis();
    }
    if (!StateLightPassage) {
      TimeClickMainPassage = millis();
    }
  }
  bool OffPowerUnit() {
    if (StateLightHallway || StateLightPassage) {
      return true;
    }
    return false;
  }
  void clickMainHallway() {  // вкл малый свет, большой свет в прихожей выкл любой из них
    if (millis() - TimeClickMainHallway <= 3000) {
      if (StateLightHallway == 0) {
        StateLightHallway = 1;
      } else if (StateLightHallway == 1) {
        StateLightHallway = 2;
      } else {
        StateLightHallway = 0;
      }
    } else {
      StateLightHallway = 0;
    }
    Serial.print(F("StateLightHallway:"));
    Serial.println(StateLightHallway);
    TimeClickMainHallway = millis();
  }
  void long1ClickMainHallway() {  //вкл большой свет корридоре и прихожей
                                  //выкл весь свет в кв
    if (!StateLightHallway && !StateLightPassage) {
      StateLightHallway = 2;
      StateLightPassage = 2;
    } else if (StateLightHallway && !StateLightPassage) {
      StateLightPassage = StateLightHallway;
    } else if (!StateLightHallway && StateLightPassage) {
      StateLightHallway = StateLightPassage;
    } else if (StateLightHallway && StateLightPassage) {
      StateLightHallway = false;
      StateLightPassage = false;
    }
  }
  void long2ClickMainHallway() {
    //выкл весь свет в кв
    StateLightHallway = false;
    StateLightPassage = false;
    apartment = true;
  }
  bool apartmentOff() {
    if (apartment) {
      apartment = false;
      return 1;
    }
    return 0;
  }
  void clickMainPassage() {
    if (millis() - TimeClickMainPassage <= 3000) {
      if (StateLightPassage == 0) {
        StateLightPassage = 1;
      } else if (StateLightPassage == 1) {
        StateLightPassage = 2;
      } else {
        StateLightPassage = 0;
      }
    } else {
      StateLightPassage = 0;
    }
    Serial.print(F("StateLightPassage:"));
    Serial.println(StateLightPassage);
    TimeClickMainPassage = millis();
  }
  void long1ClickMainPassage() {
    StateLightPassage = 2;
  }
  void long2ClickMainPassage() {
    if (StateLightHallway || StateLightPassage) {
      StateLightHallway = false;
      StateLightPassage = false;
    } else {
      StateLightPassage = 2;
    }
  }

private:
  bool apartment;
  int StateLightHallway, StateLightPassage;
  long TimeClickMainHallway, TimeClickMainPassage;
};