#include "Arduino.h"
#include "HardwareSerial.h"

class Room {
public:
  void run() {
    if (OnRibbonP) {
      digitalWrite(RibbonP, 1);
    } else {
      digitalWrite(RibbonP, 0);
    }
    if (OnRibbonBed) {
      digitalWrite(RibbonBed, 1);
    } else {
      digitalWrite(RibbonBed, 0);
    }
    if (OnRibbonWDimly) {
      digitalWrite(RibbonWDimly, 1);
    } else {
      digitalWrite(RibbonWDimly, 0);
    }
    if (OnRibbonWBrightly) {
      digitalWrite(RibbonWBrightly, 1);
    } else {
      digitalWrite(RibbonWBrightly, 0);
    }
    if (OnEdge) {
      digitalWrite(Edge, 1);
    } else {
      digitalWrite(Edge, 0);
    }
    if (OnCentre) {
      digitalWrite(Centre, 1);
    } else {
      digitalWrite(Centre, 0);
    }
    if (OnBraLBed) {
      digitalWrite(BraLBed, 1);
    } else {
      digitalWrite(BraLBed, 0);
    }
    if (OnBraRBed) {
      digitalWrite(BraRBed, 1);
    } else {
      digitalWrite(BraRBed, 0);
    }
    if (OnBraTape) {
      digitalWrite(BraTape, 1);
    } else {
      digitalWrite(BraTape, 0);
    }
    if (StopTime && OldTimeMainSwitch + 300 <= millis()) {  //гл выкл
      if (OldTimeMainSwitch < TimeMainSwitch) {
        clickMainSwitchTwo();
      } else if (OldTimeMainSwitch == TimeMainSwitch) {
        clickMainSwitchOne();
      }
      StopTime = false;
    }
    if (!StateMainSwitch) {
      TimeClickMainSwitch = millis();
    }
    if (StopTimeBraL && OldTimeBraLSwitch + 300 <= millis()) {  // Бра
      if (OldTimeBraLSwitch < TimeBraLSwitch) {
        clickBraLSwitchTwo();
      } else if (OldTimeBraLSwitch == TimeBraLSwitch) {
        clickBraLSwitchOne();
      }
      StopTimeBraL = false;
    }
    if (!StateBraLSwitch) {
      TimeClickBraLSwitch = millis();
    }
    if (StopTimeBraR && OldTimeBraRSwitch + 300 <= millis()) {  // Стол
      if (OldTimeBraRSwitch < TimeBraRSwitch) {
        clickBraRSwitchTwo();
      } else if (OldTimeBraRSwitch == TimeBraRSwitch) {
        clickBraRSwitchOne();
      }
      StopTimeBraR = false;
    }
    if (!StateBraRSwitch) {
      TimeClickBraRSwitch = millis();
    }
    if (StopTimeBraT && OldTimeBraTSwitch + 300 <= millis()) {  // Бра Стол
      if (OldTimeBraTSwitch < TimeBraTSwitch) {
        clickBraTSwitchTwo();
      } else if (OldTimeBraTSwitch == TimeBraTSwitch) {
        clickBraTSwitchOne();
      }
      StopTimeBraT = false;
    }
    if (StopTimeRibbon && OldTimeRibbonSwitch + 300 <= millis()) {  // Лента
      if (OldTimeRibbonSwitch < TimeRibbonSwitch) {
        clickRibbonSwitchTwo();
      } else if (OldTimeRibbonSwitch == TimeRibbonSwitch) {
        clickRibbonSwitchOne();
      }
      StopTimeRibbon = false;
    }
    if (!StateRibbonSwitch) {
      TimeClickRibbonSwitch = millis();
    }
  }
  void clickMainSwitchTwo() {
    Serial.println("Two clicks.");
    OnCentre = !OnCentre;
  }
  void clickMainSwitchOne() {
    Serial.println("One Click");
    if (millis() - TimeClickMainSwitch <= 3000) {
      if (StateMainSwitch == 0) {
        StateMainSwitch = 1;
        Switch1();
      } else if (StateMainSwitch == 1) {
        StateMainSwitch = 2;
        Switch2();
      } else if (StateMainSwitch == 2) {
        StateMainSwitch = 3;
        Switch3();
      } else {
        StateMainSwitch = 0;
        OffRoom();
      }
    } else {
      StateMainSwitch = 0;
      OffRoom();
    }
    TimeClickMainSwitch = millis();
  }
  void Switch1() {
    OnRibbonWDimly = true;
    OnEdge = true;
  }
  void Switch2() {
    OnCentre = true;
  }
  void Switch3() {
    OnRibbonP = true;
    OnRibbonBed = true;

    OnRibbonWDimly = false;
    OnRibbonWBrightly = true;
  }
  void clickMainSwitch() {
    if (StopTime) {
      Serial.println("clicks");
      TimeMainSwitch = millis();
    }
    if (!StopTime) {
      OldTimeMainSwitch = millis();
      TimeMainSwitch = OldTimeMainSwitch;
      StopTime = true;
    }
  }
  /******************************************/
  void clickBraLSwitch() {
    if (StopTimeBraL) {
      Serial.println(" clicks Bra");
      TimeBraLSwitch = millis();
    }
    if (!StopTimeBraL) {
      OldTimeBraLSwitch = millis();
      TimeBraLSwitch = OldTimeBraLSwitch;
      StopTimeBraL = true;
    }
  }
  void clickBraLSwitchTwo() {
    OnBraRBed = true;
    OnBraLBed = true;
  }
  void clickBraLSwitchOne() {
    if (millis() - TimeClickBraLSwitch <= 3000) {
      if (StateBraLSwitch == 0) {
        StateBraLSwitch = 1;
        OnBraLBed = true;
      } else if (StateBraLSwitch == 1) {
        StateBraLSwitch = 2;
        OnBraLBed = false;
        OnBraRBed = true;
      } else {
        StateBraLSwitch = 0;
        OnBraRBed = false;
        OnBraLBed = false;
      }
    } else {
      StateBraLSwitch = 0;
      OnBraRBed = false;
      OnBraLBed = false;
    }
    TimeClickBraLSwitch = millis();
  } /******************************************/
  void clickBraRSwitch() {
    if (StopTimeBraR) {
      Serial.println(" clicks BraR");
      TimeBraRSwitch = millis();
    }
    if (!StopTimeBraR) {
      OldTimeBraRSwitch = millis();
      TimeBraRSwitch = OldTimeBraRSwitch;
      StopTimeBraR = true;
    }
  }
  void clickBraRSwitchTwo() {
    OnBraRBed = true;
    OnBraLBed = true;
  }
  void clickBraRSwitchOne() {
    if (millis() - TimeClickBraRSwitch <= 3000) {
      if (StateBraRSwitch == 0) {
        StateBraRSwitch = 1;
        OnBraRBed = true;
      } else if (StateBraRSwitch == 1) {
        StateBraRSwitch = 2;
        OnBraRBed = false;
        OnBraLBed = true;
      } else {
        StateBraRSwitch = 0;
        OnBraRBed = false;
        OnBraLBed = false;
      }
    } else {
      StateBraRSwitch = 0;
      OnBraRBed = false;
      OnBraLBed = false;
    }
    TimeClickBraRSwitch = millis();
  }
  /******************************************/
  void clickBraTSwitch() {
    if (StopTimeBraT) {
      Serial.println(" clicks BraT");
      TimeBraTSwitch = millis();
    }
    if (!StopTimeBraT) {
      OldTimeBraTSwitch = millis();
      TimeBraTSwitch = OldTimeBraTSwitch;
      StopTimeBraT = true;
    }
  }
  void clickBraTSwitchTwo() {
    OnRibbonP = !OnRibbonP;
  }
  void clickBraTSwitchOne() {
    OnBraTape = !OnBraTape;
  }
  void clickRibbonSwitch() {
    if (StopTimeRibbon) {
      Serial.println(" clicks Ribbon");
      TimeRibbonSwitch = millis();
    }
    if (!StopTimeRibbon) {
      OldTimeRibbonSwitch = millis();
      TimeRibbonSwitch = OldTimeRibbonSwitch;
      StopTimeRibbon = true;
    }
  }
  void clickRibbonSwitchTwo() {
    OnRibbonWDimly = !OnRibbonWDimly;
  }
  void clickRibbonSwitchOne() {
    Serial.println("One Click");
    if (millis() - TimeClickRibbonSwitch <= 3000) {
      if (StateRibbonSwitch == 0) {
        StateRibbonSwitch = 1;
        OnRibbonBed = true;
      } else if (StateRibbonSwitch == 1) {
        StateRibbonSwitch = 2;
        OnRibbonP = true;
      } else if (StateRibbonSwitch == 2) {
        StateRibbonSwitch = 3;
        OnRibbonWBrightly = true;
      } else {
        StateRibbonSwitch = 0;
        OnRibbonBed = false;
        OnRibbonP = false;
        OnRibbonWBrightly = false;
      }
    } else {
      StateRibbonSwitch = 0;
      OnRibbonBed = false;
      OnRibbonP = false;
      OnRibbonWBrightly = false;
    }
    TimeClickMainSwitch = millis();
  }
  void OffRoom() {
    OnRibbonWDimly = false;     //4
    OnEdge = false;             //7
    OnCentre = false;           //8
    OnRibbonP = false;          //2
    OnRibbonBed = false;        //3
    OnRibbonWBrightly = false;  //5
    StateMainSwitch = 0;
  }
  void OffMainRoom() {
    OnRibbonWDimly = false;     //4
    OnEdge = false;             //7
    OnCentre = false;           //8
    OnRibbonP = false;          //2
    OnRibbonBed = false;        //3
    OnRibbonWBrightly = false;  //5
    OnBraLBed = false;          //9
    OnBraRBed = false;          //10
    OnBraTape = false;          //11
    StateMainSwitch = 0;
    StateBraLSwitch = 0;
    StateBraRSwitch = 0;
    StateRibbonSwitch = 0;
  }
private:
  bool OnRibbonP, OnRibbonBed, OnRibbonWDimly, OnRibbonWBrightly, OnEdge, OnCentre, OnBraLBed, OnBraRBed, OnBraTape;
  bool StopTimeBraL, StopTime, StopTimeBraR, StopTimeBraT, StopTimeRibbon;
  long OldTimeMainSwitch, TimeMainSwitch, TimeClickMainSwitch;
  long TimeBraLSwitch, OldTimeBraLSwitch, TimeClickBraLSwitch;
  long TimeBraRSwitch, OldTimeBraRSwitch, TimeClickBraRSwitch;
  long TimeBraTSwitch, OldTimeBraTSwitch;
  long TimeRibbonSwitch, OldTimeRibbonSwitch, TimeClickRibbonSwitch;
  int StateMainSwitch, StateBraLSwitch, StateBraRSwitch, StateRibbonSwitch;
};