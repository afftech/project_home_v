//8 переключателей
#define LitleRoom_LitleRBra A0    //1:519-523  2:834-839 12:473-476
#define MiddleRoom_MiddleRBra A1  //1:520-523  2:833-837 12:474-477
#define Loggia_Toilet A2          //1:519-522  2:833-837 12:472-475
#define Bathroom_Miror A3
#define Sensor_1_2 A4
#define Apron_NULL A6  // _Apron
// 12 выходов
#define MiddleRoomLight1 2
#define MiddleRoomLight2 3
#define MiddleRoomLight3 4
#define MiddleRoomBra 11


#define LitleRoomLight1 6
#define LitleRoomLight2 7
#define LitleBraLRLight3 8
#define ToiletLight 9
#define LoggiaLight 12
#define BathMirorLight 13
#define BathroomLight 10
#define RibbonWBrightly 5
#define Apron 19  //A5

#define TimeOffDT 90  //Время в секундах выключения управления освещением комнаты

#define BtnGroupTime1 200  //программная задержка от помех для кликов
#define BtnGroupTime2 500  //время для средней длинны нажатия
#define BtnGroupTime3 100  //время для длинного нажатия

#include "ButtonGroup.h"   /* Максимум 1s*/
ButtonGroup BtnGroup0(LitleRoom_LitleRBra, 1, 1, 1023, 461, 815, 413);
ButtonGroup BtnGroup1(MiddleRoom_MiddleRBra, 1, 1, 1023, 461, 815, 413);
ButtonGroup BtnGroup2(Loggia_Toilet, 1, 1, 1023, 461, 815, 413);
ButtonGroup BtnGroup3(Bathroom_Miror, 1, 1, 1023, 461, 815, 413);
ButtonGroup BtnGroup4(Sensor_1_2, 0, 0, 1023, 461, 815, 413);
ButtonGroup BtnGroup5(Apron_NULL, 1, 1, 1023, 461, 815, 413);

#include "Little_Room.h"
Little_Room little_Room;
#include "Middle_Room.h"
Middle_Room middle_Room;
#include "Bathroom.h"
Bathroom bathroom;
#include "Loggia.h"
Loggia loggia;
#include "Toilet.h"
Toilet toilet;
#include "Control_Kitchen.h"
Control_Kitchen Control_Kitchen;

void setup() {
  // put your setup code here, to run once:
  pinMode(MiddleRoomLight1, OUTPUT);
  pinMode(MiddleRoomLight2, OUTPUT);
  pinMode(MiddleRoomLight3, OUTPUT);
  pinMode(RibbonWBrightly, OUTPUT);
  pinMode(LitleRoomLight1, OUTPUT);
  pinMode(LitleRoomLight2, OUTPUT);
  pinMode(LitleBraLRLight3, OUTPUT);
  pinMode(ToiletLight, OUTPUT);
  pinMode(BathroomLight, OUTPUT);
  pinMode(MiddleRoomBra, OUTPUT);
  pinMode(LoggiaLight, OUTPUT);
  pinMode(BathMirorLight, OUTPUT);
  pinMode(Apron, OUTPUT);

  Serial.begin(9600);
}
void loop() {
  little_Room.run();
  middle_Room.run();
  bathroom.run();
  loggia.run();
  toilet.run();
  Control_Kitchen.run();
  // put your main code here, to run repeatedly:
  BtnGroup0.check();
  BtnGroup1.check();
  BtnGroup2.check();
  BtnGroup3.check();
  BtnGroup4.check();
  BtnGroup5.check();
  {  //Фартук и балкон

    if (BtnGroup5.click1()) {
      Control_Kitchen.clickApron();
      //Serial.println("click1 Apron");
    }
    if (BtnGroup5.hold1_2()) {
      Control_Kitchen.OffKitchen();  //в сериал отправляем
      //Serial.println("hold1_2 Apron");
    }
  }
  {  //малая комната
    if (BtnGroup0.click1()) {
      //Serial.println("click1 LitleRoomLight");
      little_Room.clickLitleRoom();
    }
    if (BtnGroup0.hold1_2()) {
      //Serial.println("hold1_2 LitleRoomLight Off");
      little_Room.Off_or_ONRoom();
    }
    if (BtnGroup0.click2()) {
      //Serial.println("click2 LitleRBra");
      little_Room.ClickLitleRBra();
    }
    if (BtnGroup0.hold2_2()) {
      //Serial.println("hold2_2 LitleRBra Off");
      little_Room.Off_or_ONRoom();
    }
  }
  {  //средняя комната
    if (BtnGroup1.click1()) {
      //Serial.println("click1 MiddleRoomLight");
      middle_Room.clickRoom();
    }
    if (BtnGroup1.hold1_2()) {
      //Serial.println("hold1_2 MiddleRoomLight Off");
      middle_Room.Off_or_ONRoom();
    }
    if (BtnGroup1.click2()) {
      //Serial.println("click2 MiddleRoomBra");
      middle_Room.ClickBra();
    }
    if (BtnGroup1.hold2_2()) {
      //Serial.println("hold2_2 MiddleRoomBra Off");
      middle_Room.Off_or_ONRoom();
    }
  }
  {  //лоджия
    if (BtnGroup2.click1()) {
      //Serial.println("click1 loggia");
      loggia.clickLoggia();
    }
    if (BtnGroup2.hold1_2()) {
      //Serial.println("hold1_2 loggia Off");
      loggia.Off_or_ONRoom();
    }
    if (BtnGroup2.click2()) {
      //Serial.println("click2 Toilet");
      toilet.clickToilet();
    }
    if (BtnGroup2.hold2_2()) {
      //Serial.println("hold2_2 Toilet Off");
      toilet.Off_or_ONRoom();
    }
  }
  {  //Ванна и зеркало
    if (BtnGroup3.click1()) {
      //Serial.println("click1 Bathroom");
      bathroom.clickBathroom();
    }
    if (BtnGroup3.hold1_2()) {
      //Serial.println("hold1_2 Bathroom Off");
      bathroom.Off_or_ONRoom();
    }
    if (BtnGroup3.click2()) {
      //Serial.println("click2 Mirror");
      bathroom.clickMirror();
    }
    if (BtnGroup3.hold2_2()) {
      //Serial.println("hold2_2 Mirror Off");
      bathroom.Off_or_ONRoom();
    }
  }
  if (BtnGroup4.click1()) {  //Лента туалета по датчику
    //Serial.println("click1 clickRibbon On");
    bathroom.clickRibbon();
  }
  if (BtnGroup4.click2()) {  //Лента туалета по датчику
    //Serial.println("click2 clickRibbon On");
    bathroom.clickRibbon();
  }
}