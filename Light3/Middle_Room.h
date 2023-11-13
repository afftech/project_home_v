class Middle_Room {
#include "TimerOff.h"
  Timer TimerControlState{ TimeOffDT };
public:
  void run() {
    TimerControlState.run();
    if (TimerControlState.resp()) {
      ControlMiddleRoom = false;
    }
    if (OnMiddleRoomLight1) {
      digitalWrite(MiddleRoomLight1, 1);
    } else {
      digitalWrite(MiddleRoomLight1, 0);
    }
    if (OnMiddleRoomLight2) {
      digitalWrite(MiddleRoomLight2, 1);
    } else {
      digitalWrite(MiddleRoomLight2, 0);
    }
    /*if (OnMiddleRoomLight3) {
      digitalWrite(MiddleRoomLight3, 1);
    } else {
      digitalWrite(MiddleRoomLight3, 0);
    }*/
    if (OnMiddleRoomBra) {
      digitalWrite(MiddleRoomBra, 1);
    } else {
      digitalWrite(MiddleRoomBra, 0);
    }
    if (!StateSwitchRoom) {
      TimeClickSwitchRoom = millis();
    }
    if (!StateBra) {
      TimeClickMiddleRoomBra = millis();
    }
    if (StopTimeMiddleRoomBra && OldMiddleRoomBra + 300 <= millis()) {
      if (OldMiddleRoomBra < TimeMiddleRoomBra) {
        TwoClickBra();
      } else if (OldMiddleRoomBra == TimeMiddleRoomBra) {
        OneClickBra();
      }
      StopTimeMiddleRoomBra = false;
    }
  }
  void clickRoom() {
    if (millis() - TimeClickSwitchRoom <= 3000) {
      if (StateSwitchRoom == 0) {
        StateSwitchRoom = 1;
        OnMiddleRoomLight1 = true;
      } else if (StateSwitchRoom == 1) {
        StateSwitchRoom = 2;
        OnMiddleRoomLight1 = false;
        OnMiddleRoomLight2 = true;
      } else if (StateSwitchRoom == 2) {
        StateSwitchRoom = 3;
        OnMiddleRoomLight1 = true;
        OnMiddleRoomLight2 = true;
        //OnMiddleRoomLight3 = true;
      } else {
        StateSwitchRoom = 0;
        OnMiddleRoomLight1 = false;
        OnMiddleRoomLight2 = false;
        //OnMiddleRoomLight3 = false;
      }
    } else {
      StateSwitchRoom = 0;
      OnMiddleRoomLight1 = false;
      OnMiddleRoomLight2 = false;
      //OnMiddleRoomLight3 = false;
    }
    TimeClickSwitchRoom = millis();
  }
  void ClickBra() {
    if (StopTimeMiddleRoomBra) {
      Serial.println("clicks");
      TimeMiddleRoomBra = millis();
    }
    if (!StopTimeMiddleRoomBra) {
      OldMiddleRoomBra = millis();
      TimeMiddleRoomBra = OldMiddleRoomBra;
      StopTimeMiddleRoomBra = true;
    }
  }
  void OneClickBra() {
    if (!ControlMiddleRoom) {
      if (millis() - TimeClickMiddleRoomBra <= 3000) {
        if (StateBra == 0) {
          StateBra = 1;
          OnMiddleRoomBra = true;
        } else {
          StateBra = 0;
          OnMiddleRoomBra = false;
        }
      } else {
        StateBra = 0;
        OnMiddleRoomBra = false;
      }
      TimeClickMiddleRoomBra = millis();
    } else {
      clickRoom();
    }
  }
  void TwoClickBra() {
    ControlMiddleRoom = !ControlMiddleRoom;
    if (ControlMiddleRoom) {
      TimerControlState.on();
    } else {
      TimerControlState.stop();
    }
  }
  void Off_or_ONRoom() {
    if (OnMiddleRoomLight1 || OnMiddleRoomLight2 || OnMiddleRoomBra) {
      OnMiddleRoomLight1 = false;
      OnMiddleRoomLight2 = false;
      //OnMiddleRoomLight3 = false;
      OnMiddleRoomBra = false;
    } else if (!OnMiddleRoomLight1 && !OnMiddleRoomLight2 && !OnMiddleRoomBra) {
      OnMiddleRoomLight1 = true;
      OnMiddleRoomLight2 = true;
      //OnMiddleRoomLight3 = false;
      OnMiddleRoomBra = true;
    }
    StateSwitchRoom = 0;
    StateBra = 0;
  }
private:
  bool StopTimeMiddleRoomBra;
  long OldMiddleRoomBra, TimeMiddleRoomBra;
  bool ControlMiddleRoom;
  bool OnMiddleRoomLight1, OnMiddleRoomLight2, /* OnMiddleRoomLight3,*/ OnMiddleRoomBra;
  long TimeClickSwitchRoom, TimeClickMiddleRoomBra;
  int StateSwitchRoom, StateBra;
};