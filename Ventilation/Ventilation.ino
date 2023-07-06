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

#include "Control.h"
Control control;

#include "ButtonGroup.h"
ButtonGroup BtnGroup1(RangeHood_1and2, 0, 0, 1023, 816, 465, 417);
ButtonGroup BtnGroup2(RangeHood3_KitchenBtn, 0, 1, 1023, 816, 463, 415);
ButtonGroup BtnGroup4(BathroomBtn_Light, 0, 1, 1023, 817, 463, 415);
ButtonGroup BtnGroup3(ToiletBtn_Light, 0, 1, 1023, 816, 460, 413);

int RangeHood_Slave[3][3] = { { 0, 0, 0 },    //1 СКОРОСТЬ вытяжки {скорость кухни, скорость ванной, скорость туалета}
                              { 0, 0, 0 },    //2 СКОРОСТЬ вытяжки {скорость кухни, скорость ванной, скорость туалета}
                              { 0, 0, 0 } };  //3 СКОРОСТЬ вытяжки {скорость кухни, скорость ванной, скорость туалета}

int SpeedBathroom[] = { 0, 0 };   //Это массив скорости ванной. например {2,4} значит что после первого нажатия включится 2, после второго 4.
int Bathroom_Slave[] = { 0, 0 };  //Задать скорость вентиляторов в {Кухня, туалет} когда вентилятор в ванне включен;
int Toilet_Slave[] = { 0, 0 };
int SpeedToilet[] = { 0, 0 };  //Это массив скорости туалета. например {2,4} значит что после первого нажатия включится 2, после второго 4.


void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  //control.init();
}

void loop() {
  BtnGroup1.check();
  BtnGroup2.check();
  BtnGroup3.check();
  BtnGroup4.check();
  control.RangeHood(BtnGroup1.click1(), BtnGroup1.click2(), BtnGroup2.click1());
  if (BtnGroup2.click2) {
    control.KitchenFan();
  }
  if (BtnGroup2.click2) {
    control.BathroomFan();
  }
  if (BtnGroup3.click2) {
    control.ToileFan();
  }
  // Serial.println(analogRead(BathroomBtn_Light));
  //delay(10);
  // put your main code here, to run repeatedly:
}