//8 переключателей
#define MainHallway_Passage A0
#define Kitchen_Lamp A1
#define Bar_Ribbon A2
#define Apron_Balcony_R A3
#define Balcony_L_Double A4
// 11 выходов
/*Кухня*/
#define Working_area 2  //рабочая зона  */*
#define Lamp 3          //Люстра */*
#define Bar 4           //Бар */*
#define Ribbon 11       //Лента */ не горит*
#define Apron 12        //фартук */ не горит*
/*Балкон*/
#define BalconyR 5  //балкон */*
#define BalconyL 6  //балкон */*
/*Коридор и прихожая*/
#define SmallLightHallway 7  //прихожая слабый свет */*
#define BigLightHallway 8    //прихожая сильный свет */*
#define SmallLightPassage 9  //Коридор */*
#define BigLightPassage 10   //Коридор */*

#define TimeDoubleClick 350  //Время двойного клика */*

#include "ButtonGroup.h"
#include "ButtonGroupS3.h"
ButtonGroupS3 BtnGroup0(MainHallway_Passage, 1, 1, 1023, 521, 836, 474);
ButtonGroup BtnGroup1(MainHallway_Passage, 1, 1, 1023, 521, 836, 474); /*ButtonGroup**(аналоговый пин, 
                                                                                тип сигнала,
                                                                                тип сигнала,
                                                                                состояние без нажатия,
                                                                                состояние 1 сигнала,
                                                                                состояние 2 сигнала) */
                                                                       /*тип сигнала может быть:
                                                                                1 - это обычная кнопка 
                                                                                0 - это постоянный сигнал с залипанием*/
ButtonGroup BtnGroup2(Kitchen_Lamp, 1, 1, 1023, 521, 836, 475);
ButtonGroup BtnGroup3(Bar_Ribbon, 1, 1, 1023, 520, 836, 475);
ButtonGroup BtnGroup4(Apron_Balcony_R, 1, 1, 1023, 520, 836, 475);
ButtonGroup BtnGroup5(Balcony_L_Double, 1, 1, 1023, 520, 836, 475);
#include "Control_Hallway_Passage.h"
Control_Hallway_Passage Control_Hallway_Passage;
#include "Control_Kitchen.h"
Control_Kitchen Control_Kitchen;
#include "Control_BalconyRL.h"
Control_BalconyRL Control_BalconyRL;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Working_area, OUTPUT);
  pinMode(Lamp, OUTPUT);
  pinMode(Bar, OUTPUT);
  pinMode(Ribbon, OUTPUT);
  pinMode(Apron, OUTPUT);
  pinMode(BalconyR, OUTPUT);
  pinMode(BalconyL, OUTPUT);
  pinMode(SmallLightHallway, OUTPUT);
  pinMode(BigLightHallway, OUTPUT);
  pinMode(SmallLightPassage, OUTPUT);
  pinMode(BigLightPassage, OUTPUT);
}
void loop() {
  Control_Hallway_Passage.run();
  Control_Kitchen.run();
  Control_BalconyRL.run();
  // put your main code here, to run repeatedly:
  BtnGroup0.check();
  BtnGroup1.check();
  BtnGroup2.check();
  BtnGroup3.check();
  BtnGroup4.check();
  BtnGroup5.check();
  {  // гл выкл
    if (BtnGroup0.click1()) {
      Serial.println("click1 MainHallway");
      Control_Hallway_Passage.clickMainHallway();
    }
    if (BtnGroup0.hold1_1()) {
      Serial.println("hold1_1 MainHallway1");
      Control_Hallway_Passage.long1ClickMainHallway();
    }
    if (BtnGroup0.hold1_2()) {
      Serial.println("hold1_1 MainHallway2");
      Control_Hallway_Passage.long2ClickMainHallway();
    }
  }
  {  // выкл в прихожей
    if (BtnGroup1.click2()) {
      Control_Hallway_Passage.clickMainPassage();
      Serial.println("Passage");
    }
    if (BtnGroup1.hold2_1()) {
      Serial.println("hold2_2 Passage");
      Control_Hallway_Passage.long1ClickMainPassage();
    }
    if (BtnGroup1.hold2_2()) {
      Serial.println("hold2_2 Passage");
      Control_Hallway_Passage.long2ClickMainPassage();
    }
  }
  if (Control_Hallway_Passage.apartmentOff()) {  //выкл света во всей кв
    Control_Kitchen.OffKitchen();
    Control_BalconyRL.OffBalconyLR();
    Serial.println("OffAll");
  }
  {  // выкл в кухни
    if (BtnGroup2.click1()) {
      Control_Kitchen.clickMainKitchen();
      Serial.println("click1 Main Kitchen");
    }
    if (BtnGroup2.hold1_2()) {
      Control_Kitchen.OffKitchen();
      Serial.println("hold1_2 Main Kitchen");
    }
    if (BtnGroup2.click2()) {
      Control_Kitchen.clickLamp();
      Serial.println("click2 Lamp");
    }
    if (BtnGroup2.hold2_2()) {
      Control_Kitchen.OffKitchen();
      Serial.println("hold2_2 Lamp");
    }
    //бар
    if (BtnGroup3.click1()) {
      Control_Kitchen.clickBar();
      Serial.println("click1 Bar");
    }
    if (BtnGroup3.hold1_2()) {
      Control_Kitchen.OffKitchen();
      Serial.println("hold1_2 Bar");
    }
    if (BtnGroup3.click2()) {
      Control_Kitchen.clickRibbon();
      Serial.println("click2 Ribbon");
    }
    if (BtnGroup3.hold2_2()) {
      Control_Kitchen.OffKitchen();
      Serial.println("hold2_2 Ribbon");
    }
    if (BtnGroup4.click1()) {
      Control_Kitchen.clickApron();
      Serial.println("click1 Apron");
    }
    if (BtnGroup4.hold1_2()) {
      Control_Kitchen.OffKitchen();
      Serial.println("hold1_2 Apron");
    }
  }
  {  //балкон
    if (BtnGroup4.click2()) {
      Control_BalconyRL.clickMainBalconyR();
      Serial.println("click2 BalconyR");
    }
    if (BtnGroup4.hold2_2()) {
      Control_BalconyRL.OffBalconyLR();
      Serial.println("hold2_2 BalconyR");
    }
    if (BtnGroup5.click1()) {
      Control_BalconyRL.clickMainBalconyL();
      Serial.println("click1 BalconyL");
    }
    if (BtnGroup5.hold1_2()) {
      Control_BalconyRL.OffBalconyLR();
      Serial.println("hold1_2 BalconyL");
    }
  }
  {  //Дублирует 3 вход
    if (BtnGroup5.click2()) {
      Control_Kitchen.clickMainKitchen();
      Serial.println("click2 Main Kitchen 2");
    }
    if (BtnGroup5.hold2_2()) {
      Control_Kitchen.OffKitchen();
      Serial.println("hold2_2 Main Kitchen 2");
    }
  }
}