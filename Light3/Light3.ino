//8 переключателей
#define LitleRoom PB13
#define LitleRBra PB14
#define MiddleRoom PB15
#define MiddleRBra PA8
#define LoggiaB PA11
#define ToiletB PB12
#define BathroomB PA15
#define Miror PB3
#define Sensor_1 PB4
//#define Sensor_2 PB5
#define ApronB PB5  //PB6

// 12 выходов
#define MiddleRoomLight1 PA0  //2
#define MiddleRoomLight2 PA1  //3
//#define MiddleRoomLight3 PA2  //4 нет больше
#define MiddleRoomBra PB1     //11
#define LitleRoomLight1 PA4   //6
#define LitleRoomLight2 PA5   //7
#define LitleBraLRLight3 PA6  //8
#define ToiletLight PA7       //9
#define LoggiaLight PB10      //12
#define BathMirorLight PB11   //13
#define BathroomLight PB0     //10
#define RibbonWBrightly PA3   //5
#define Apron PA2             //PB12            //19              //A5

#define TimeOffDT 90  //Время в секундах выключения управления освещением комнаты

#define BtnGroupTime1 100  //программная задержка от помех для кликов
#define BtnGroupTime2 250  //время для средней длинны нажатия
#define BtnGroupTime3 400  //время для длинного нажатия

#include "button.h"
Button Button1(LitleRoom, 1);
Button Button2(LitleRBra, 1);
Button Button3(MiddleRoom, 1);
Button Button4(MiddleRBra, 1);
Button Button5(LoggiaB, 1);
Button Button6(ToiletB, 1);
Button Button7(BathroomB, 1);
Button Button8(Miror, 1);
Button Button9(Sensor_1, 0);
//Button Button10(Sensor_2, 0);
Button Button11(ApronB, 1);

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


#include "CAN_Net.h"

#include "Control_Kitchen.h"
Control_Kitchen Control_Kitchen;

#include "CAN_Control.h"

void setup() {
  // put your setup code here, to run once:
  pinMode(MiddleRoomLight1, OUTPUT);
  pinMode(MiddleRoomLight2, OUTPUT);
  //pinMode(MiddleRoomLight3, OUTPUT);
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
  CAN_Setup();
}
void loop() {
  little_Room.run();
  middle_Room.run();
  bathroom.run();
  loggia.run();
  toilet.run();
  Control_Kitchen.run();
  // put your main code here, to run repeatedly:
 Button1.check();
  Button2.check();
  Button3.check();
  Button4.check();
  Button5.check();
  Button6.check();
  Button7.check();
  Button8.check();
  Button9.check();
  //не надо //Button10.check();
  Button11.check();
  loop_CAN_Net();

  {  //Фартук и балкон

    if (Button11.click()) {
      Control_Kitchen.clickApron();
      Serial.println("click Apron");
    }
    if (Button11.hold1() || Button11.hold2()) {
      Control_Kitchen.OffKitchen();
      Serial.println("hold Apron");
    }
  }
  {  //малая комната
    if (Button1.click()) {
      Serial.println("click LitleRoomLight");
      little_Room.clickLitleRoom();
    }
    if (Button1.hold1() || Button1.hold2()) {
      Serial.println("hold LitleRoomLight Off");
      little_Room.Off_or_ONRoom();
    }
    if (Button2.click()) {
      Serial.println("click LitleRBra");
      little_Room.ClickLitleRBra();
    }
    if (Button2.hold1() || Button2.hold2()) {
      Serial.println("hold LitleRBra Off");
      little_Room.Off_or_ONRoom();
    }
  }
  {  //средняя комната
    if (Button3.click()) {
      Serial.println("click MiddleRoomLight");
      middle_Room.clickRoom();
    }
    if (Button3.hold1() || Button3.hold2()) {
      Serial.println("hold MiddleRoomLight Off");
      middle_Room.Off_or_ONRoom();
    }
    if (Button4.click()) {
      Serial.println("click MiddleRoomBra");
      middle_Room.ClickBra();
    }
    if (Button4.hold1() || Button4.hold2()) {
      Serial.println("hold MiddleRoomBra Off");
      middle_Room.Off_or_ONRoom();
    }
  }
  {  //лоджия
    if (Button5.click()) {
      Serial.println("click loggia");
      loggia.clickLoggia();
    }
    if (Button5.hold1() || Button5.hold2()) {
      Serial.println("hold loggia Off");
      loggia.Off_or_ONRoom();
    }
    if (Button6.click()) {  //Button6
      Serial.println("click Toilet");
      toilet.clickToilet();
    }
    if (Button6.hold1() || Button6.hold2()) {  //Button6
      Serial.println("hold Toilet Off");
      toilet.Off_or_ONRoom();
    }
  }
  {  //Ванна и зеркало Button7
      if (Button7.click()) {//Временно 
      Serial.println("click Bathroom");
      bathroom.clickBathroom();
    }
    if (Button7.hold2() || Button7.hold1()) {
      Serial.println("hold Bathroom Off");
      bathroom.Off_or_ONRoom();
    }
    if (Button8.click()) {
      Serial.println("click Mirror");
      bathroom.clickMirror();
    }
    if (Button8.hold2() || Button8.hold1()) {
      Serial.println("hold Mirror Off");
      bathroom.Off_or_ONRoom();
    }
  }
  if (Button9.click()) {  //Лента туалета по датчику
    Serial.println("click clickRibbon On");
    bathroom.clickRibbon();
  }
  /*if (Button10.click()) {  //Лента туалета по датчику
    Serial.println("click2 clickRibbon On");
    bathroom.clickRibbon();
  }*/
}