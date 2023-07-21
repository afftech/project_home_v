#include "HardwareSerial.h"
#include "Fun.h"

Fun FanKitchen(FanKitchen1, FanKitchen2, FanKitchen3, FanKitchen4, 1, 2, 3);
Fun FanBathroom(FanBathroom1, FanBathroom2, FanBathroom3, FanBathroom4, 1, 2, 3);
Fun FanToilet(FanToilet1, FanToilet2, FanToilet3, FanToilet4, 1, 2, 3);
class Control {
public:
  void RangeHood(bool RangeHoodspeed1, bool RangeHoodspeed2, bool RangeHoodspeed3) {
    FanKitchen.run(false);
    if (!RangeHoodspeed1 && !RangeHoodspeed2 && !RangeHoodspeed3 && Flag_rangeHoodspeed != 3) {
      Flag1 = false;
      Flag2 = false;
      Flag3 = false;
      Flag_rangeHoodspeed = 3;  //состояние 3 при котором все выключено
                                /*скорость 0*/
      if (!ManualFlag1) {       //передаём параметры для кухки если ручн. р. не активен
        KitchenCurrentSpeed = 0;
        KitchenRunAuto(KitchenCurrentSpeed);
      }
    }
    /*скорость 1*/
    if (RangeHoodspeed1 && !Flag1) {
      if (ManualFlag1) {  //передаём параметры для кухки если ручн. р. не активен
        if (KitchenCurrentSpeed < RangeHood_Slave[0][0]) {
          KitchenCurrentSpeed = RangeHood_Slave[0][0];
          KitchenRunAuto(KitchenCurrentSpeed);
        }
      } else {
        KitchenCurrentSpeed = RangeHood_Slave[0][0];
        KitchenRunAuto(KitchenCurrentSpeed);
      }
      Flag_rangeHoodspeed = 0;
      Flag1 = true;
      Flag2 = false;
      Flag3 = false;
    }
    /*скорость 2*/
    if (RangeHoodspeed2 && !Flag2) {
      KitchenCurrentSpeed = RangeHood_Slave[1][0];
      KitchenRunAuto(KitchenCurrentSpeed);

      Flag_rangeHoodspeed = 1;
      Flag1 = false;
      Flag2 = true;
      Flag3 = false;
    }
    /*скорость 3*/
    if (RangeHoodspeed3 && !Flag3) {
      KitchenCurrentSpeed = RangeHood_Slave[2][0];
      KitchenRunAuto(KitchenCurrentSpeed);

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
    KitchenRunManual(KitchenCurrentSpeed);
  }

  void KitchenRunManual(int i) {
    FanKitchen.Speed(i, 0);
  }
  void KitchenRunAuto(int i) {
    FanKitchen.Speed(i, 1);
  }

private:
  bool Flag1, Flag2, Flag3;
  bool ManualFlag1, ManualFlag2, ManualFlag3;
  int Flag_rangeHoodspeed;
  int KitchenCurrentSpeed, BathroomCurrentSpeed, ToileCurrentSpeed;
  int OldSpeedKitchen;
};