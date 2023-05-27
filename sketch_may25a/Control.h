
class control {
public:
  void buttons() {
    if (ButtonValve1.click()) {
      switch (CurrentStateKitchen) {
        case 0:
          Valve1State = 1;
          print("CurrentStateKitchen 0");
          print(Valve1State);
          break;
        case 1:
          Valve1State = 2;
          print("CurrentStateKitchen 1");
          print(Valve1State = 2);
          break;
      }
    }
  }
  void AutoKitchen() {
    print(SignalKitchen);
    bool state = true;
    if (SignalKitchen && Valve1State == 0 && CurrentStateKitchen !=1) {//закрыть по датчику
      if (OpenClose(1)) {
        CurrentStateKitchen = 1;
        Valve1State = 0;
        SignalKitchen = 0;
        OpenClose(0);
      }
    }
    if (Valve1State == 1 && Valve1State != 2) {//закрыть по кнопке
      if (OpenClose(1)) {
        CurrentStateKitchen = 1;
        Valve1State = 0;
        SignalKitchen = 0;
        OpenClose(0);
      }
    }
    if (Valve1State == 2 && Valve1State != 1) {
      if (OpenClose(2)) {
        CurrentStateKitchen = 0;
        Valve1State = 0;
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
    } else if (y == 0) {
      increment = 0;
      return true;
    }
  }
  void Signals() {
    if (analogRead(DataSensor1) <= 200 || analogRead(DataSensor2) <= 200 || analogRead(DataSensor3) <= 200) {
        SignalKitchen = 1;
    }else {
    SignalKitchen =0;
    }
    if (analogRead(DataSensor4) <= 200 || analogRead(DataSensor5) <= 200 || analogRead(DataSensor6) <= 200) {
      SignalBathroom = 1;
    }
  }
private:
};