//6 переключателей
#define MainSwitch PB13
#define LBra PB14
#define RBra PB15
#define MainLight PA8
#define Ribbon PA11
#define BraTable PA12

// 9 выходов
#define RibbonP PA0          //2
#define RibbonBed PA1        //3
#define RibbonWDimly PA2     //4     //Лента шкафа тускло
#define RibbonWBrightly PA3  //5  //Лента шкафа ярко

#define Edge PA5     //7     //край
#define Centre PA6   //8   //центр
#define BraLBed PA7  //9  //Бра левая часть кровати
#define BraRBed PB0  //10
#define BraTape PB1  //11  //Бра стол

#define BtnGroupTime1 100  //программная задержка от помех для кликов
#define BtnGroupTime2 250  //время для средней длинны нажатия
#define BtnGroupTime3 400  //время для длинного нажатия

#include "button.h"

//#include "ButtonGroupS3.h"
Button Button1(MainSwitch, 1);
Button Button2(LBra, 1);
Button Button3(RBra, 1);
Button Button4(MainLight, 1);
Button Button5(Ribbon, 1);
Button Button6(BraTable, 1);

#include "CAN_Net.h"

#include "Room.h"
Room Room;

#include "CAN_Control.h"

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
  CAN_Setup();
}
void loop() {
  Room.run();
  // put your main code here, to run repeatedly:
  Button1.check();
  Button2.check();
  Button3.check();
  Button4.check();
  Button5.check();
  Button6.check();
  loop_CAN_Net();
  {  // гл выкл
    if (Button1.click()) {
      Serial.println("click1 MainSwitch");
      Room.clickMainSwitch();
    }
    if (Button1.hold1() || Button1.hold2()) {
      Serial.println("hold1_2 MainSwitch");
      Room.Off_On_Bra();
    }
    if (Button4.click()) {
      Serial.println("click2 MainSwitch 2");
      Room.clickMainSwitch();
    }
    if (Button4.hold1() || Button4.hold2()) {
      Serial.println("hold1_2 MainSwitch 2");
      Room.Off_On_Bra();
    }
  }
  {  //бра
    if (Button2.click()) {
      Serial.println("click2 BraL");
      Room.clickBraLSwitch();
    }
    if (Button2.hold1() || Button2.hold2()) {
      Serial.println("hold2_2 BraL");
      Room.Off_On_Bra();
    }
    if (Button3.click()) {
      Serial.println("click1 BraR");
      Room.clickBraRSwitch();
    }
    if (Button3.hold1() || Button3.hold2()) {
      Serial.println("hold1_2 BraR");
      Room.Off_On_Bra();
    }
  }
  {  //Выкл ленты
    if (Button5.click()) {
      Serial.println("click1 Ribbon");
      Room.clickRibbonSwitch();
    }
    if (Button5.hold1() || Button5.hold2()) {
      Serial.println("hold1_2 Ribbon");
      Room.Off_On_Bra();
    }
    if (Button5.click()) {
      Serial.println("click2 BraTable");
      Room.clickBraTSwitch();
    }
    if (Button5.hold1() || Button5.hold2()) {
      Serial.println("hold2_2 BraTable");
      Room.Off_On_Bra();
    }
  }
}