//12 ВХОДОВ
#define Dt_1_2 A0
#define Dt_3_4 A1
#define Dt_5_6 A2
#define Photores1_Photores2 A3
#define Photores3_Photores4 A4
#define Photores5_Photores6 A5
// 5 выходов
#define floorLight1 2
#define floorLight2 3
#define floorLight3 4
#define floorLight4 5
#define floorLight5 6
#define floorLight6 7

#define DelayTimeS 10

#include "ButtonGroup.h"
ButtonGroup BtnGroup0(Dt_1_2, 0, 0, 1023, 836, 521, 474);
ButtonGroup BtnGroup1(Dt_3_4, 0, 0, 1023, 836, 521, 474);
ButtonGroup BtnGroup2(Dt_5_6, 0, 0, 1023, 836, 521, 474);
ButtonGroup BtnGroup3(Photores1_Photores2, 0, 0, 1023, 836, 521, 474);
ButtonGroup BtnGroup4(Photores3_Photores4, 0, 0, 1023, 836, 521, 474);
ButtonGroup BtnGroup5(Photores5_Photores6, 0, 0, 1023, 836, 521, 474);

#include "Passage.h"
Passage Light1(floorLight1);
Passage Light2(floorLight2);
Passage Light3(floorLight3);
Passage Light4(floorLight4);
Passage Light5(floorLight5);
Passage Light6(floorLight6);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}
void loop() {
  Light1.run();
  Light2.run();
  Light3.run();
  Light4.run();
  Light5.run();
  Light6.run();
  // put your main code here, to run repeatedly:
  BtnGroup0.check();
  BtnGroup1.check();
  BtnGroup2.check();
  BtnGroup3.check();
  BtnGroup4.check();
  BtnGroup5.check();
  {  // гл выкл
    if (BtnGroup0.click1()) {
      if (!BtnGroup3.click1()) {
        Light1.On(true);
      }
    } else {
      Light1.On(false);
    }
    if (BtnGroup0.click2()) {
      if (!BtnGroup3.click2()) {
        Light2.On(true);
      }
    } else {
      Light2.On(false);
    }
    if (BtnGroup1.click1()) {
      if (!BtnGroup4.click1()) {
        Light3.On(true);
      }
    } else {
      Light3.On(false);
    }
    if (BtnGroup1.click2()) {
      if (!BtnGroup4.click2()) {
        Light4.On(true);
      }
    } else {
      Light4.On(false);
    }
    if (BtnGroup2.click1()) {
      if (!BtnGroup5.click1()) {
        Light4.On(true);
      }
    } else {
      Light4.On(false);
    }
    if (BtnGroup2.click2()) {
      if (!BtnGroup5.click2()) {
        Light4.On(true);
      }
    } else {
      Light4.On(false);
    }
  }
}