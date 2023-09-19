//8 переключателей
#define MainHallway_Passage A0  //1:519-523  2:834-839 12:473-476 1-2 & 12 Прихожая_Коридор
#define Kitchen_Lamp A1         //1:520-523  2:833-837 12:474-477 1-2-12 _Гл.выкл.Кухня_Люстра
#define Bar_Ribbon A2           //1:519-522  2:833-837 12:472-475 1-2-12 Бар_Лента
#define Balcony_R_and_L A3      //1:519-523  2:833-837 12:472-476 1-2-12 _Гл.выкл.Кухня_Люстра
// 11 выходов
/*Кухня*/
#define Working_area 2  //рабочая зона  */*
#define Lamp 3          //Лампа */*
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

#include "ButtonGroup.h"
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
#include "Control_Hallway_Passage.h"
Control_Hallway_Passage Control_Hallway_Passage;
#include "Control_Kitchen.h"
Control_Kitchen Control_Kitchen;
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
  // put your main code here, to run repeatedly:
  BtnGroup1.check();
  BtnGroup2.check();
  {  // гл выкл
    if (BtnGroup1.click1()) {
      Serial.println("click1 MainHallway");
      Control_Hallway_Passage.clickMainHallway();
    }
    if (BtnGroup1.hold1_1()) {
      Serial.println("hold1_1 MainHallway1");
      Control_Hallway_Passage.long1ClickMainHallway();
    }
    if (BtnGroup1.hold1_2()) {
      Serial.println("hold1_1 MainHallway2");
      Control_Hallway_Passage.long2ClickMainHallway();
    }
  }
  {  // выкл в прихожей
    if (BtnGroup1.click2()) {
      Control_Hallway_Passage.clickMainPassage();
      Serial.println("Passage");
    }
    if (BtnGroup1.hold2_2()) {
      Serial.println("hold2_2 Passage");
      Control_Hallway_Passage.long2ClickMainPassage();
    }
  }
  if (Control_Hallway_Passage.apartmentOff()) {  //выкл света во всей кв
    Serial.println("apartment Off");
  }
  {  // выкл в кухни
    if (BtnGroup2.click1()) {
      Control_Kitchen.clickMainKitchen();
      Serial.println("click1 Main Kitchen");
    }
    if (BtnGroup2.click2()) {
      //Control_Hallway_Passage.clickMainPassage();
      Serial.println("click2 Lamp");
    }
  }
}