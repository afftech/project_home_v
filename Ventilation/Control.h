#include "Fun.h"
Fun FanKitchen(FanKitchen1, FanKitchen2, FanKitchen3, FanKitchen4, 0, 0);
Fun FanBathroom(FanBathroom1, FanBathroom2, FanBathroom3, FanBathroom4, 5, 10);
Fun FanToilet(FanToilet1, FanToilet2, FanToilet3, FanToilet4, 5, 10);
class Control {
public:
  void RangeHood(bool RangeHoodspeed1, bool RangeHoodspeed2, bool RangeHoodspeed3) {
    if (!RangeHoodspeed1 && !RangeHoodspeed2 && !RangeHoodspeed3) {
      Flag1 = false;
      Flag2 = false;
      Flag3 = false;
      Flag_rangeHoodspeed = 0;
    }
    if (RangeHoodspeed1 && !Flag1) {
      FanKitchen.Speed(RangeHood_Slave[0][0]);
      KitchenCurrentSpeed = RangeHood_Slave[0][0];
      FanBathroom.Speed(RangeHood_Slave[0][1]);
      BathroomCurrentSpeed = RangeHood_Slave[0][1];
      FanToilet.Speed(RangeHood_Slave[0][2]);
      ToileCurrentSpeed = RangeHood_Slave[0][2];
      Flag_rangeHoodspeed = 1;
      Flag1 = true;
      Flag2 = false;
      Flag3 = false;
    }
    if (RangeHoodspeed2 && !Flag2) {
      FanKitchen.Speed(RangeHood_Slave[1][0]);
      KitchenCurrentSpeed = RangeHood_Slave[1][0];
      FanBathroom.Speed(RangeHood_Slave[1][1]);
      BathroomCurrentSpeed = RangeHood_Slave[1][1];
      FanToilet.Speed(RangeHood_Slave[1][2]);
      ToileCurrentSpeed = RangeHood_Slave[1][2];
      Flag_rangeHoodspeed = 2;
      Flag1 = false;
      Flag2 = true;
      Flag3 = false;
    }
    if (RangeHoodspeed3 && !Flag3) {
      FanKitchen.Speed(RangeHood_Slave[2][0]);
      KitchenCurrentSpeed = RangeHood_Slave[0][0];
      FanBathroom.Speed(RangeHood_Slave[2][1]);
      BathroomCurrentSpeed = RangeHood_Slave[0][1];
      FanToilet.Speed(RangeHood_Slave[2][2]);
      ToileCurrentSpeed = RangeHood_Slave[0][2];
      Flag_rangeHoodspeed = 3;
      Flag1 = false;
      Flag2 = false;
      Flag3 = true;
    }
  }

  void KitchenFan() {
    KitchenCurrentSpeed++;
    if (KitchenCurrentSpeed > 4) {
      if (Flag_rangeHoodspeed == 0) {
        KitchenCurrentSpeed = 0;
      } else {
        KitchenCurrentSpeed = RangeHood_Slave[Flag_rangeHoodspeed - 1][0];
      }
    }
  }
  void BathroomFan() {
  }
  void ToileFan() {
  }
private:
  bool Flag1, Flag2, Flag3;
  int Flag_rangeHoodspeed;
  int KitchenCurrentSpeed, BathroomCurrentSpeed, ToileCurrentSpeed;
  int OldSpeedKitchen;
};