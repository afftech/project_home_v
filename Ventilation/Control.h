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
      Flag_rangeHoodspeed = 3;  //состояние 3 при котором все выключено
    }
    if (RangeHoodspeed1 && !Flag1) {
      KitchenCurrentSpeed = RangeHood_Slave[0][0];
      KitchenRun(KitchenCurrentSpeed);
      //////////
      FanBathroom.Speed(RangeHood_Slave[0][1]);
      BathroomCurrentSpeed = RangeHood_Slave[0][1];

      FanToilet.Speed(RangeHood_Slave[0][2]);
      ToileCurrentSpeed = RangeHood_Slave[0][2];

      Flag_rangeHoodspeed = 0;
      Flag1 = true;
      Flag2 = false;
      Flag3 = false;
    }
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
    if (click) {
      KitchenCurrentSpeed++;
      if (KitchenCurrentSpeed > 4) {
        if (Flag_rangeHoodspeed != 3) {  //
          KitchenCurrentSpeed = RangeHood_Slave[Flag_rangeHoodspeed][0];
        } else {
          KitchenCurrentSpeed = 0;
        }
      } else {
        if (Flag_rangeHoodspeed != 3) {
          KitchenCurrentSpeed = RangeHood_Slave[Flag_rangeHoodspeed][0];
        } else {
          KitchenCurrentSpeed = 0;
        }
      }
      KitchenRun(KitchenCurrentSpeed);
    }
    void KitchenRun(int i) {
      FanKitchen.Speed(i);
    }
    void BathroomFan() {
    }
    void BathroomRun(int i) {
    }
    void ToileFan() {
    }
    void ToileRun(int i) {
    }
  private:
    bool Flag1, Flag2, Flag3;
    int Flag_rangeHoodspeed;
    int KitchenCurrentSpeed, BathroomCurrentSpeed, ToileCurrentSpeed;
    int OldSpeedKitchen;
  };