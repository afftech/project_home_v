//10 переключателей
#define MainHallway PB13
#define Passage PB14
#define Kitchen PB15
#define KitchenDuplicate PB4
#define Lamp PA8
#define Bra PA11
#define Ribbon PA12
#define Balcony_R PA15
#define Balcony_L PB3
#define Passage1 PB5
#define Passage2 PB6
// 11 выходов

/*Кухня*/
#define Working_area PA0  //2  //рабочая зона  */* //включаем если весь свет на кухне погас!!!
#define Lamp PA1          //3            //Лампа */*
#define Bra PA2           //4             //Бар */*
#define Ribbon PB1        //11         //Лента */ не горит*
#define Foot_light PB10   //12     //фартук */ не горит*  // Apron переезжает  ---> foot light (Выключается если что то из света кухни ON, вкл. если выкл всесь свет кухни погас)
/*Балкон*/
#define BalconyR PA3  //5  //балкон */*
#define BalconyL PA4  //6  //балкон */*
/*Коридор и прихожая*/
#define SmallLightHallway PA5  //7  //прихожая слабый свет */*
#define BigLightHallway PA6    //8    //прихожая сильный свет */*
#define SmallLightPassage PA7  //9  //Коридор */*
#define BigLightPassage PB0    //10   //Коридор */*


#define PowerUnit PB11  //13  //Включение блока питания */*
bool OnPowerUnit;       //Включение блока питания */*
#include "TimerOff.h"
Timer PowerOff(1);  //время выключения блока в минутах
Timer Timer1(1);    //время выключения подсветки в ноги в минутах (Кухня)
bool PowerOffState;

//для обычных кнопок ButtonGroup
#define BtnGroupTime1 40   //программная задержка от помех для кликов
#define BtnGroupTime2 390  //время для средней длинны нажатия
#define BtnGroupTime3 500  //время для длинного нажатия
//для таких же обычных кнопок только ButtonGroupS3.h
#define BtnGroupTimeS1 40    //программная задержка от помех для кликов
#define BtnGroupTimeS2 390   //время для средней длинны нажатия
#define BtnGroupTimeS3 3000  //время для длинного нажатия

#include "button.h"
#include "button3S.h"

Button3S Button1(MainHallway, 1);
Button Button2(Passage, 1);
Button Button3(Kitchen, 1);
Button Button3_D(KitchenDuplicate, 1);
Button Button4(Lamp, 1);
Button Button5(Bra, 1);
Button Button6(Ribbon, 1);
Button Button7(Balcony_R, 1);
Button Button8(Balcony_L, 1);
Button Button9(Passage1, 1);
Button Button10(Passage2, 1);


