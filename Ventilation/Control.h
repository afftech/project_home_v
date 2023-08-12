#include "HardwareSerial.h"

class Control {
public:
  void RangeHood(bool RangeHoodspeed1, bool RangeHoodspeed2, bool RangeHoodspeed3) {
    {  //передача сигнала включенного света
      FanKitchen.run(true);
      FanBathroom.run(BtnGroup3.click2());
      FanToilet.run(BtnGroup4.click2());
    }
    {
      if (FanKitchen.reset(false)) {  //сброс счетчика скорости кухни
        KitchenCurrentSpeed = 0;
      }
      if (FanBathroom.reset(false)) {  //сброс счетчика скорости ванной
        BathroomCurrentSpeed = 0;
      }
      if (FanToilet.reset(false)) {  //сброс счетчика скорости туалета
        ToiletCurrentSpeed = 0;
      }
    }
    if (!RangeHoodspeed1 && !RangeHoodspeed2 && !RangeHoodspeed3 && Flag_rangeHoodspeed != 3) {
      /*общие флаги*/
      Flag1 = false;
      Flag2 = false;
      Flag3 = false;
      Flag_rangeHoodspeed = 3;  //состояние 3 при котором все выключено
                                /*скорость 0*/
      /*управление кухней*/
      KitchenRunAuto(0);
      KitchenCurrentSpeed = FanKitchen.reset(true);
      /*управление Ванной*/
      BathroomRunAuto(0);
      BathroomCurrentSpeed = FanBathroom.reset(true);
      /*управление Туалетом*/
      ToiletRunAuto(0);
      ToiletCurrentSpeed = FanToilet.reset(true);
    }
    /*скорость 1*/
    if (RangeHoodspeed1 && !Flag1) {
      /*управление кухней*/
      //KitchenCurrentSpeed = RangeHood_Slave[0][0];
      KitchenRunAuto(RangeHood_Slave[0][0]);
      KitchenCurrentSpeed = RangeHood_Slave[0][0];
      /*управление ванной*/
      BathroomRunAuto(RangeHood_Slave[0][1]);

      /*управление Туалетом*/
      ToiletRunAuto(RangeHood_Slave[0][2]);

      /*общие флаги*/
      Flag_rangeHoodspeed = 0;
      Flag1 = true;
      Flag2 = false;
      Flag3 = false;
    }

    /*скорость 2*/
    if (RangeHoodspeed2 && !Flag2) {
      /*управление кухней*/
      KitchenRunAuto(RangeHood_Slave[1][0]);
      KitchenCurrentSpeed = RangeHood_Slave[1][0];
      /*управление ванной*/
      BathroomRunAuto(RangeHood_Slave[1][1]);

      /*управление Туалетом*/
      ToiletRunAuto(RangeHood_Slave[1][2]);

      /*общие флаги*/
      Flag_rangeHoodspeed = 1;
      Flag1 = false;
      Flag2 = true;
      Flag3 = false;
    }

    /*скорость 3*/
    if (RangeHoodspeed3 && !Flag3) {
      /*управление кухней*/
      KitchenRunAuto(RangeHood_Slave[2][0]);
      KitchenCurrentSpeed = RangeHood_Slave[2][0];
      /*управление Ванной*/
      BathroomRunAuto(RangeHood_Slave[2][1]);

      /*управление Туалетом*/
      ToiletRunAuto(RangeHood_Slave[2][2]);

      /*общие флаги*/
      Flag_rangeHoodspeed = 2;
      Flag1 = false;
      Flag2 = false;
      Flag3 = true;
    }
  }
  /*все что касается кухни*/
  void KitchenFan(bool click) {
    if (click) {
      if (Flag_rangeHoodspeed != 3) {  //Если вытяжка включена то выставляем правильную скорость
        if (KitchenCurrentSpeed < RangeHood_Slave[Flag_rangeHoodspeed][0]) {
          KitchenCurrentSpeed = RangeHood_Slave[Flag_rangeHoodspeed][0];
        }
        KitchenCurrentSpeed++;
        if (KitchenCurrentSpeed > 4) {
          KitchenCurrentSpeed = RangeHood_Slave[Flag_rangeHoodspeed][0];
        }
      } else {
        KitchenCurrentSpeed++;
        if (KitchenCurrentSpeed > 4) {
          KitchenCurrentSpeed = 0;
        }
      }
    } else {
      KitchenCurrentSpeed = 0;
      KitchenRunAuto(RangeHood_Slave[Flag_rangeHoodspeed][0]);
    }
    KitchenRunManual(KitchenCurrentSpeed);
  }
  void
  KitchenRunManual(int i) {
    Serial.print("KitchenRunManual Speed:");
    Serial.println(i);
    FanKitchen.Speed(i, 0);
  }
  void KitchenRunAuto(int i) {
    Serial.print("KitchenRunAuto Speed:");
    Serial.println(i);
    FanKitchen.Speed(i, 1);
  }
  /*==все что касается кухни==*/

