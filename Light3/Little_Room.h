
class Little_Room {
#include "TimerOff.h"
  Timer TimerControlState{ TimeOffDT };
public:
  void run() {
    TimerControlState.run();
    if (TimerControlState.resp()) {
      ControlLittleRoom = false;
    }
    if (OnLitleRoomLight1) {
      digitalWrite(LitleRoomLight1, 1);
    } else {
      digitalWrite(LitleRoomLight1, 0);
    }
    if (OnLitleRoomLight2) {
      digitalWrite(LitleRoomLight2, 1);
    } else {
      digitalWrite(LitleRoomLight2, 0);
    }
    if (OnLitleBraLRLight3) {
      digitalWrite(LitleBraLRLight3, 1);
    } else {
      digitalWrite(LitleBraLRLight3, 0);
    }
    if (!StateSwitchRoom) {
      TimeClickSwitchRoom = millis();
    }
    if (!StateLitleBraLRLight3) {
      TimeClickLitleBraLRLight3 = millis();
    }
    if (StopTimeLitleRBra && OldTimeLitleRBra + 300 <= millis()) {
      if (OldTimeLitleRBra < TimeLitleRBra) {
        TwoClickLitleRBra();
      } else if (OldTimeLitleRBra == TimeLitleRBra) {
        OneClickLitleRBra();
      }
      StopTimeLitleRBra = false;
    }
  }
  void clickLitleRoom() {
    if (millis() - TimeClickSwitchRoom <= 3000) {
      if (StateSwitchRoom == 0) {
        StateSwitchRoom = 1;
        OnLitleRoomLight1 = true;
      } else if (StateSwitchRoom == 1) {
        StateSwitchRoom = 2;
        OnLitleRoomLight1 = false;
        OnLitleRoomLight2 = true;
      } else if (StateSwitchRoom == 2) {
        StateSwitchRoom = 3;
        OnLitleRoomLight1 = true;
        OnLitleRoomLight2 = true;
      } else {
        StateSwitchRoom = 0;
        OnLitleRoomLight1 = false;
        OnLitleRoomLight2 = false;
      }
    } else {
      StateSwitchRoom = 0;
      OnLitleRoomLight1 = false;
      OnLitleRoomLight2 = false;
      OnLitleBraLRLight3 = false;
    }
    TimeClickSwitchRoom = millis();
  }
  void ClickLitleRBra() {
    if (StopTimeLitleRBra) {
      Serial.println("clicks");
      TimeLitleRBra = millis();
    }
    if (!StopTimeLitleRBra) {
      OldTimeLitleRBra = millis();
      TimeLitleRBra = OldTimeLitleRBra;
      StopTimeLitleRBra = true;
    }
  }
  void OneClickLitleRBra() {
    if (!ControlLittleRoom) {
      if (millis() - TimeClickLitleBraLRLight3 <= 3000) {
        if (StateLitleBraLRLight3 == 0) {
          StateLitleBraLRLight3 = 1;
          OnLitleBraLRLight3 = true;
        } else {
          StateLitleBraLRLight3 = 0;
          OnLitleBraLRLight3 = false;
        }
      } else {
        StateLitleBraLRLight3 = 0;
        OnLitleBraLRLight3 = false;
      }
      TimeClickLitleBraLRLight3 = millis();
    } else {
      clickLitleRoom();
    }
  }
  void TwoClickLitleRBra() {
    ControlLittleRoom = !ControlLittleRoom;
    if (ControlLittleRoom) {
      TimerControlState.on();
    } else {
      TimerControlState.stop();
    }
  }
  void Off_or_ONRoom() {
    if (OnLitleRoomLight1 || OnLitleRoomLight2 || OnLitleBraLRLight3) {
      OnLitleRoomLight1 = false;
      OnLitleRoomLight2 = false;
      OnLitleBraLRLight3 = false;
      StateSwitchRoom = 0;  //возможно надо доб в цикл ветвления
      StateLitleBraLRLight3 = 0;
    } else if (!OnLitleRoomLight1 && !OnLitleRoomLight2 && !OnLitleBraLRLight3) {
      OnLitleRoomLight1 = true;
      OnLitleRoomLight2 = true;
      OnLitleBraLRLight3 = true;
      StateSwitchRoom = 3;
      StateLitleBraLRLight3 = 1;
    }
  }

private:
  bool StopTimeLitleRBra;
  long OldTimeLitleRBra, TimeLitleRBra;
  bool ControlLittleRoom;
  bool OnLitleRoomLight1, OnLitleRoomLight2, OnLitleBraLRLight3;
  long TimeClickSwitchRoom, TimeClickLitleBraLRLight3;
  int StateSwitchRoom, StateLitleBraLRLight3;
};