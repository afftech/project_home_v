//6 переключателей
#define MainSwitch_LBra A0  //1:519-523  2:834-839 12:473-476 1-2 & 12 Прихожая_Коридор
#define RBra_MainLight A1   //1:520-523  2:833-837 12:474-477 1-2-12 _Гл.выкл.Кухня_Люстра
#define Ribbon_BraTable A2  //1:519-522  2:833-837 12:472-475 1-2-12 Бар_Лента

// 9 выходов
#define RibbonP 2
#define RibbonBed 3
#define RibbonWDimly 4     //Лента шкафа тускло
#define RibbonWBrightly 5  //Лента шкафа ярко

#define Edge 7     //край
#define Centre 8   //центр
#define BraLBed 9  //Бра левая часть кровати
#define BraRBed 10
#define BraTape 11  //Бра стол

#include "ButtonGroup.h" /* Максимум 1s*/
//#include "ButtonGroupS3.h"                                           
ButtonGroup BtnGroup0(MainSwitch_LBra, 1, 1, 1023, 521, 836, 474);
ButtonGroup BtnGroup1(RBra_MainLight, 1, 1, 1023, 521, 836, 474);  
ButtonGroup BtnGroup2(Ribbon_BraTable, 1, 1, 1023, 521, 836, 475);


#include "Room.h"
Room Room;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(RibbonP, OUTPUT);
  pinMode(RibbonBed, OUTPUT);
  pinMode(RibbonWDimly, OUTPUT);
  pinMode(RibbonWBrightly, OUTPUT);
  pinMode(Edge, OUTPUT);
  pinMode(Centre, OUTPUT);
  pinMode(BraLBed, OUTPUT);
  pinMode(BraRBed, OUTPUT);
  pinMode(BraTape, OUTPUT);
}
void loop() {
  Room.run();
  // put your main code here, to run repeatedly:
  BtnGroup0.check();
  BtnGroup1.check();
  BtnGroup2.check();
  {  // гл выкл
    if (BtnGroup0.click1()) {
      Serial.println("click1 MainSwitch");
      Room.clickMainSwitch();
    }
    if (BtnGroup0.hold1_2()) {
      Serial.println("hold1_2 MainSwitch");
      Room.OffMainRoom();
    }
    if (BtnGroup1.click2()) {
      Serial.println("click2 MainSwitch 2");
      Room.clickMainSwitch();
    }
    if (BtnGroup1.hold2_2()) {
      Serial.println("hold1_2 MainSwitch 2");
      Room.OffMainRoom();
    }
  }
  {  //бра
    if (BtnGroup0.click2()) {
      Serial.println("click2 BraL");
      Room.clickBraLSwitch();
    }
    if (BtnGroup0.hold2_2()) {
      Serial.println("hold2_2 BraL");
      Room.OffMainRoom();
    }
    if (BtnGroup1.click1()) {
      Serial.println("click1 BraR");
      Room.clickBraRSwitch();
    }
    if (BtnGroup1.hold1_2()) {
      Serial.println("hold1_2 BraR");
      Room.OffMainRoom();
    }
  }
  {  //Выкл ленты
    if (BtnGroup2.click1()) {
      Serial.println("click1 Ribbon");
      Room.clickRibbonSwitch();
    }
    if (BtnGroup2.hold1_2()) {
      Serial.println("hold1_2 Ribbon");
      Room.OffMainRoom();
    }
    if (BtnGroup2.click2()) {
      Serial.println("click2 BraTable");
      Room.clickBraTSwitch();
    }
    if (BtnGroup2.hold2_2()) {
      Serial.println("hold2_2 BraTable");
      Room.OffMainRoom();
    }
  }
}