#include "HardwareSerial.h"
#include "Server.h"

bool Valve2State, SignalKitchen, OldSignalKitchen, CurrentStateKitchen,
  SignalBathroom, OldSignalBathroom, CurrentStateBathroom;
bool SensorKitchenState = false;
bool SensorBathroomState = false;
int ValveKitchen, ValveBathroom;
bool ManualKitchenControl, ManualBathroomControl;
class control {
public:
  control(int sec) {
    _sec = sec;
  }
  void buttons() {
    if (ButtonValve1.click()) {
      Serial.println("ButtonValve1.click()");
      voice.Play(2);
    }
    if (ButtonValve2.click()) {
      Serial.println("ButtonValve2.click()");
      voice.Play(10);
    }
    if (ButtonValve1.hold2()) {
      Serial.println("ButtonValve1.hold2()");
      if (ValveKitchen != 0) {
        digitalWrite(Valve1Open, false);
        digitalWrite(Valve1Close, false);
        CurrentStateKitchen = !CurrentStateKitchen;
        increment = 0;
      }
      /*  */
      switch (CurrentStateKitchen) {
        case 0:
          ValveKitchen = 1;  //Закрытие кранов
          voice.Play(3);
          onStait_Kitchen = 1;
          break;
        case 1:  //Открытие вида 2 сообщения
          ValveKitchen = 2;
          onStait_Kitchen = 0;
          if (LeakKitchen) {
            LeakKitchen = false;
            ManualKitchenControl = true;  // открываем в ручнуом реджиме, откл авто до снятия сигналов
            voice.Play(8);
          } else {
            if (OldSignalKitchen) {
              voice.Play(6);
              OldSignalKitchen = false;  //снимаем состояние протечки после сообщения о ней и открытия
            } else {
              voice.Play(5);  //Протечек не было просто открываем
            }
          }
          break;
      }
    }
    if (ButtonValve2.hold2()) {
      Serial.println("ButtonValve2.hold2()");
      if (ValveBathroom != 0) {
        digitalWrite(Valve2Open, false);
        digitalWrite(Valve2Close, false);
        CurrentStateBathroom = !CurrentStateBathroom;
        increment1 = 0;
      }
      switch (CurrentStateBathroom) {
        case 0:  //Закрытие кранов
          ValveBathroom = 1;
          voice.Play(11);
          onStait_Bathroom = 1;
          break;
        case 1:  //Открытие кранов
          ValveBathroom = 2;
          onStait_Bathroom = 0;
          if (LeakBathroom) {
            LeakBathroom = false;
            ManualBathroomControl = true;  // открываем в ручнуом реджиме, откл авто до снятия сигналов
            voice.Play(8);
          } else {
            if (OldSignalBathroom) {
              voice.Play(13);
              OldSignalBathroom = false;  //снимаем состояние протечки после сообщения о ней и открытия
            } else {
              voice.Play(12);  //Протечек не было просто открываем
            }
          }
          break;
      }
    }
  }
  void AutoBathroom() {
    if (!ManualBathroomControl && SignalBathroom && ValveBathroom == 0 && CurrentStateBathroom != 1) {  //закрыть по датчику
      if (voice.Play(9)) {
        SensorBathroomState = true;
        LeakBathroom = true;  //фиксируем состояние протечки
      }
    }
    if (SensorBathroomState) {
      if (OpenCloseBathroom(4)) {
        CurrentStateBathroom = 1;
        ValveBathroom = 0;
        SignalBathroom = 0;
        OpenCloseBathroom(0);
        SensorBathroomState = false;
      }
    }
    if (ValveBathroom == 1 && ValveBathroom != 2) {  //закрыть по кнопке
      if (OpenCloseBathroom(4)) {
        CurrentStateBathroom = 1;
        ValveBathroom = 0;
        SignalBathroom = 0;
        OpenCloseBathroom(0);
      }
    }
    if (ValveBathroom == 2 && ValveBathroom != 1) {
      if (OpenCloseBathroom(3)) {
        CurrentStateBathroom = 0;
        ValveBathroom = 0;
        OpenCloseBathroom(0);
      }
    }
    Strait_Bathroom.loop();
    if (onStait_Bathroom && !LeakBathroom) {  //если включено от кнопки и не было протечки
      if (!OldSignalBathroom) {
        Strait_Bathroom.set_State(1);
      } else {
        Strait_Bathroom.set_State(0);
      }
    } else {
      Strait_Bathroom.set_State(0);
    }
  }
  void AutoKitchen() {
    if (!ManualKitchenControl && SignalKitchen && ValveKitchen == 0 && CurrentStateKitchen != 1) {  //закрыть по датчику
      if (voice.Play(1)) {
        SensorKitchenState = true;
        LeakKitchen = true;  //фиксируем состояние протечки
      }
    }
    if (SensorKitchenState) {
      if (OpenClose(2)) {
        CurrentStateKitchen = 1;
        ValveKitchen = 0;
        SignalKitchen = 0;
        OpenClose(0);
        SensorKitchenState = false;
      }
    }
    if (ValveKitchen == 1 && ValveKitchen != 2) {  //закрыть по кнопке
      if (OpenClose(2)) {
        CurrentStateKitchen = 1;
        ValveKitchen = 0;
        SignalKitchen = 0;
        OpenClose(0);
      }
    }
    if (ValveKitchen == 2 && ValveKitchen != 1) {  //открыть
      if (OpenClose(1)) {
        CurrentStateKitchen = 0;
        ValveKitchen = 0;
        OpenClose(0);
      }
    }
    Strait_Kitchen.loop();
    if (onStait_Kitchen && !LeakKitchen) {  //если включено от кнопки и не было протечки
      if (!OldSignalKitchen) {
        Strait_Kitchen.set_State(1);
      } else {
        Strait_Kitchen.set_State(0);
      }
    } else {
      Strait_Kitchen.set_State(0);
    }
  }
  bool OpenClose(int y) {
    if (y == 1) {
      if (millis() - Timer1 >= 1000) {
        increment++;
        Timer1 = millis();
        if (increment >= _sec) {
          digitalWrite(Valve1Open, false);
          increment = 0;
          voice.Play(7);  //краны закрыты
          return true;
        } else {
          digitalWrite(Valve1Open, true);
          return false;
        }
      }
      return false;
    }
    if (y == 2) {
      if (millis() - Timer1 >= 1000) {
        Timer1 = millis();
        increment++;
        if (increment >= _sec) {
          digitalWrite(Valve1Close, false);
          increment = 0;
          voice.Play(4);  //краны закрыты
          return true;
        } else {
          digitalWrite(Valve1Close, true);
          return false;
        }
      }
      return false;
    }
    if (y == 0) {
      increment = 0;
      return true;
    }
  }
  bool OpenCloseBathroom(int y) {
    if (y == 3) {
      if (millis() - Timer2 >= 1000) {
        Timer2 = millis();
        increment1++;
        if (increment1 >= _sec) {
          digitalWrite(Valve2Open, false);
          increment1 = 0;
          return true;
        } else {
          digitalWrite(Valve2Open, true);
          return false;
        }
      }
      return false;
    }
    if (y == 4) {
      if (millis() - Timer2 >= 1000) {
        Timer2 = millis();
        increment1++;
        if (increment1 >= _sec) {
          digitalWrite(Valve2Close, false);
          increment1 = 0;
          //voice.Play(11);  //краны закрыты
          return true;
        } else {
          digitalWrite(Valve2Close, true);
          return false;
        }
      }
      return false;
    }
    if (y == 0) {
      increment = 0;
      return true;
    }
  }
  void Signals() {
    if ((analogRead(DataSensor1) <= 200 || analogRead(DataSensor2) <= 200 || analogRead(DataSensor3) <= 200) && !SensorKitchenState) {
      SignalKitchen = 1;
      if (onStait_Kitchen == 1) {
        OldSignalKitchen = true;
      }
    } else {
      SignalKitchen = 0;
      ManualKitchenControl = false;  // снимаем ручное режим ручного открытия  как высохнут датчики и переводим в автомат
    }
    if ((analogRead(DataSensor4) <= 200 || analogRead(DataSensor5) <= 200 || analogRead(DataSensor6) <= 200) && !SensorBathroomState) {
      SignalBathroom = 1;
      if (onStait_Bathroom == 1) {
        OldSignalBathroom = true;
      }
    } else {
      SignalBathroom = 0;
      ManualBathroomControl = false;
    }
  }
private:
  bool onStait_Kitchen, onStait_Bathroom;
  bool LeakKitchen, LeakBathroom;
  int increment, increment1, _sec;
  unsigned long Timer1, Timer2;
};