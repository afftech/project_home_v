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
      //Serial.println(DependenceHead);
      if (Flag_rangeHoodspeed != oldFlag_rangeHoodspeed || oldKitchenCurrentSpeed != KitchenCurrentSpeed || oldBathroomCurrentSpeed != BathroomCurrentSpeed || oldToiletCurrentSpeed != ToiletCurrentSpeed) {
        Serial.println("Start");
        oldFlag_rangeHoodspeed = Flag_rangeHoodspeed;
        oldKitchenCurrentSpeed = KitchenCurrentSpeed;
        oldBathroomCurrentSpeed = BathroomCurrentSpeed;
        oldToiletCurrentSpeed = ToiletCurrentSpeed;
        //авто запуск первой скорости зависимостьи одних от других
        if (BathroomCurrentSpeed || ToiletCurrentSpeed) {
          FanKitchen.New_Init_State(1);

        } else {
          FanKitchen.New_Init_State(0);
        }
        if (KitchenCurrentSpeed || ToiletCurrentSpeed) {
          FanBathroom.New_Init_State(1);
          //Serial.println("FanBathroom.New_Init_State(1);");
        } else {
          FanBathroom.New_Init_State(0);
          //Serial.println("FanBathroom.New_Init_State(0);");
        }
        if (KitchenCurrentSpeed || BathroomCurrentSpeed) {
          FanToilet.New_Init_State(1);
        } else {
          FanToilet.New_Init_State(0);
        }
      }
      if (FanKitchen.reset(false)) {
        if (DependenceHead > 0) {
          if (DependenceHead == 1) {  // если кухня главная, то позволяем выключить все авто вкл вентиляторы
            DependenceHead = 0;
            KitchenCurrentSpeed = 0;
            DependenceHead_State(1);
          } else {
            KitchenCurrentSpeed = 0;
          }
        } else {
          KitchenCurrentSpeed = 0;
        }
      }
      if (FanBathroom.reset(false)) {
        if (DependenceHead > 0) {
          if (DependenceHead == 2) {  // если ванная главная, то позволяем выключить все авто вкл вентиляторы
            DependenceHead = 0;
            BathroomCurrentSpeed = 0;
            DependenceHead_State(2);  //это для того что бы сменить главного
          } else {
            BathroomCurrentSpeed = 0;
          }
        } else {
          BathroomCurrentSpeed = 0;
        }
      }
      if (FanToilet.reset(false)) {
        if (DependenceHead > 0) {
          if (DependenceHead == 3) {  // если ванная главная, то позволяем выключить все авто вкл вентиляторы
            DependenceHead = 0;
            ToiletCurrentSpeed = 0;
            DependenceHead_State(3);  //это для того что бы сменить главного
          } else {
            ToiletCurrentSpeed = 0;
          }
        } else {
          ToiletCurrentSpeed = 0;
        }
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
      Serial.println("ERROR");
    }
    /*скорость 1*/
    if (RangeHoodspeed1 && !Flag1) {
      /*управление кухней*/
      //KitchenCurrentSpeed = RangeHood_Slave[0][0];
      KitchenRunAuto(RangeHood_Slave[0][0]);
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
      if (Flag_rangeHoodspeed != 3) {                                         //Если вытяжка включена то выставляем правильную скорость
        if (KitchenCurrentSpeed < RangeHood_Slave[Flag_rangeHoodspeed][0]) {  //если скорость ручного вкл меньше скорости вытяжки
          KitchenCurrentSpeed = RangeHood_Slave[Flag_rangeHoodspeed][0];
        }
        KitchenCurrentSpeed++;
        if (KitchenCurrentSpeed > 4) {
          KitchenCurrentSpeed = RangeHood_Slave[Flag_rangeHoodspeed][0];
        }
      } else {
        if (DependenceHead != 1 && DependenceHead != 0 && KitchenCurrentSpeed == 0) {  //Если есть главный то начинаем отчёт от 1 если нет то с 0
          KitchenCurrentSpeed = 1;
          KitchenCurrentSpeed++;
        } else {
          KitchenCurrentSpeed++;
        }
      }
      if (KitchenCurrentSpeed > 4) {  //Если KitchenCurrentSpeed больше 4 проверяем есть ли главный
        if (DependenceHead > 0) {
          if (DependenceHead == 1) {  // если кухня главная, то позволяем выключить все авто вкл вентиляторы
            DependenceHead = 0;
            KitchenCurrentSpeed = 0;
            DependenceHead_State(1);
          } else {
            KitchenCurrentSpeed = 0;
          }
        } else {
          KitchenCurrentSpeed = 0;
        }
      }
    } else {
      if (DependenceHead > 0) {
        if (DependenceHead == 1) {  // если кухня главная, то позволяем выключить все авто вкл вентиляторы
          DependenceHead = 0;
          KitchenCurrentSpeed = 0;
          DependenceHead_State(1);
        } else {
          KitchenCurrentSpeed = 0;
        }
      } else {
        KitchenCurrentSpeed = 0;
      }
    }
    KitchenRunManual(KitchenCurrentSpeed);
  }
  void KitchenRunManual(int i) {
    if (DependenceHead == 0 && i != 0) {  //срабатывает только если нет главного и запрашиваемая скорость не 0
      DependenceHead = 1;
    }
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
        if (DependenceHead != 2 && DependenceHead != 0 && BathroomCurrentSpeed == 0) {  //Если есть главный то начинаем отчёт от 1 если нет то с 0
          BathroomCurrentSpeed = 1;
          BathroomCurrentSpeed++;
        } else {
          BathroomCurrentSpeed++;
        }
      }
      if (BathroomCurrentSpeed > 4) {  //Если BathroomCurrentSpeed больше 4 проверяем есть ли главный
        if (DependenceHead > 0) {
          if (DependenceHead == 2) {  // если BathroomCurrentSpeed главная, то позволяем выключить все авто вкл вентиляторы
            DependenceHead = 0;
            BathroomCurrentSpeed = 0;
            DependenceHead_State(2);
          } else {
            BathroomCurrentSpeed = 0;
          }
        } else {
          BathroomCurrentSpeed = 0;
        }
      }
    } else {
      if (DependenceHead > 0) {
        if (DependenceHead == 2) {  // если ванная главная, то позволяем выключить все авто вкл вентиляторы
          DependenceHead = 0;
          BathroomCurrentSpeed = 0;
          DependenceHead_State(2);  //это для того что бы сменить главного
        } else {
          BathroomCurrentSpeed = 0;
        }
      } else {
        BathroomCurrentSpeed = 0;
      }
    }
    BathroomRunManual(BathroomCurrentSpeed);
  }

  void BathroomRunManual(int i) {
    if (DependenceHead == 0 && i != 0) {  //срабатывает только если нет главного и запрашиваемая скорость не 0
      DependenceHead = 2;
    }
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

  /*все что касается туалета*/
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
        if (DependenceHead != 3 && DependenceHead != 0 && ToiletCurrentSpeed == 0) {  //Если есть главный то начинаем отчёт от 1 если нет то с 0
          ToiletCurrentSpeed = 1;
          ToiletCurrentSpeed++;
        } else {
          ToiletCurrentSpeed++;
        }
      }
      if (ToiletCurrentSpeed > 4) {  //Если ToiletCurrentSpeed больше 4 проверяем есть ли главный
        if (DependenceHead > 0) {
          if (DependenceHead == 3) {  // если ToiletCurrentSpeed главная, то позволяем выключить все авто вкл вентиляторы
            DependenceHead = 0;
            ToiletCurrentSpeed = 0;
            DependenceHead_State(3);
          } else {
            ToiletCurrentSpeed = 0;
          }
        } else {
          ToiletCurrentSpeed = 0;
        }
      }
    } else {
      if (DependenceHead > 0) {
        if (DependenceHead == 3) {  // если ванная главная, то позволяем выключить все авто вкл вентиляторы
          DependenceHead = 0;
          ToiletCurrentSpeed = 0;
          DependenceHead_State(3);  //это для того что бы сменить главного
        } else {
          ToiletCurrentSpeed = 0;
        }
      } else {
        ToiletCurrentSpeed = 0;
      }
    }
    ToiletRunManual(ToiletCurrentSpeed);
  }

  void ToiletRunManual(int i) {
    if (DependenceHead == 0 && i != 0) {  //срабатывает только если нет главного и запрашиваемая скорость не 0
      DependenceHead = 3;
    }
    Serial.print("ToiletRunManual Speed:");
    Serial.println(i);
    FanToilet.Speed(i, 0);
  }
  void ToiletRunAuto(int i) {
    Serial.print("ToiletRunAuto Speed:");
    Serial.println(i);
    FanToilet.Speed(i, 1);
  }
  void DependenceHead_State(int head) {
    if (KitchenCurrentSpeed > 1 && head != 1) {
      DependenceHead = 1;
      return;
    }
    if (BathroomCurrentSpeed > 1 && head != 2) {
      DependenceHead = 2;
      return;
    }
    if (ToiletCurrentSpeed > 1 && head != 3) {
      DependenceHead = 3;
      return;
    }
  }
  /*==все что касается ванной==*/
private:
  bool Flag1, Flag2, Flag3;
  //bool ManualFlag1, ManualFlag2, ManualFlag3;
  int Flag_rangeHoodspeed, oldFlag_rangeHoodspeed;
  int KitchenCurrentSpeed, BathroomCurrentSpeed, ToiletCurrentSpeed;
  int retKitchenCurrentSpeed, retBathroomCurrentSpeed, retToiletCurrentSpeed;
  int OldSpeedKitchen, DependenceHead;
  int oldKitchenCurrentSpeed,
    oldBathroomCurrentSpeed,
    oldToiletCurrentSpeed;
};