  /*все что касается ванной*/
  void BathroomFan(bool click) {
    if (click) {
      if (Flag_rangeHoodspeed != 3) {  //активированна ли вытяжка?
        if (BathroomCurrentSpeed < RangeHood_Slave[Flag_rangeHoodspeed][1]) {
          BathroomCurrentSpeed = RangeHood_Slave[Flag_rangeHoodspeed][1];
        }
        BathroomCurrentSpeed++;
        if (BathroomCurrentSpeed > 4) {
          BathroomCurrentSpeed = RangeHood_Slave[Flag_rangeHoodspeed][1];
        }
      } else {
        BathroomCurrentSpeed++;
        if (BathroomCurrentSpeed > 4) {
          BathroomCurrentSpeed = 0;
        }
      }
    } else {
      BathroomCurrentSpeed = 0;
      BathroomRunAuto(RangeHood_Slave[Flag_rangeHoodspeed][1]);
    }
    BathroomRunManual(BathroomCurrentSpeed);
  }

  void BathroomRunManual(int i) {
    Serial.print("BathroomRunManual Speed:");
    Serial.println(i);
    FanBathroom.Speed(i, 0);
  }
  void BathroomRunAuto(int i) {
    Serial.print("BathroomRunAuto Speed:");
    Serial.println(i);
    FanBathroom.Speed(i, 1);
  }
  /*==все что касается ванной==*/


  /*все что касается ванной*/
  void ToiletFan(bool click) {
    if (click) {
      if (Flag_rangeHoodspeed != 3) {  //активированна ли вытяжка?
        if (ToiletCurrentSpeed < RangeHood_Slave[Flag_rangeHoodspeed][2]) {
          ToiletCurrentSpeed = RangeHood_Slave[Flag_rangeHoodspeed][2];
        }
        ToiletCurrentSpeed++;
        if (ToiletCurrentSpeed > 4) {
          ToiletCurrentSpeed = RangeHood_Slave[Flag_rangeHoodspeed][2];
        }
      } else {
        ToiletCurrentSpeed++;
        if (ToiletCurrentSpeed > 4) {
          ToiletCurrentSpeed = 0;
        }
      }
    } else {
      ToiletCurrentSpeed = 0;
      ToiletRunAuto(RangeHood_Slave[Flag_rangeHoodspeed][2]);
    }
    ToiletRunManual(ToiletCurrentSpeed);
  }

  void ToiletRunManual(int i) {
    Serial.print("ToiletRunManual Speed:");
    Serial.println(i);
    FanToilet.Speed(i, 0);
  }
  void ToiletRunAuto(int i) {
    /*Serial.print("ToiletRunAuto Speed:");
    Serial.println(i);*/
    FanToilet.Speed(i, 1);
  }
  /*==все что касается ванной==*/
private:
  bool Flag1, Flag2, Flag3;
  //bool ManualFlag1, ManualFlag2, ManualFlag3;
  int Flag_rangeHoodspeed;
  int KitchenCurrentSpeed, BathroomCurrentSpeed, ToiletCurrentSpeed;
  int OldSpeedKitchen;
};