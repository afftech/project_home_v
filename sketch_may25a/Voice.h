#include "Print.h"
class voice {
public:
  voice() {
    pinMode(6, OUTPUT);  //открыть кухню
    pinMode(7, OUTPUT);  //закрыть кухню
    pinMode(8, OUTPUT);  //открыть кухню
    pinMode(9, OUTPUT);  //закрыть кухню
    digitalWrite(6, true);
    digitalWrite(7, true);
    digitalWrite(8, true);
    digitalWrite(9, true);
  }
  void process() {
    //кухня
    if (PlayOpenKitchen) {
      if (timer()) {
        digitalWrite(6, true);
        PlayOpenKitchen = false;
      }
    }
    if (PlayCloseKitchen) {
      if (timer()) {
        digitalWrite(7, true);
        PlayCloseKitchen = false;
      }
    }
    //Ванная комната
    if (PlayOpenBathroom) {
      if (timer()) {
        digitalWrite(8, true);
        PlayOpenBathroom = false;
      }
    }
    if (PlayCloseBathroom) {
      if (timer()) {
        digitalWrite(9, true);
        PlayCloseBathroom = false;
      }
    }
  }
  bool OpenKitchen() {
    digitalWrite(6, false);
    PlayOpenKitchen = true;
    T1 = millis();
    Serial.println("Open");
    return true;
  }
  bool CloseKitchen() {
    digitalWrite(7, false);
    PlayCloseKitchen = true;
    Serial.println("Close");
    T1 = millis();
    return true;
  }
  bool OpenBathroom() {
    digitalWrite(8, false);
    PlayOpenBathroom = true;
    T1 = millis();
    Serial.println("Open");
    return true;
  }
  bool CloseBathroom() {
    digitalWrite(9, false);
    PlayCloseBathroom = true;
    Serial.println("Close");
    T1 = millis();
    return true;
  }
  bool timer() {
    if (millis() - T1 >= 200) {
      Serial.println("millis() - T1");
      Serial.println(millis() - T1);
      return true;
    }
    return false;
  }
private:
  bool PlayOpenKitchen, PlayCloseKitchen, PlayOpenBathroom, PlayCloseBathroom;
  long T1;
};