#include "Control_Hallway_Passage.h"
Control_Hallway_Passage Control_Hallway_Passage;
#include "Control_BalconyRL.h"
Control_BalconyRL Control_BalconyRL;
#include "Control_Kitchen.h"
Control_Kitchen Control_Kitchen;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Working_area, OUTPUT);
  pinMode(Lamp, OUTPUT);
  pinMode(Bra, OUTPUT);
  pinMode(Ribbon, OUTPUT);
  pinMode(Foot_light, OUTPUT);
  pinMode(BalconyR, OUTPUT);
  pinMode(BalconyL, OUTPUT);
  pinMode(SmallLightHallway, OUTPUT);
  pinMode(BigLightHallway, OUTPUT);
  pinMode(SmallLightPassage, OUTPUT);
  pinMode(BigLightPassage, OUTPUT);
  pinMode(PowerUnit, OUTPUT);
}
void loop() {
  Control_Hallway_Passage.run();
  Control_Kitchen.run();
  Control_BalconyRL.run();
  // put your main code here, to run repeatedly:
  Button1.check();
  Button2.check();
  Button3.check();
  Button3_D.check();
  Button4.check();
  Button5.check();
  Button6.check();
  Button7.check();
  Button8.check();
  Button9.check();
  Button10.check();

  {  // гл выкл
    if (Button1.click()) {
      //Serial.println(F("click1 MainHallway"));
      Control_Hallway_Passage.clickMainHallway();
    }
    if (Button1.hold1()) {
      //Serial.println(F("hold1_1 MainHallway1"));
      Control_Hallway_Passage.long1ClickMainHallway();
    }
    if (Button1.hold2()) {
      //Serial.println(F("hold1_1 MainHallway2"));
      Control_Hallway_Passage.long2ClickMainHallway();
    }
  }
  {  // выкл в прихожей
    if (Button2.click()) {
      Control_Hallway_Passage.clickMainPassage();
      //Serial.println(F("Passage1"));
    }
    if (Button2.hold1()) {
      //Serial.println(F("hold2_2 Passage1"));
      Control_Hallway_Passage.long1ClickMainPassage();
    }
    if (Button2.hold2()) {
      // Serial.println(F("hold2_2 Passage1"));
      Control_Hallway_Passage.long2ClickMainPassage();
    }
  }
  {  // выкл в прихожей
    if (Button9.click()) {
      Control_Hallway_Passage.clickMainPassage();
      // Serial.println(F("Passage2"));
    }
    if (Button9.hold1()) {
      //Serial.println(F("hold2_2 Passage2"));
      Control_Hallway_Passage.long1ClickMainPassage();
    }
    if (Button9.hold2()) {
      //Serial.println(F("hold2_2 Passage2"));
      Control_Hallway_Passage.long2ClickMainPassage();
    }
  }
  {  // выкл в прихожей
    if (Button10.click()) {
      Control_Hallway_Passage.clickMainPassage();
      //Serial.println(F("Passage3"));
    }
    if (Button10.hold1()) {
      //Serial.println(F("hold2_2 Passage3"));
      Control_Hallway_Passage.long1ClickMainPassage();
    }
    if (Button10.hold2()) {
      //Serial.println(F("hold2_2 Passage3"));
      Control_Hallway_Passage.long2ClickMainPassage();
    }
  }
  if (Control_Hallway_Passage.apartmentOff()) {  //выкл света во всей кв
    Control_Kitchen.OffKitchenfrom_Hallway_Passage();
    Control_BalconyRL.OffBalconyLR();
    //Serial.println(F("OffAll"));
  }
  {  // выкл в кухни
    if (Button3.click()) {
      Control_Kitchen.clickMainKitchen();
      //Serial.println(F("click1 Main Kitchen"));  //правый балкон вкл
    }
    if (Button3.hold1() || Button3.hold2()) {  //включить весь свет в кухне D2,D3.D4.D5.D11.D12
      Control_Kitchen.OffKitchen();
      //Serial.println(F("hold1_2 Main Kitchen"));  //правый балкон выкл
    }
    if (Button4.click()) {
      Control_Kitchen.clickLamp();
      //Serial.println(F("click2 Lamp"));
    }
    if (Button4.hold1() || Button4.hold2()) {
      Control_Kitchen.OffKitchen();
      //Serial.println(F("hold2_2 Lamp"));
    }
    //бар
    if (Button5.click()) {
      Control_Kitchen.clickBra();
      //Serial.println(F("click1 Bra"));
    }
    if (Button5.hold1() || Button5.hold2()) {
      Control_Kitchen.OffKitchen();
      //Serial.println(F("hold1_2 Bra"));
    }
    if (Button6.click()) {
      Control_Kitchen.clickRibbon();
      //Serial.println(F("click2 Ribbon"));
    }
    if (Button6.hold1() || Button6.hold2()) {
      Control_Kitchen.OffKitchen();
      //Serial.println(F("hold2_2 Ribbon"));
    }
  }
  {  //балкон
    if (Button7.click()) {
      Control_BalconyRL.clickMainBalconyR();
      //Serial.println(F("click2 BalconyR"));
    }
    if (Button7.hold1() || Button7.hold2()) {
      Control_BalconyRL.Off_or_Off_BalconyLR();
      //Serial.println(F("hold2_2 BalconyR"));
    }
    if (Button8.click()) {
      Control_BalconyRL.clickMainBalconyL();
      //Serial.println(F("click1 BalconyL"));
    }
    if (Button8.hold1() || Button8.hold2()) {
      Control_BalconyRL.Off_or_Off_BalconyLR();
      //Serial.println(F("hold1_2 BalconyL"));
    }
    if (Button3_D.click()) {  //кухня гл вкл
      Control_Kitchen.clickMainKitchen();
      //Serial.println(F("click1 Main Kitchen duplicate"));
    }
    if (Button3_D.hold1() || Button3_D.hold2()) {
      Control_Kitchen.OffKitchen();
      //Serial.println(F("hold1_2 Main Kitchen duplicate"));
    }
  }
  {  //запуск Блока питания
    PowerOff.run();
    if (Button1.stateBtn() || Button2.stateBtn() || Button9.stateBtn() || Button10.stateBtn()) {
      OnPowerUnit = true;
      PowerOffState = false;
      PowerOff.stop();
      //Serial.println(F("Stop"));
    }
    if (!Control_Hallway_Passage.OffPowerUnit()) {
      if (OnPowerUnit && !PowerOffState) {
        PowerOff.on();
        PowerOffState = true;
        //Serial.println(F("On"));
      }
      if (PowerOff.resp()) {
        OnPowerUnit = false;
      }
    }
    //Serial.println(OnPowerUnit);
    digitalWrite(PowerUnit, OnPowerUnit);
  }
}