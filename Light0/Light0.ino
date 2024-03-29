//8 переключателей
#define MainHallway_Passage A0  //1:519-523  2:834-839 12:473-476 1-2 & 12 Прихожая_Коридор
#define Kitchen_Lamp A1         //1:520-523  2:833-837 12:474-477 1-2-12 _Гл.выкл.Кухня_Люстра
#define Bra_Ribbon A2           //1:519-522  2:833-837 12:472-475 1-2-12 Бар_Лента добавляется ф-ия упр.---> foot light
#define NULL_Balcony_R A3       //1:519-523  2:833-837 12:472-476 1-2-12 Apron переезжает  (удалить от сюда)
#define Balcony_L A4            //1:519-523  2:833-837 12:472-476 1-2-12 Дубль Гл.выкл.Кухня
#define Passage1_Passage2 A5    //1:519-523  2:833-837 12:472-476 1-2-12 Дубль Гл.выкл.Кухня
// 11 выходов

/*Кухня*/
#define Working_area 2  //рабочая зона  */* //включаем если весь свет на кухне погас!!!
#define Lamp 3          //Лампа */*
#define Bra 4           //Бар */*
#define Ribbon 11       //Лента */ не горит*
#define Foot_light 12   //фартук */ не горит*  // Apron переезжает  ---> foot light (Выключается если что то из света кухни ON, вкл. если выкл всесь свет кухни погас)
/*Балкон*/
#define BalconyR 5  //балкон */*
#define BalconyL 6  //балкон */*
/*Коридор и прихожая*/
#define SmallLightHallway 7  //прихожая слабый свет */*
#define BigLightHallway 8    //прихожая сильный свет */*
#define SmallLightPassage 9  //Коридор */*
#define BigLightPassage 10   //Коридор */*


#define PowerUnit 13  //Включение блока питания */*
bool OnPowerUnit;     //Включение блока питания */*
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

#include "ButtonGroup.h"
#include "ButtonGroupS3.h"
ButtonGroupS3 BtnGroup0(MainHallway_Passage, 1, 1, 1023, 521, 836, 475);  //1023, 521, 836, 475
ButtonGroup BtnGroup1(MainHallway_Passage, 1, 1, 1023, 521, 836, 475);    /*ButtonGroup**(аналоговый пин, 
                                                                                тип сигнала,
                                                                                тип сигнала,
                                                                                состояние без нажатия,
                                                                                состояние 1 сигнала,
                                                                                состояние 2 сигнала) */
                                                                          /*тип сигнала может быть:
                                                                                1 - это обычная кнопка 
                                                                                0 - это постоянный сигнал с залипанием*/
