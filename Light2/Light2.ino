//6 переключателей
#define Dt_1_2 A0               //1:519-523  2:834-839 12:473-476
#define Dt_3_4 A1               //1:520-523  2:833-837 12:474-477
#define Photores1_Photores2 A2  //1:519-522  2:833-837 12:472-475
#define Photores3_Photores4 A3  //1:519-522  2:833-837 12:472-475
// 9 выходов
#define floorLight1 2
#define floorLight2 3
#define floorLight3 4
#define floorLight4 5

#define DelayTimeS 10

#include "ButtonGroup.h"
ButtonGroup BtnGroup0(Dt_1_2, 0, 0, 1023, 521, 836, 474);
ButtonGroup BtnGroup1(Dt_3_4, 0, 0, 1023, 521, 836, 474);
ButtonGroup BtnGroup2(Photores1_Photores2, 0, 0, 1023, 521, 836, 475);
ButtonGroup BtnGroup3(Photores3_Photores4, 0, 0, 1023, 521, 836, 475);

#include "Passage.h"
Passage Light1(floorLight1);
Passage Light2(floorLight2);
Passage Light3(floorLight3);
Passage Light4(floorLight4);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}
void loop() {
  Light1.run();
  Light2.run();
  // put your main code here, to run repeatedly:
  BtnGroup0.check();
  BtnGroup1.check();
  BtnGroup2.check();
  BtnGroup3.check();
  {  // гл выкл
    if (BtnGroup0.click1()) {
      if (!BtnGroup2.click1()) {
        Light1.On(true);
      }
    } else {
      Light1.On(false);
    }
    if (BtnGroup0.click2()) {
      if (!BtnGroup2.click2()) {
        Light2.On(true);
      }
    } else {
      Light2.On(false);
    }
    if (BtnGroup1.click1()) {
      if (!BtnGroup3.click1()) {
        Light3.On(true);
      }
    } else {
      Light3.On(false);
    }
    if (BtnGroup1.click2()) {
      if (!BtnGroup3.click2()) {
        Light4.On(true);
      }
    } else {
      Light4.On(false);
    }
  }
}