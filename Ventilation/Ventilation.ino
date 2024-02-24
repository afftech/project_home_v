
#define RangeHood_1and2 A0        //465//816//417
#define RangeHood3_KitchenBtn A1  //463//816//415
#define BathroomBtn_Light A2      //460//816//413

#define ToiletBtn_Light A3  //463//817//415

#define FanToilet1 6  //////4 скорости
#define FanToilet2 7
#define FanToilet3 8
#define FanToilet4 9

#define FanBathroom1 10  //////4 скорости
#define FanBathroom2 11
#define FanBathroom3 12
#define FanBathroom4 13

#define FanKitchen1 2  //////4 скорости
#define FanKitchen2 3
#define FanKitchen3 4
#define FanKitchen4 5

#include "Fun.h"

Fun FanKitchen(FanKitchen1, FanKitchen2, FanKitchen3, FanKitchen4, 0, 0, 120); /*вентилятор кухни          (Pin 1 скорости,Pin 2 скорости,
                                                                                                            Pin 3 скорости,Pin 4 скорости, 
                                                                                                            Время выкл без включенного света, 
                                                                                                            время выкл когда свет выключен, 
                                                                                                            время выкл когда свет не выключили и он продолжает гореть)*/
Fun FanBathroom(FanBathroom1, FanBathroom2, FanBathroom3, FanBathroom4, 10, 5, 1);
Fun FanToilet(FanToilet1, FanToilet2, FanToilet3, FanToilet4, 10, 5, 1);

int RangeHood_Slave[3][3] = { { 2, 3, 4 },    //1 СКОРОСТЬ вытяжки {скорость кухни, скорость ванной, скорость туалета}
                              { 3, 3, 3 },    //2 СКОРОСТЬ вытяжки {скорость кухни, скорость ванной, скорость туалета}
                              { 4, 3, 2 } };  //3 СКОРОСТЬ вытяжки {скорость кухни, скорость ванной, скорость туалета}

#define BtnGroupTime1 100  //программная задержка от помех для кликов
#define BtnGroupTime2 350  //время для средней длинны нажатия
#define BtnGroupTime3 400  //время для длинного нажатия
#include "ButtonGroup.h"

ButtonGroup BtnGroup1(RangeHood_1and2, 0, 0, 1023, 465, 816, 417); /*BtnGroup**(аналоговый пин, 
                                                                                тип сигнала,
                                                                                тип сигнала,
                                                                                состояние без нажатия,
                                                                                состояние 1 сигнала,
                                                                                состояние 2 сигнала) */
                                                                   /*тип сигнала может быть:
                                                                                1 - это обычная кнопка 
                                                                                0 - это постоянный сигнал с залипанием*/
ButtonGroup BtnGroup2(RangeHood3_KitchenBtn, 0, 1, 1023, 463, 816, 415);
ButtonGroup BtnGroup3(BathroomBtn_Light, 1, 0, 1023, 463, 817, 415);
ButtonGroup BtnGroup4(ToiletBtn_Light, 1, 0, 1023, 460, 816, 413);


#include "Control.h"
Control control;

void setup() {
  Serial.begin(9600);
}

void loop() {
  BtnGroup1.check();
  BtnGroup2.check();
  BtnGroup3.check();
  BtnGroup4.check();

  control.RangeHood(BtnGroup1.click1(), BtnGroup1.click2(), BtnGroup2.click1());
  //Кухня
  if (BtnGroup2.click2()) {
    control.KitchenFan(true);
    Serial.println("Button: KitchenFan");
  }
  if (BtnGroup2.hold2_1() || BtnGroup2.hold2_2()) {
    control.KitchenFan(false);
    Serial.println("Stop: KitchenFan");
  }
  //Ванная комната
  if (BtnGroup3.click1()) {
    control.BathroomFan(true);
    Serial.println("Button: BathroomFan");
  }
  if (BtnGroup3.hold1_1() || BtnGroup3.hold1_2()) {
    control.BathroomFan(false);
    Serial.println("Stop: BathroomFan");
  }

  if (BtnGroup4.click1()) {
    control.ToiletFan(true);
    Serial.println("Button: ToileFan");
  }
  if (BtnGroup4.hold1_1() || BtnGroup4.hold1_2()) {
    control.ToiletFan(false);
    Serial.println("Stop: ToileFan");
  }
}