ButtonGroup BtnGroup2(Kitchen_Lamp, 1, 1, 1023, 521, 836, 475);
ButtonGroup BtnGroup3(Bra_Ribbon, 1, 1, 1023, 521, 836, 475);
ButtonGroup BtnGroup4(NULL_Balcony_R, 1, 1, 1023, 521, 836, 475);
ButtonGroup BtnGroup5(Balcony_L, 1, 1, 1023, 521, 836, 475);
ButtonGroup BtnGroup6(Passage1_Passage2, 1, 1, 1023, 521, 836, 475);



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
  BtnGroup0.check();
  BtnGroup1.check();
  BtnGroup2.check();
  BtnGroup3.check();
  BtnGroup4.check();
  BtnGroup5.check();
  BtnGroup6.check();

  {  // гл выкл
    if (BtnGroup0.click1()) {
      //Serial.println(F("click1 MainHallway"));
      Control_Hallway_Passage.clickMainHallway();
    }
    if (BtnGroup0.hold1_1()) {
      //Serial.println(F("hold1_1 MainHallway1"));
      Control_Hallway_Passage.long1ClickMainHallway();
    }
    if (BtnGroup0.hold1_2()) {
      //Serial.println(F("hold1_1 MainHallway2"));
      Control_Hallway_Passage.long2ClickMainHallway();
    }
  }
  {  // выкл в прихожей
    if (BtnGroup1.click2()) {
      Control_Hallway_Passage.clickMainPassage();
      //Serial.println(F("Passage1"));
    }
    if (BtnGroup1.hold2_1()) {
      //Serial.println(F("hold2_2 Passage1"));
      Control_Hallway_Passage.long1ClickMainPassage();
    }
    if (BtnGroup1.hold2_2()) {
      // Serial.println(F("hold2_2 Passage1"));
      Control_Hallway_Passage.long2ClickMainPassage();
    }
  }
  {  // выкл в прихожей
    if (BtnGroup6.click1()) {
      Control_Hallway_Passage.clickMainPassage();
      // Serial.println(F("Passage2"));
    }
    if (BtnGroup6.hold1_1()) {
      //Serial.println(F("hold2_2 Passage2"));
      Control_Hallway_Passage.long1ClickMainPassage();
    }
    if (BtnGroup6.hold1_2()) {
      //Serial.println(F("hold2_2 Passage2"));
      Control_Hallway_Passage.long2ClickMainPassage();
    }
  }
  {  // выкл в прихожей
    if (BtnGroup6.click2()) {
      Control_Hallway_Passage.clickMainPassage();
      //Serial.println(F("Passage3"));
    }
    if (BtnGroup6.hold2_1()) {
      //Serial.println(F("hold2_2 Passage3"));
      Control_Hallway_Passage.long1ClickMainPassage();
    }
    if (BtnGroup6.hold2_2()) {
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
    if (BtnGroup2.click1()) {
      Control_Kitchen.clickMainKitchen();
      //Serial.println(F("click1 Main Kitchen"));  //правый балкон вкл
    }
    if (BtnGroup2.hold1_2() || BtnGroup2.hold1_1()) {  //включить весь свет в кухне D2,D3.D4.D5.D11.D12
      Control_Kitchen.OffKitchen();
      //Serial.println(F("hold1_2 Main Kitchen"));  //правый балкон выкл
    }
    if (BtnGroup2.click2()) {
      Control_Kitchen.clickLamp();
      //Serial.println(F("click2 Lamp"));
    }
    if (BtnGroup2.hold2_2() || BtnGroup2.hold2_1()) {
      Control_Kitchen.OffKitchen();
      //Serial.println(F("hold2_2 Lamp"));
    }
    //бар
    if (BtnGroup3.click1()) {
      Control_Kitchen.clickBra();
      //Serial.println(F("click1 Bra"));
    }
    if (BtnGroup3.hold1_2() || BtnGroup3.hold1_1()) {
      Control_Kitchen.OffKitchen();
      //Serial.println(F("hold1_2 Bra"));
    }
    if (BtnGroup3.click2()) {
      Control_Kitchen.clickRibbon();
      //Serial.println(F("click2 Ribbon"));
    }
    if (BtnGroup3.hold2_2() || BtnGroup3.hold2_1()) {
      Control_Kitchen.OffKitchen();
      //Serial.println(F("hold2_2 Ribbon"));
    }
  }
  {  //балкон
    if (BtnGroup4.click2()) {
      Control_BalconyRL.clickMainBalconyR();
      //Serial.println(F("click2 BalconyR"));
    }
    if (BtnGroup4.hold2_2() || BtnGroup4.hold2_1()) {
      Control_BalconyRL.Off_or_Off_BalconyLR();
      //Serial.println(F("hold2_2 BalconyR"));
    }
    if (BtnGroup5.click1()) {
      Control_BalconyRL.clickMainBalconyL();
      //Serial.println(F("click1 BalconyL"));
    }
    if (BtnGroup5.hold1_2() || BtnGroup5.hold1_1()) {
      Control_BalconyRL.Off_or_Off_BalconyLR();
      //Serial.println(F("hold1_2 BalconyL"));
    }
    if (BtnGroup5.click2()) {  //кухня гл вкл
      Control_Kitchen.clickMainKitchen();
      //Serial.println(F("click1 Main Kitchen duplicate"));
    }
    if (BtnGroup5.hold2_2() || BtnGroup5.hold2_1()) {
      Control_Kitchen.OffKitchen();
      //Serial.println(F("hold1_2 Main Kitchen duplicate"));
    }
  }
  {  //запуск Блока питания
    PowerOff.run();
    if (BtnGroup0.stateAnyBtn() || BtnGroup1.stateAnyBtn() || BtnGroup6.stateAnyBtn()) {
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