#include "HardwareSerial.h"
#include "Fun.h"

Fun FanKitchen(FanKitchen1, FanKitchen2, FanKitchen3,'!', FanKitchen4, 0, 0);
Fun FanBathroom(FanBathroom1, FanBathroom2, FanBathroom3, FanBathroom4, 5, 10);
Fun FanToilet(FanToilet1, FanToilet2, FanToilet3, FanToilet4, 5, 10);
class Control {
public:
  void RangeHood(bool RangeHoodspeed1, bool RangeHoodspeed2, bool RangeHoodspeed3) {
    if (!RangeHoodspeed1 && !RangeHoodspeed2 && !RangeHoodspeed3 && Flag_rangeHoodspeed != 3) {
      Flag1 = false;
      Flag2 = false;
      Flag3 = false;
      Flag_rangeHoodspeed = 3;  //состояние 3 при котором все выключено

      if (!ManualFlag1) {  //передаём параметры для кухки если ручн. р. не активен
        KitchenCurrentSpeed = 0;
        KitchenRun(KitchenCurrentSpeed);
      }
    }
    /*скорость 1*/
    if (RangeHoodspeed1 && !Flag1) {
      KitchenCurrentSpeed = RangeHood_Slave[0][0];
      KitchenRun(KitchenCurrentSpeed);
      //////////
      FanBathroom.Speed(RangeHood_Slave[0][1]);
      BathroomCurrentSpeed = RangeHood_Slave[0][1];

      FanToilet.Speed(RangeHood_Slave[0][2]);
      ToileCurrentSpeed = RangeHood_Slave[0][2];
      //Serial.println(OldSpeed);
      Flag_rangeHoodspeed = 0;
      Flag1 = true;
      Flag2 = false;
      Flag3 = false;
    }
    /*скорость 2*/
    if (RangeHoodspeed2 && !Flag2) {
      KitchenCurrentSpeed = RangeHood_Slave[1][0];
      KitchenRun(KitchenCurrentSpeed);
      //////////
      FanBathroom.Speed(RangeHood_Slave[1][1]);
      BathroomCurrentSpeed = RangeHood_Slave[1][1];

      FanToilet.Speed(RangeHood_Slave[1][2]);
      ToileCurrentSpeed = RangeHood_Slave[1][2];

      Flag_rangeHoodspeed = 1;
      Flag1 = false;
      Flag2 = true;
      Flag3 = false;
    }
    /*if(!RangeHoodspeed2){
      Flag2 = false;
      ToileCurrentSpeed =  0;
      FanBathroom.Speed(0);
    }*/

    /*скорость 3*/
    if (RangeHoodspeed3 && !Flag3) {
      KitchenCurrentSpeed = RangeHood_Slave[2][0];
      KitchenRun(KitchenCurrentSpeed);
      ///////
      FanBathroom.Speed(RangeHood_Slave[2][1]);
      BathroomCurrentSpeed = RangeHood_Slave[2][1];

      FanToilet.Speed(RangeHood_Slave[2][2]);
      ToileCurrentSpeed = RangeHood_Slave[2][2];

      Flag_rangeHoodspeed = 2;
      Flag1 = false;
      Flag2 = false;
      Flag3 = true;
    }
  }

  void KitchenFan(bool click) {
    ManualFlag1 = true;  //флаг ручнгого вкл
    if (click) {
      KitchenCurrentSpeed++;
      if (Flag_rangeHoodspeed != 3) {  //активированна ли вытяжка?
        if (KitchenCurrentSpeed > 4) {
          KitchenCurrentSpeed = RangeHood_Slave[Flag_rangeHoodspeed][0];
        }
      } else {
        if (KitchenCurrentSpeed > 4) {
          KitchenCurrentSpeed = 0;
          ManualFlag1 = false;  //флаг ручнгого выкл
        }
      }
    }
    //Serial.println(KitchenCurrentSpeed);
    KitchenRun(KitchenCurrentSpeed);
  }

  void KitchenRun(int i) {
    FanKitchen.Speed(i);
  }
  /*void BathroomFan(bool click) {
    if (click) {
      BathroomCurrentSpeed++;
      if (Flag_rangeHoodspeed != 3) {  //
        if (BathroomCurrentSpeed > 4) {
          BathroomCurrentSpeed = RangeHood_Slave[Flag_rangeHoodspeed][0];
        }
      } else {
        if (BathroomCurrentSpeed > 4) {
          BathroomCurrentSpeed = 0;
        }
      }
    }
    //Serial.println(BathroomCurrentSpeed);
    BathroomRun(BathroomCurrentSpeed);
  }
  void BathroomRun(int i) {
    FanBathroom.Speed(i);
  }
  void ToileFan(bool click) {
    if (click) {
      ToileCurrentSpeed++;
      if (Flag_rangeHoodspeed != 3) {  //
        if (ToileCurrentSpeed > 4) {
          ToileCurrentSpeed = RangeHood_Slave[Flag_rangeHoodspeed][0];
        }
      } else {
        if (ToileCurrentSpeed > 4) {
          ToileCurrentSpeed = 0;
        }
      }
    }
    //Serial.println(ToileCurrentSpeed);
    ToileRun(ToileCurrentSpeed);
  }
  void ToileRun(int i) {
    FanToilet.Speed(i);
  }*/
private:
  bool Flag1, Flag2, Flag3;
  bool ManualFlag1, ManualFlag2, ManualFlag3;
  int Flag_rangeHoodspeed;
  int KitchenCurrentSpeed, BathroomCurrentSpeed, ToileCurrentSpeed;
  int OldSpeedKitchen;
};