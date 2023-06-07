#include "Voice.h"
voice voice;
bool Valve2State, SignalKitchen, CurrentStateKitchen,
  SignalBathroom, CurrentStateBathroom;
bool SensorKitchenState = false;
bool SensorBathroomState = false;
int ValveKitchen, ValveBathroom;
class control {
public:

  void buttons() {
    if (ButtonValve1.click()) {
      switch (CurrentStateKitchen) {
        case 0:
          ValveKitchen = 1;
          break;
        case 1:
          ValveKitchen = 2;
          break;
      }
    }
    if (ButtonValve2.click()) {
      switch (CurrentStateBathroom) {
        case 0:
          ValveBathroom = 1;
          break;
        case 1:
          ValveBathroom = 2;
          break;
      }
    }
  }
  void AutoBathroom() {
    bool state = true;

    if (SignalBathroom && ValveBathroom == 0 && CurrentStateBathroom != 1) {  //закрыть по датчику
      SensorBathroomState = true;
    }
    if (SensorBathroomState) {
      if (OpenClose(3)) {
        CurrentStateBathroom = 1;
        ValveBathroom = 0;
        SignalBathroom = 0;
        OpenClose(0);
        SensorBathroomState = false;
      }
    }
    if (ValveBathroom == 1 && ValveBathroom != 2) {  //закрыть по кнопке
      if (OpenClose(3)) {
        CurrentStateBathroom = 1;
        ValveBathroom = 0;
        SignalBathroom = 0;
        OpenClose(0);
      }
    }
    if (ValveBathroom == 2 && ValveBathroom != 1) {
      if (OpenClose(4)) {
        CurrentStateBathroom = 0;
        ValveBathroom = 0;
        OpenClose(0);
      }
    }
    if (state) {
      //OpenClose(0);
    }
  }
  void AutoKitchen() {
    bool state = true;

    if (SignalKitchen && ValveKitchen == 0 && CurrentStateKitchen != 1) {  //закрыть по датчику
      SensorKitchenState = true;
    }
    if (SensorKitchenState) {
      if (OpenClose(1)) {
        CurrentStateKitchen = 1;
        ValveKitchen = 0;
        SignalKitchen = 0;
        OpenClose(0);
        SensorKitchenState = false;
      }
    }
    if (ValveKitchen == 1 && ValveKitchen != 2) {  //закрыть по кнопке
      if (OpenClose(1)) {
        CurrentStateKitchen = 1;
        ValveKitchen = 0;
        SignalKitchen = 0;
        OpenClose(0);
      }
    }
    if (ValveKitchen == 2 && ValveKitchen != 1) {
      if (OpenClose(2)) {
        CurrentStateKitchen = 0;
        ValveKitchen = 0;
        OpenClose(0);
      }
    }
    if (state) {
      //OpenClose(0);
    }
  }
  bool OpenClose(int y) {
    if (y == 1) {
      if (millis() - Timer1 >= 1000) {
        print(increment);
        increment++;
        Timer1 = millis();
        if (increment >= 6) {
          digitalWrite(Valve1Open, false);
          increment = 0;
          return true;
        } else {
          digitalWrite(Valve1Open, true);
          voice.OpenKitchen();
          return false;
        }
      }
      return false;
    }
    if (y == 2) {
      if (millis() - Timer1 >= 1000) {
        Timer1 = millis();
        increment++;
        if (increment >= 6) {
          digitalWrite(Valve1Close, false);
          increment = 0;
          return true;
        } else {
          digitalWrite(Valve1Close, true);
          return false;
        }
      }
      return false;
    }
    if (y == 3) {
      if (millis() - Timer1 >= 1000) {
        Timer1 = millis();
        increment++;
        if (increment >= 6) {
          digitalWrite(Valve2Open, false);
          increment = 0;
          return true;
        } else {
          digitalWrite(Valve2Open, true);
          return false;
        }
      }
      return false;
    }
    if (y == 4) {
      if (millis() - Timer1 >= 1000) {
        Timer1 = millis();
        increment++;
        if (increment >= 6) {
          digitalWrite(Valve2Close, false);
          increment = 0;
          return true;
        } else {
          digitalWrite(Valve2Close, true);
          return false;
        }
      }
      return false;
    } else if (y == 0) {
      increment = 0;
      return true;
    }
  }
  void Signals() {
    if (analogRead(DataSensor1) <= 200 || analogRead(DataSensor2) <= 200 || analogRead(DataSensor3) <= 200) {
      SignalKitchen = 1;
    } else {
      SignalKitchen = 0;
    }
    if (analogRead(DataSensor4) <= 200 || analogRead(DataSensor5) <= 200 || analogRead(DataSensor6) <= 200) {
      SignalBathroom = 1;
    } else {
      SignalBathroom = 0;
    }
  }
private:
};